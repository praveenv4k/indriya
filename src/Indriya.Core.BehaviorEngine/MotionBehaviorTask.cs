using System;
using System.Collections.Generic;
using Common.Logging;
using NCalc;
using NetMQ;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Quartz.Util;
using SharpDX;

namespace Indriya.Core.BehaviorEngine
{
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
                    Log.Info(@"------------- Task Details --------------");
                    Log.InfoFormat(@"Behavior Name : {0}", behavior.Name);
                    Log.InfoFormat(@"Human Id : {0}", behavior.Id);
                    Log.InfoFormat(@"Trigger Name : {0}", behavior.Trigger);
                    Log.InfoFormat(@"Confidence Level : {0}", behavior.ConfidenceLevel);
                    Log.InfoFormat(@"Priority : {0}", behavior.Priority);
                    Log.Info(@"-----------------------------------------");
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
                        Log.InfoFormat(@"Getting updated information about the human : {0}",
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
                        Log.InfoFormat(@"Getting updated information about the robot");
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
            if (pos != null && pos.HasValues)
            {
                t.X = pos.Value<float>("x")/1000;
                t.Y = pos.Value<float>("y")/1000;
                t.Z = pos.Value<float>("z")/1000;
            }
            if (orient != null && orient.HasValues)
            {
                q.X = orient.Value<float>("x");
                q.Y = orient.Value<float>("y");
                q.Z = orient.Value<float>("z");
                q.W = orient.Value<float>("w");
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
            if (pos != null && pos.HasValues)
            {
                t.X = pos.Value<float>("x")/1000;
                t.Y = pos.Value<float>("y")/1000;
                t.Z = pos.Value<float>("z")/1000;
            }
            if (orient != null && orient.HasValues)
            {
                q.X = orient.Value<float>("x");
                q.Y = orient.Value<float>("y");
                q.Z = orient.Value<float>("z");
                q.W = orient.Value<float>("w");
            }
            Matrix m = Matrix.RotationQuaternion(q);
            m.TranslationVector = t;
            return m;
        }

        public static void GetWorldFrameMatrix(string worldFrameJson, out Vector3 translation, out Matrix3x3 rotation, out Quaternion q)
        {
            translation = new Vector3(0, 0, 0);
            rotation = Matrix3x3.Identity;
            q = Quaternion.Identity;

            var jObj = JObject.Parse(worldFrameJson);
            var pos = jObj.SelectToken("$.position");
            var orient = jObj.SelectToken("$.orientation");
            if (pos != null && pos.HasValues)
            {
                translation.X = pos.Value<float>("x")/1000;
                translation.Y = pos.Value<float>("y")/1000;
                translation.Z = pos.Value<float>("z")/1000;
            }
            if (orient != null && orient.HasValues)
            {
                q = new Quaternion
                {
                    X = orient.Value<float>("x"),
                    Y = orient.Value<float>("y"),
                    Z = orient.Value<float>("z"),
                    W = orient.Value<float>("w")
                };
                rotation = Matrix3x3.RotationQuaternion(q);
            }
        }

        public static void GetLocalizationFromRobotJson(string robotJson, out Vector3 translation, out Matrix3x3 rotation, out Quaternion q)
        {
            translation = new Vector3(0, 0, 0);
            rotation = Matrix3x3.Identity;
            q = Quaternion.Identity;

            var jObj = JObject.Parse(robotJson);
            var localize = jObj.SelectToken("$.Localization");
            var pos = localize.SelectToken("$.Position");
            var orient = localize.SelectToken("$.Orientation");
            if (pos != null && pos.HasValues)
            {
                translation.X = pos.Value<float>("x")/1000;
                translation.Y = pos.Value<float>("y")/1000;
                translation.Z = pos.Value<float>("z")/1000;
            }
            if (orient != null && orient.HasValues)
            {
                q = new Quaternion
                {
                    X = orient.Value<float>("x"),
                    Y = orient.Value<float>("y"),
                    Z = orient.Value<float>("z"),
                    W = orient.Value<float>("w")
                };
                rotation = Matrix3x3.RotationQuaternion(q);
            }
        }

        public static void GetHumanPoseFromJson(string humanInfo, out Vector3 translation, out Matrix3x3 rotation, out Quaternion q)
        {
            translation = new Vector3(0, 0, 0);
            rotation = Matrix3x3.Identity;
            q = Quaternion.Identity;

            var jObj = JObject.Parse(humanInfo);
            var pos = jObj.SelectToken("$.TorsoPosition");
            var orient = jObj.SelectToken("$.TorsoOrientation");

            if (pos != null && pos.HasValues)
            {
                // Already in metres
                translation.X = pos.Value<float>("x");
                translation.Y = pos.Value<float>("y");
                translation.Z = pos.Value<float>("z");
            }
            if (orient != null && orient.HasValues)
            {
                // Check NaN
                var x = orient.Value<float>("x");
                if (float.IsNaN(x))
                {

                }
                else
                {
                    q = new Quaternion
                    {
                        X = orient.Value<float>("x"),
                        Y = orient.Value<float>("y"),
                        Z = orient.Value<float>("z"),
                        W = orient.Value<float>("w")
                    };
                }
                rotation = Matrix3x3.RotationQuaternion(q);
            }
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
                        Log.InfoFormat(@"Getting the world Frame");
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

        public static double AngleBetween(Vector2 vector1, Vector2 vector2)
        {
            vector1.Normalize();
            vector2.Normalize();

            double ratio = Vector2.Dot(vector1, vector2);

            double theta;

            if (ratio < 0)
            {
                theta = Math.PI - 2.0*Math.Asin((-vector1 - vector2).Length()/2.0);
            }
            else
            {
                theta = 2.0*Math.Asin((vector1 - vector2).Length()/2.0);
            }

            return theta;
        }


        public static double GetRelativeAngle(Vector2 v1, Vector2 v2)
        {
            // Note : http://www.euclideanspace.com/maths/algebra/vectors/angleBetween/issues/index.htm
            // It is useful to keep in mind that:
            // 1. We can always add or subtract 360° (or in radians 2π) to any angle without changing the angle it represents 
            //    (because after 360° we get back to where we started ). 
            //    In most implementations atan2 will return a value between +π and -π but if we want a value between 0 and 2π then we could add 2π to negative values.
            // 2. If atan2 returns a value between +π and -π then 
            //    atan2(v2.y,v2.x) - atan2(v1.y,v1.x)
            //    could return a value between +2π and -2π so if it is above +π we might want to subtract 2π and if it is below -π we might want to add 2π.
            // 3. If we are facing in direction 1 and we want to rotate to face in direction 2 we could rotate clockwise or anti-clockwise. 
            //    So a rotation of pi/2 in the clockwise direction is the same as in the anti-clockwise direction 3pi/4. 
            //    So we need to be clear if we always want to rotate in a clockwise direction or if we want to rotate clockwise or anti-clockwise depending on which is the smaller angle.
            var angle = Math.Atan2(v2.Y, v2.X) - Math.Atan2(v1.Y, v1.X);
            if (angle > Math.PI) angle -= Math.PI*2;
            if (angle < -Math.PI) angle += Math.PI*2;
            return angle;
        }

        public static float GetHeading(Quaternion q)
        {
            //var yaw = Math.Atan2(2.0*(q.Y*q.Z + q.W*q.X),
            //    q.W*q.W - q.X*q.X - q.Y*q.Y + q.Z*q.Z);
            var yaw = Math.Atan2(2.0 * (q.Y * q.W - q.X * q.Z),
                1 - 2 * q.Y * q.Y - 2 * q.Z * q.Z);
            return (float)yaw;
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
                    // Increment count once
                    count = count + 1;
                    if (!string.IsNullOrEmpty(humanInfo))
                    {
                        //Log.Info(humanInfo);
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
                                //Log.Info(humanInfo);
                            }
                            if (behaviorInfo != null)
                            {
                                Log.InfoFormat("Behavior Detail: {0}", behaviorInfo.ToString());
                                if (behaviorInfo.BehaviorName == "Say Expressively")
                                {
                                    var msg = string.Empty;
                                    var arg = string.Empty;
                                    var msgDict =
                                        behaviorInfo.Parameters.TryGetAndReturn("msg") as Dictionary<string, object>;
                                    var argDict =
                                        behaviorInfo.Parameters.TryGetAndReturn("arg") as Dictionary<string, object>;
                                    if (msgDict != null && argDict != null)
                                    {
                                        msg = msgDict.TryGetAndReturn("value") as string;
                                        arg = argDict.TryGetAndReturn("value") as string;
                                    }
                                    Log.InfoFormat("Msg: {0}, Arg: {1}", msg, arg);
                                    if (!string.IsNullOrEmpty(msg) && !string.IsNullOrEmpty(arg) &&
                                        !string.IsNullOrEmpty(behavior.TriggerCountVariable))
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
                                if (behaviorInfo.BehaviorName == "Move To")
                                {
                                    var humanDict =
                                        behaviorInfo.Parameters.TryGetAndReturn("human") as Dictionary<string, object>;
                                    var rotDict =
                                        behaviorInfo.Parameters.TryGetAndReturn("rotation") as Dictionary<string, object>;
                                    var transDict =
                                        behaviorInfo.Parameters.TryGetAndReturn("translation") as Dictionary<string, object>;
                                    var distDict =
                                        behaviorInfo.Parameters.TryGetAndReturn("dist") as Dictionary<string, object>;
                                    float isHuman, isRotation, isTranslation;
                                    float.TryParse(humanDict.TryGetAndReturn("value").ToString(), out isHuman);
                                    float.TryParse(transDict.TryGetAndReturn("value").ToString(), out isTranslation);
                                    float.TryParse(rotDict.TryGetAndReturn("value").ToString(), out isRotation);
                                    if (isHuman > 0 && isRotation > 0)
                                    {
                                        // Get Robot String
                                        var robotString = GetRobotInfo(contextServer);

                                        // Get World String
                                        var worldFrame = GetWorldFrame(contextServer);

                                        Matrix3x3 robotRot;
                                        Matrix3x3 worldRot;
                                        Matrix3x3 humanRot;

                                        Quaternion robotQ;
                                        Quaternion worldQ;
                                        Quaternion humanQ;

                                        Vector3 robotTrans;
                                        Vector3 worldTrans;
                                        Vector3 humanTrans;

                                        // Get the transformation from the JSON strings
                                        GetHumanPoseFromJson(humanInfo, out humanTrans, out humanRot, out humanQ);
                                        GetLocalizationFromRobotJson(robotString, out robotTrans, out robotRot,
                                            out robotQ);
                                        GetWorldFrameMatrix(worldFrame, out worldTrans, out worldRot, out worldQ);

                                        var humanMat = GetMatrixFromPose(humanQ,
                                            new Vector3(0, 0, 0));
                                        var worldMat = GetMatrixFromPose(worldQ,
                                            new Vector3(0, 0, 0));
                                        var robotMat = GetMatrixFromPose(robotQ,
                                            new Vector3(0, 0, 0));

                                        worldMat.Invert();
                                        var hWorld = worldMat*humanMat;
                                        var hRobot = worldMat*robotMat;

                                        var hWorldQ = Quaternion.RotationMatrix(hWorld);
                                        var rWorldQ = Quaternion.RotationMatrix(hRobot);

                                        var hWorldYaw = GetHeading(hWorldQ);
                                        var rWorldYaw = GetHeading(rWorldQ);

                                        // Compute the displacement of Robot and Human wrt to world frame
                                        worldRot.Invert();

                                        var hDisp =
                                            new Vector3(Vector3.Dot(worldRot.Column1, humanTrans),
                                                Vector3.Dot(worldRot.Column2, humanTrans),
                                                Vector3.Dot(worldRot.Column3, humanTrans)) -
                                            new Vector3(Vector3.Dot(worldRot.Column1, worldTrans),
                                                Vector3.Dot(worldRot.Column2, worldTrans),
                                                Vector3.Dot(worldRot.Column3, worldTrans));

                                        var rDisp =
                                            new Vector3(Vector3.Dot(worldRot.Column1, robotTrans),
                                                Vector3.Dot(worldRot.Column2, robotTrans),
                                                Vector3.Dot(worldRot.Column3, robotTrans)) -
                                            new Vector3(Vector3.Dot(worldRot.Column1, worldTrans),
                                                Vector3.Dot(worldRot.Column2, worldTrans),
                                                Vector3.Dot(worldRot.Column3, worldTrans));

                                        // We get the unit vector from Robot pointing towards human
                                        var toHumanVec = new Vector2(hDisp.X, hDisp.Y) -
                                                         new Vector2(rDisp.X, rDisp.Y);
                                        toHumanVec.Normalize();
                                        // Next we would like to align the X-Axis of the robot with that of this unit vector
                                        var yUnit = Vector2.UnitY;
                                        var xUnit = Vector2.UnitX;
                                        // Now we find the angle of rotation needed to do this alignment
                                        //var angle = Math.Acos(Vector2.Dot(toHumanVec, yUnit));
                                        var angle = GetRelativeAngle(xUnit, toHumanVec);
                                        if (rWorldYaw > 0)
                                            angle += rWorldYaw;
                                        else
                                            angle -= rWorldYaw;
                                        // Update the values of X,Y,Theta
                                        var xDict = behaviorInfo.Parameters.TryGetAndReturn("x") as
                                            Dictionary<string, object>;
                                        var yDict =
                                            behaviorInfo.Parameters.TryGetAndReturn("y") as
                                                Dictionary<string, object>;
                                        var thetaDict =
                                            behaviorInfo.Parameters.TryGetAndReturn("theta") as
                                                Dictionary<string, object>;

                                        Log.InfoFormat("Move To Rotation Angle : {0}",
                                            MathUtil.RadiansToDegrees((float) angle));

                                        if (xDict != null)
                                        {
                                            xDict["value"] = 0.0f;
                                        }
                                        if (yDict != null)
                                        {
                                            yDict["value"] = 0.0f;
                                        }
                                        if (thetaDict != null)
                                        {
                                            thetaDict["value"] = angle;
                                        }

                                    }
                                    else if (isHuman > 0 && isTranslation > 0)
                                    {
                                        // Get Robot String
                                        var robotString = GetRobotInfo(contextServer);

                                        // Get World String
                                        var worldFrame = GetWorldFrame(contextServer);

                                        Matrix3x3 robotRot;
                                        Matrix3x3 worldRot;
                                        Matrix3x3 humanRot;

                                        Quaternion robotQ;
                                        Quaternion worldQ;
                                        Quaternion humanQ;

                                        Vector3 robotTrans;
                                        Vector3 worldTrans;
                                        Vector3 humanTrans;

                                        // Get the transformation from the JSON strings
                                        GetHumanPoseFromJson(humanInfo, out humanTrans, out humanRot, out humanQ);
                                        GetLocalizationFromRobotJson(robotString, out robotTrans, out robotRot,
                                            out robotQ);
                                        GetWorldFrameMatrix(worldFrame, out worldTrans, out worldRot, out worldQ);

                                        var humanMat = GetMatrixFromPose(humanQ,
                                            new Vector3(0, 0, 0));
                                        var worldMat = GetMatrixFromPose(worldQ,
                                            new Vector3(0, 0, 0));
                                        var robotMat = GetMatrixFromPose(robotQ,
                                            new Vector3(0, 0, 0));

                                        worldMat.Invert();
                                        var hWorld = worldMat*humanMat;
                                        var hRobot = worldMat*robotMat;

                                        var hWorldQ = Quaternion.RotationMatrix(hWorld);
                                        var rWorldQ = Quaternion.RotationMatrix(hRobot);

                                        var hWorldYaw = GetHeading(hWorldQ);
                                        var rWorldYaw = GetHeading(rWorldQ);

                                        // Compute the displacement of Robot and Human wrt to world frame
                                        worldRot.Invert();

                                        var hDisp =
                                            new Vector3(Vector3.Dot(worldRot.Column1, humanTrans),
                                                Vector3.Dot(worldRot.Column2, humanTrans),
                                                Vector3.Dot(worldRot.Column3, humanTrans)) -
                                            new Vector3(Vector3.Dot(worldRot.Column1, worldTrans),
                                                Vector3.Dot(worldRot.Column2, worldTrans),
                                                Vector3.Dot(worldRot.Column3, worldTrans));

                                        var rDisp =
                                            new Vector3(Vector3.Dot(worldRot.Column1, robotTrans),
                                                Vector3.Dot(worldRot.Column2, robotTrans),
                                                Vector3.Dot(worldRot.Column3, robotTrans)) -
                                            new Vector3(Vector3.Dot(worldRot.Column1, worldTrans),
                                                Vector3.Dot(worldRot.Column2, worldTrans),
                                                Vector3.Dot(worldRot.Column3, worldTrans));

                                        // We get the unit vector from Robot pointing towards human
                                        var toHumanVec = new Vector2(hDisp.X, hDisp.Y) -
                                                         new Vector2(rDisp.X, rDisp.Y);
                                        var distance = toHumanVec.Length();
                                        var threshold = distance;
                                        if (distDict != null)
                                        {
                                            float.TryParse(humanDict.TryGetAndReturn("value").ToString(),
                                                out threshold);
                                        }

                                        var residual = 0.0f;
                                        if (distance > threshold)
                                        {
                                            residual = distance - threshold;
                                        }

                                        // Unit Vector
                                        toHumanVec.Normalize();
                                        //var residualVector = toHumanVec*residual;
                                        var residualVector = Vector2.UnitX*residual;

                                        // Update the values of X,Y,Theta
                                        var xDict = behaviorInfo.Parameters.TryGetAndReturn("x") as
                                            Dictionary<string, object>;
                                        var yDict =
                                            behaviorInfo.Parameters.TryGetAndReturn("y") as
                                                Dictionary<string, object>;
                                        var thetaDict =
                                            behaviorInfo.Parameters.TryGetAndReturn("theta") as
                                                Dictionary<string, object>;

                                        Log.InfoFormat("Move To X : {0}, Y:{1}", residualVector.X, residualVector.Y);

                                        if (xDict != null)
                                        {
                                            xDict["value"] = 0.75*residualVector.X;
                                        }
                                        if (yDict != null)
                                        {
                                            yDict["value"] = 0.75*residualVector.Y;
                                        }
                                        if (thetaDict != null)
                                        {
                                            thetaDict["value"] = 0.0f;
                                        }
                                    }
                                }
                                SyncExecuteBehavior(behaviorInfo);
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
                        if (behavior.ExecutionLifetime == BehaviorExecutionLifetime.until)
                        {
                            if (!string.IsNullOrEmpty(behavior.ExecutionEvalExpression) &&
                                !string.IsNullOrEmpty(behavior.TriggerCountVariable))
                            {
                                // Evaluating Termination condition
                                var expression = new Expression(behavior.ExecutionEvalExpression);
                                expression.Parameters.Add(behavior.TriggerCountVariable, count + 1);
                                var result = expression.Evaluate();
                                bool complete;
                                if (bool.TryParse(result.ToString(), out complete))
                                {
                                    behavior.CyclicActionsComplete = !complete;
                                }
                            }
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
                Log.ErrorFormat("Simple behavior stack_trace : {0}", ex.StackTrace);
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
                        //var robotString = GetRobotInfo(contextServer);
                        //var worldFrame = GetWorldFrame(contextServer);
                        //if (!string.IsNullOrEmpty(robotString) && !string.IsNullOrEmpty(worldFrame))
                        //{
                        //    var m = GetWorldFrameMatrix(worldFrame);
                        //    var r = GetLocalizationFromRobotJson(robotString);
                        //    Log.InfoFormat("Robot Info : {0}", string.Join(",", r.ToArray()));
                        //    Log.InfoFormat("World Frame : {0}", string.Join(",", m.ToArray()));
                        //}
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
                Log.ErrorFormat("Motion Behavior Task error : {0}", ex.Message);
            }
        }
    }
}