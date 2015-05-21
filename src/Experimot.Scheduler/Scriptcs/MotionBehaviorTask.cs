using System;
using System.Collections.Generic;
using Common.Logging;
using NetMQ;
using NCalc;
using Newtonsoft.Json.Linq;

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
                    SyncExecuteBehavior(behavior.InitActions);
                    behavior.InitActionsComplete = true;
                }

                // Evaluate Expression
                string humanInfo = GetHumanInfo(contextServer, behavior.Id);
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
                        var count = GestureTriggerCount(humanInfo, behavior.Trigger, behavior.ConfidenceLevel);
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
                    foreach (var behaviorInfo in behavior.RobotActions)
                    {
                        // Before executing each action get the latest information about the human
                        humanInfo = GetHumanInfo(contextServer, behavior.Id);
                        if (!string.IsNullOrEmpty(humanInfo))
                        {
                            Console.WriteLine(humanInfo);
                        }
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

                                sock.Send(behaviorName);
                                Log.InfoFormat("Sent behavior execution request: {0}", behaviorName);

                                var reply = sock.ReceiveString();
                                Log.InfoFormat("Behavior execution response: {0}", reply);
                            }
                        }
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
                    SyncExecuteBehavior(behavior.ExitActions);
                    behavior.ExitActionsComplete = true;
                }
            }
        }
        catch (Exception ex)
        {
            Log.ErrorFormat("Simple behavior error : {0}", ex.Message);
        }
    }

    public static void SyncExecuteBehavior(IList<BehaviorInfo> behaviorList)
    {
        try
        {
            if (behaviorList != null)
            {

                foreach (var behaviorInfo in behaviorList)
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

                            sock.Send(behaviorName);
                            Log.InfoFormat("Sent behavior execution request: {0}", behaviorName);

                            var reply = sock.ReceiveString();
                            Log.InfoFormat("Behavior execution response: {0}", reply);
                        }
                    }
                }

            }
        }
        catch (Exception ex)
        {
            Log.ErrorFormat("Simple behavior error : {0}", ex.Message);
        }
    }
}