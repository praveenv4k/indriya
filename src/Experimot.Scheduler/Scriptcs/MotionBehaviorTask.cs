using System;
using System.Runtime;
using System.Collections.Generic;
using Common.Logging;
using NetMQ;
using NCalc;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Quartz.Util;
using SharpDX;
using SharpDX.Mathematics;

public class MotionBehaviorTask : Quartz.IJob
{
    private static readonly ILog Log = LogManager.GetLogger(typeof (MotionBehaviorTask));

    public void Execute(Quartz.IJobExecutionContext context)
    {
        if (context != null)
        {
            var behavior = context.MergedJobDataMap.Get("MotionBasedBehavior") as MotionBasedBehavior;
            var contextServer = context.MergedJobDataMap.Get("ContextServer") as string;
            if (behavior != null)
            {
                Console.WriteLine(@"------------- Task Details --------------");
                Console.WriteLine(@"Behavior Name : {0}", behavior.Name);
                Console.WriteLine(@"Human Id : {0}", behavior.Id);
                Console.WriteLine(@"Trigger Name : {0}", behavior.Trigger);
                Console.WriteLine(@"Confidence Level : {0}", behavior.ConfidenceLevel);
                Console.WriteLine(@"Priority : {0}", behavior.Priority);
                Console.WriteLine(@"-----------------------------------------");
                SyncExecuteBehavior(contextServer, behavior);
            }
        }
    }

    public static string GetHumanInfo(string contextServer, int id)
    {
        string humanInfo = string.Empty;
        if (!string.IsNullOrEmpty(contextServer))
        {
            using (var ctx = NetMQContext.Create())
            {
                using (var sock = ctx.CreateRequestSocket())
                {
                    sock.Connect(contextServer);
                    Console.WriteLine(@"Getting updated information about the human : {0}",
                        id);
                    sock.Send(string.Format("human/{0}", id));
                    humanInfo = sock.ReceiveString();
                }
            }
        }
        return humanInfo;
    }

    public static string GetRobotInfo(string contextServer)
    {
        string robotInfo = string.Empty;
        if (!string.IsNullOrEmpty(contextServer))
        {
            using (var ctx = NetMQContext.Create())
            {
                using (var sock = ctx.CreateRequestSocket())
                {
                    sock.Connect(contextServer);
                    Console.WriteLine(@"Getting updated information about the robot");
                    sock.Send("robot");
                    robotInfo = sock.ReceiveString();
                }
            }
        }
        return robotInfo;
    }

    public static Matrix GetMatrixFromPose(Quaternion q, Vector3 t)
    {
        Matrix m = Matrix.RotationQuaternion(q);
        m.TranslationVector = t;
        return m;
    }

    public static Matrix GetWorldFrameMatrix(string worldFrameJson)
    {
        var jObj = JObject.Parse(worldFrameJson);
        var pos = jObj.SelectToken("$.position");
        var orient = jObj.SelectToken("$.orientation");
        var t = new Vector3();
        var q = Quaternion.Identity;
        if (pos.HasValues)
        {
            t.X = pos.Value<float>("x");
            t.Y = pos.Value<float>("y");
            t.Z = pos.Value<float>("z");
        }
        if (orient.HasValues)
        {
            q.X = pos.Value<float>("x");
            q.Y = pos.Value<float>("y");
            q.Z = pos.Value<float>("z");
            q.W = pos.Value<float>("w");
        }
        Matrix m = Matrix.RotationQuaternion(q);
        m.TranslationVector = t;
        return m;
    }

    public static Matrix GetLocalizationFromRobotJson(string robotJson)
    {
        var jObj = JObject.Parse(robotJson);
        var localize = jObj.SelectToken("$.Localization");
        var pos = localize.SelectToken("$.Position");
        var orient = localize.SelectToken("$.Orientation");
        var t = new Vector3();
        var q = Quaternion.Identity;
        if (pos.HasValues)
        {
            t.X = pos.Value<float>("x");
            t.Y = pos.Value<float>("y");
            t.Z = pos.Value<float>("z");
        }
        if (orient.HasValues)
        {
            q.X = pos.Value<float>("x");
            q.Y = pos.Value<float>("y");
            q.Z = pos.Value<float>("z");
            q.W = pos.Value<float>("w");
        }
        Matrix m = Matrix.RotationQuaternion(q);
        m.TranslationVector = t;
        return m;
    }

    public static string GetWorldFrame(string contextServer)
    {
        string worldFrame = string.Empty;
        if (!string.IsNullOrEmpty(contextServer))
        {
            using (var ctx = NetMQContext.Create())
            {
                using (var sock = ctx.CreateRequestSocket())
                {
                    sock.Connect(contextServer);
                    Console.WriteLine(@"Getting the world Frame");
                    sock.Send("world_frame");
                    worldFrame = sock.ReceiveString();
                }
            }
        }
        return worldFrame;
    }

    public static int GestureTriggerCount(string humanStr, string triggerName, int confidence)
    {
        if (!string.IsNullOrEmpty(humanStr))
        {
            JObject human = JObject.Parse(humanStr);
            JToken gestureToken = null;
            var gestures = human.SelectToken("$.Gestures");
            // ReSharper disable once LoopCanBeConvertedToQuery
            foreach (var gesture in gestures)
            {
                string name = gesture.Value<string>("Name");
                if (name == triggerName)
                {
                    gestureToken = gesture;
                    break;
                }
            }
            if (gestureToken != null)
            {
                JToken token = gestureToken.SelectToken("$.ConfidenceDict");
                // ReSharper disable once LoopCanBeConvertedToQuery
                foreach (var item in token)
                {
                    if (item.HasValues)
                    {
                        var level = item.First.Value<int>("Level");
                        if (level == confidence)
                        {
                            return item.First.Value<int>("Count");
                        }
                    }
                }
            }
        }
        return 0;
    }

    public static void SyncExecuteBehavior(string contextServer, MotionBasedBehavior behavior)
    {
        try
        {
            if (!string.IsNullOrEmpty(contextServer) && behavior != null)
            {
                // Execute Init actions only once
                if (!behavior.InitActionsComplete)
                {
                    SyncExecuteBehavior(contextServer, behavior.InitActions);
                    behavior.InitActionsComplete = true;
                }

                // Evaluate Expression
                string humanInfo = GetHumanInfo(contextServer, behavior.Id);
                var count = GestureTriggerCount(humanInfo, behavior.Trigger, behavior.ConfidenceLevel);
                if (!string.IsNullOrEmpty(humanInfo))
                {
                    Console.WriteLine(humanInfo);
                }
                if (behavior.ExecutionLifetime == BehaviorExecutionLifetime.until)
                {
                    if (!string.IsNullOrEmpty(behavior.ExecutionEvalExpression) &&
                        !string.IsNullOrEmpty(behavior.TriggerCountVariable))
                    {
                        // Evaluating Termination condition
                        var expression = new Expression(behavior.ExecutionEvalExpression);
                        expression.Parameters.Add(behavior.TriggerCountVariable, count);
                        var result = expression.Evaluate();
                        bool complete;
                        if (bool.TryParse(result.ToString(), out complete))
                        {
                            behavior.CyclicActionsComplete = !complete;
                        }
                    }
                }
                if (!behavior.CyclicActionsComplete)
                {
                    foreach (var behaviorItem in behavior.RobotActions)
                    {
                        var behaviorInfo = behaviorItem.Clone() as BehaviorInfo;

                        // Before executing each action get the latest information about the human
                        humanInfo = GetHumanInfo(contextServer, behavior.Id);
                        if (!string.IsNullOrEmpty(humanInfo))
                        {
                            Console.WriteLine(humanInfo);
                        }
                        if (behaviorInfo != null)
                        {
                            if (behaviorInfo.BehaviorName == "Say Expressively")
                            {
                                var msg = string.Empty;
                                var arg = string.Empty;
                                var msgDict = behaviorInfo.Parameters.TryGetAndReturn("msg") as Dictionary<string,object>;
                                var argDict = behaviorInfo.Parameters.TryGetAndReturn("arg") as Dictionary<string, object>;
                                if (msgDict != null && argDict != null)
                                {
                                    msg = msgDict.TryGetAndReturn("value") as string;
                                    arg = argDict.TryGetAndReturn("value") as string;
                                }
                                Log.InfoFormat("Msg: {0}, Arg: {1}", msg, arg);
                                if (!string.IsNullOrEmpty(msg) && !string.IsNullOrEmpty(arg))
                                {
                                    var newMsg = string.Empty;
                                    if (arg == behavior.TriggerCountVariable)
                                    {
                                        newMsg = string.Format(msg, count);
                                        if (msgDict != null) msgDict["value"] = newMsg;
                                        //behaviorInfo.Parameters["msg"] = newMsg;
                                    }
                                    Log.InfoFormat("New Msg: {0}, Count : {1}", newMsg, count);
                                }
                            }
                        }
                        SyncExecuteBehavior(behaviorInfo);
                    }
                }
                if (behavior.BehaviorType == BehaviorType.Behavior)
                {
                    if (behavior.ExecutionLifetime == BehaviorExecutionLifetime.once)
                    {
                        behavior.CyclicActionsComplete = true;
                    }
                    if (behavior.RobotActions.Count == 0)
                    {
                        behavior.CyclicActionsComplete = true;
                    }
                }
                // Execute exit actions only once
                if (behavior.CyclicActionsComplete && !behavior.ExitActionsComplete)
                {
                    SyncExecuteBehavior(contextServer, behavior.ExitActions);
                    behavior.ExitActionsComplete = true;
                }
            }
        }
        catch (Exception ex)
        {
            Log.ErrorFormat("Simple behavior error : {0}", ex.Message);
        }
    }

    public static void SyncExecuteBehavior(string contextServer, IList<BehaviorInfo> behaviorList)
    {
        try
        {
            if (behaviorList != null)
            {

                foreach (var behaviorInfo in behaviorList)
                {
                    var robotString = GetRobotInfo(contextServer);
                    var worldFrame = GetWorldFrame(contextServer);
                    if (!string.IsNullOrEmpty(robotString) && !string.IsNullOrEmpty(worldFrame))
                    {
                        var m = GetWorldFrameMatrix(worldFrame);
                        var r = GetLocalizationFromRobotJson(robotString);
                        Log.InfoFormat("Robot Info : {0}", string.Join(",", r.ToArray()));
                        Log.InfoFormat("World Frame : {0}", string.Join(",", m.ToArray()));
                    }
                    SyncExecuteBehavior(behaviorInfo);
                }

            }
        }
        catch (Exception ex)
        {
            Log.ErrorFormat("Simple behavior error : {0}", ex.Message);
        }
    }

    public static void SyncExecuteBehavior(BehaviorInfo behaviorInfo)
    {
        try
        {
            using (var ctx = NetMQContext.Create())
            {
                using (var sock = ctx.CreateRequestSocket())
                {
                    var ip = behaviorInfo.Ip;
                    var port = behaviorInfo.Port;
                    var behaviorName = behaviorInfo.BehaviorName;
                    var moduleName = behaviorInfo.ModuleName;

                    var addr = string.Format("{0}:{1}", ip, port);
                    Log.InfoFormat("Connecting to behavior server - Module: {0}, Address: {1}",
                        moduleName, addr);

                    sock.Connect(addr);
                    Log.InfoFormat("Connected to behavior server: {0}", addr);

                    //sock.Send(behaviorName);
                    sock.Send(JsonConvert.SerializeObject(behaviorInfo));
                    Log.InfoFormat("Sent behavior execution request: {0}", behaviorName);

                    var reply = sock.ReceiveString();
                    Log.InfoFormat("Behavior execution response: {0}", reply);
                }
            }
        }
        catch (Exception ex)
        {
            Log.ErrorFormat("Simple behavior error : {0}", ex.Message);
        }
    }
}