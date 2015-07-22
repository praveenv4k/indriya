using System;
using System.Collections.Generic;
using Common.Logging;
using NetMQ;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Quartz.Util;
using SharpDX;

namespace Indriya.Core.BehaviorEngine
{ // ReSharper disable FunctionComplexityOverflow
// ReSharper disable LoopCanBeConvertedToQuery

    public static class RobotStatusString
    {
        public const string StsRun = "RUN";
        public const string StsRunReady = "RUN_READY";
        public const string StsWaitArg = "WAIT_ARG";
        public const string StsIdle = "IDLE";
        public const string StsErr = "ERR";
        public const string StsUnknown = "UNKNOWN";
    }

    public static class RobotCommandString
    {
        public const string CmdStartReq = "START_REQ";
        public const string CmdRunReq = "RUN_REQ";
        public const string CmdStsReq = "STS_REQ";
        public const string CmdStopReq = "STOP_REQ";
        public const string CmdResetReq = "RESET_REQ";
    }

    public class BehaviorExecutionContext : IBehaviorExecutionContext
    {
        private readonly string _contextServer;
        private static readonly ILog Log = LogManager.GetLogger(typeof(BehaviorExecutionContext));
        private bool _cancelRequest;
        private readonly object _object = new object();
        private const int RecvTimeout = 500;
        private const int FsmPeriod = 50;
        private const int SpeechDuration = 2500;

        public string ContextServer
        {
            get { return _contextServer; }
        }

        public BehaviorExecutionContext(string contextServer)
        {
            _contextServer = contextServer;
        }

        public static string GetContextJsonString(string contextServer,int timeout, string reqName)
        {
            string resp;
            using (var ctx = NetMQContext.Create())
            {
                using (var socket = ctx.CreateRequestSocket())
                {
                    socket.Connect(contextServer);
                    socket.Send(reqName);
                    resp = socket.ReceiveString(new TimeSpan(0, 0, 0, 0, timeout));
                }
            }
            return resp;
        }

        public void UpdateBehaviorResponderInfo(BehaviorInfo info)
        {
            if (info != null && !string.IsNullOrEmpty(info.BehaviorName) && !string.IsNullOrEmpty(info.RobotName))
            {
                Log.InfoFormat("Getting runtime information for {0} : {1}", info.BehaviorName, info.RobotName);
                var resp = GetContextJsonString(ContextServer, RecvTimeout,
                    string.Format("behavior_module/robot/{0}", info.RobotName));
                //Log.InfoFormat("Context: {1}, Behavior Modules  : {0}", resp, ContextServer);
                if (!string.IsNullOrEmpty(resp))
                {
                    var module = JObject.Parse(resp);
                    //if (modules != null && modules.Count > 0)
                    if (module != null)
                    {
                        Log.InfoFormat("Module not null");
                        var moduleName = module.Value<string>("name");
                        var responder = module.SelectToken("$.responder");
                        string host = string.Empty;
                        int port = 0;
                        if (responder != null)
                        {
                            host = responder.Value<string>("Host");
                            port = responder.Value<int>("Port");
                        }
                        var behaviors = module.SelectToken("$.behaviors");
                        foreach (var behavior in behaviors)
                        {
                            string name = behavior.Value<string>("name");
                            string functionName = behavior.Value<string>("function_name");
                            var args = behavior.SelectToken("$.arg");
                            if (info.BehaviorName == name)
                            {
                                var parameters = new Dictionary<string, object>();
                                // ReSharper disable once LoopCanBeConvertedToQuery
                                foreach (var arg in args)
                                {
                                    parameters.Add(arg.Value<string>("name"), new Dictionary<string, object>
                                    {
                                        {"value", arg.Value<string>("value")},
                                        {"place_holder", arg.Value<string>("place_holder")},
                                        {"type", arg.Value<string>("type")}
                                    });
                                }

                                var matchingBehavior = info;
                                matchingBehavior.ModuleName = moduleName;
                                matchingBehavior.FunctionName = functionName;
                                matchingBehavior.Ip = host;
                                matchingBehavior.Port = port;
                                foreach (var parameter in parameters)
                                {
                                    if (!matchingBehavior.Parameters.ContainsKey(parameter.Key))
                                    {
                                        matchingBehavior.Parameters.Add(parameter);
                                    }
                                }
                                Log.InfoFormat("Obtained the responder info: {0}:{1}", host, port);
                                break;
                            }
                        }
                    }
                }
            }
        }

        public void UpdateBehaviorResponderInfo2(BehaviorInfo info)
        {
            if (info != null && !string.IsNullOrEmpty(info.BehaviorName))
            {
                var resp = GetContextJsonString(ContextServer, RecvTimeout, "behavior_modules");
                //Log.InfoFormat("Context: {1}, Behavior Modules  : {0}", resp, ContextServer);
                if (!string.IsNullOrEmpty(resp))
                {
                    var modules = JArray.Parse(resp);
                    if (modules != null && modules.Count > 0)
                    {
                        foreach (var module in modules)
                        {
                            var moduleName = module.Value<string>("name");
                            string robot = module.Value<string>("robot");
                            if (info.RobotName == robot)
                            {
                                var responder = module.SelectToken("$.responder");
                                string host = string.Empty;
                                int port = 0;
                                if (responder != null)
                                {
                                    host = responder.Value<string>("Host");
                                    port = responder.Value<int>("Port");
                                }
                                var behaviors = module.SelectToken("$.behaviors");
                                foreach (var behavior in behaviors)
                                {
                                    string name = behavior.Value<string>("name");
                                    string functionName = behavior.Value<string>("function_name");
                                    var args = behavior.SelectToken("$.arg");
                                    if (info.BehaviorName == name)
                                    {
                                        var parameters = new Dictionary<string, object>();
                                        // ReSharper disable once LoopCanBeConvertedToQuery
                                        foreach (var arg in args)
                                        {
                                            parameters.Add(arg.Value<string>("name"), new Dictionary<string, object>
                                            {
                                                {"value", arg.Value<string>("value")},
                                                {"place_holder", arg.Value<string>("place_holder")},
                                                {"type", arg.Value<string>("type")}
                                            });
                                        }

                                        var matchingBehavior = info;
                                        matchingBehavior.ModuleName = moduleName;
                                        matchingBehavior.FunctionName = functionName;
                                        matchingBehavior.Ip = host;
                                        matchingBehavior.Port = port;
                                        foreach (var parameter in parameters)
                                        {
                                            if (!matchingBehavior.Parameters.ContainsKey(parameter.Key))
                                            {
                                                matchingBehavior.Parameters.Add(parameter);
                                            }
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        public void SyncExecuteBehavior(BehaviorInfo behaviorInfo)
        {
            //try
            {
                DisplayRobotPose();
                using (var ctx = NetMQContext.Create())
                {
                    using (var sock = ctx.CreateRequestSocket())
                    {
                        var ip = behaviorInfo.Ip;
                        var port = behaviorInfo.Port;
                        //var behaviorName = behaviorInfo.BehaviorName;
                        var moduleName = behaviorInfo.ModuleName;
                        string respMsg = string.Empty;
                        var addr = string.Format("{0}:{1}", ip, port);
                        Log.InfoFormat("Connecting to behavior server - Module: {0}, Address: {1}",
                            moduleName, addr);

                        sock.Connect(addr);
                        Log.InfoFormat("Connected to behavior server: {0}", addr);

                        bool canceled = false;
                        int state = 0;
                        int loopCount = 0;
                        while (true)
                        {
                            if (loopCount > 0)
                            {
                                System.Threading.Thread.Sleep(FsmPeriod);
                            }
                            loopCount++;
                            bool cancel;
                            lock (_object)
                            {
                                cancel = CancelRequest;
                                CancelRequest = false;
                            }
                            if (cancel)
                            {
                                Log.Info("Cancel received");
                                sock.Send(RobotCommandString.CmdStopReq);
                                Log.Info("Cancel sent");
                                canceled = true;
                                state = 99;
                            }
                            if (state == -1)
                            {
                                if (canceled)
                                {
                                    throw new BehaviorCanceledException("Behavior canceled");
                                }
                                break;
                            }

                            switch (state)
                            {
                                case 0:
                                    sock.Send(RobotCommandString.CmdStartReq);
                                    state = 99;
                                    continue;
                                case 1:
                                    sock.Send(JsonConvert.SerializeObject(behaviorInfo));
                                    state = 99;
                                    continue;
                                case 2:
                                    sock.Send(RobotCommandString.CmdRunReq);
                                    state = 99;
                                    continue;
                                case 3:
                                    sock.Send(RobotCommandString.CmdStsReq);
                                    state = 99;
                                    continue;
                                case 4:
                                    sock.Send(RobotCommandString.CmdResetReq);
                                    state = 99;
                                    continue;
                                case 99:
                                    var str = sock.ReceiveString();
                                    var jObj = JObject.Parse(str);
                                    if (jObj != null && jObj.HasValues)
                                    {
                                        var resp = jObj.Value<string>("resp");
                                        var msg = jObj.Value<string>("msg");
                                        if (respMsg != msg)
                                        {
                                            respMsg = msg;
                                            Log.InfoFormat("Behavior Module: status - {1} , response message - {0}",
                                                respMsg, resp);
                                        }
                                        if (!string.IsNullOrEmpty(resp))
                                        {
                                            if (resp == RobotStatusString.StsWaitArg)
                                            {
                                                state = 1;
                                            }
                                            else if (resp == RobotStatusString.StsRunReady)
                                            {
                                                state = 2;
                                            }
                                            else if (resp == RobotStatusString.StsRun)
                                            {
                                                state = 3;
                                            }
                                            else if (resp == RobotStatusString.StsErr)
                                            {
                                                state = 4;
                                            }
                                            else if (resp == RobotStatusString.StsIdle)
                                            {
                                                state = -1;
                                            }
                                        }
                                    }
                                    continue;
                            }
                        }
                    }
                }
            }
            //catch (Exception ex)
            //{
            //    Log.ErrorFormat("Motion Behavior Task error : {0}", ex.Message);
            //}
        }

        public void SyncExecuteBehavior2(BehaviorInfo behaviorInfo)
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

        public bool GetHumanExists()
        {
            var humansStr = GetContextJsonString(ContextServer, RecvTimeout, "humans");
            if (!string.IsNullOrEmpty(humansStr))
            {
                var humans = JArray.Parse(humansStr);
                return humans.Count > 0;
            }
            return false;
        }

        public void GetNearestHuman(out int id, out double distance)
        {
            id = -1;
            distance = double.PositiveInfinity;

            var humansStr = GetContextJsonString(ContextServer, RecvTimeout, "humans");
            var robotStr = GetContextJsonString(ContextServer, RecvTimeout, "robot");
            var worldFrameStr = GetContextJsonString(ContextServer, RecvTimeout, "world_frame");
            if (!string.IsNullOrEmpty(humansStr) && !string.IsNullOrEmpty(robotStr) && !string.IsNullOrEmpty(worldFrameStr))
            {
                var humans = JArray.Parse(humansStr);

                Matrix3x3 robotRot;
                Matrix3x3 worldRot;

                Quaternion robotQ;
                Quaternion worldQ;

                Vector3 robotTrans;
                Vector3 worldTrans;

                GetLocalizationFromRobotJson(robotStr, out robotTrans, out robotRot,
                    out robotQ);
                GetWorldFrameMatrix(worldFrameStr, out worldTrans, out worldRot, out worldQ);

                foreach (var human in humans)
                {
                    // Get the transformation from the JSON strings
                    Matrix3x3 humanRot;
                    Quaternion humanQ;
                    Vector3 humanTrans;
                    GetHumanPoseFromJson(human, out humanTrans, out humanRot, out humanQ);

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
                    var length = toHumanVec.Length();
                    if (length < distance)
                    {
                        distance = length;
                        id = human.Value<int>("Id");
                    }
                }
            }
        }

        public void GetRelativePose(int id, out double dx, out double dy, out double dTheta)
        {
            throw new NotImplementedException();
        }

        public bool CheckHumanProximity(double threshold, out int id)
        {
            double distance;
            GetNearestHuman(out id, out distance);
            if (distance <= threshold && id != -1)
            {
                return true;
            }
            return false;
        }

        public GestureInfo GetGestureInfo(string gestureName)
        {
            var ret = new GestureInfo
            {
                HumanId = -1,
                Active = false,
                Confidence = 0,
                Name = gestureName
            };
            var humanStr = GetContextJsonString(ContextServer, RecvTimeout, "humans");
            if (!string.IsNullOrEmpty(humanStr))
            {
                var humanArray = JArray.Parse(humanStr);
                foreach (var human in humanArray)
                {
                    if (gestureName == "HumanDetected")
                    {
                        ret.HumanId = human.Value<int>("Id");
                        ret.Active = true;
                        ret.Confidence = 91;
                        break;
                    }

                    var gestures = human.SelectToken("$.Gestures");
                    foreach (var gesture in gestures)
                    {
                        string name = gesture.Value<string>("Name");
                        if (name != gestureName)
                        {
                            continue;
                        }
                        ret.HumanId = human.Value<int>("Id");
                        ret.Active = gesture.Value<bool>("Active");
                        ret.Confidence = gesture.Value<int>("Confidence");
                    }
                }
            }
            //Console.WriteLine(@"GetGestureInfo : {0}, Confidence : {1}", gestureName, ret.Confidence);
            return ret;
        }

        public List<GestureInfo> GetGestureInfoList(string gestureName)
        {
            var ret = new List<GestureInfo>();
            var humanStr = GetContextJsonString(ContextServer, RecvTimeout, "humans");
            if (!string.IsNullOrEmpty(humanStr))
            {
                var humanArray = JArray.Parse(humanStr);
                foreach (var human in humanArray)
                {
                    if (gestureName == "HumanDetected")
                    {
                        ret.Add(new GestureInfo
                        {
                            Name = gestureName,
                            HumanId = human.Value<int>("Id"),
                            Active = true,
                            Confidence = 91
                        });
                        break;
                    }
                    var gestures = human.SelectToken("$.Gestures");
                    foreach (var gesture in gestures)
                    {
                        string name = gesture.Value<string>("Name");
                        if (name != gestureName)
                        {
                            continue;
                        }
                        ret.Add(new GestureInfo
                        {
                            Name = gestureName,
                            HumanId = human.Value<int>("Id"),
                            Active = gesture.Value<bool>("Active"),
                            Confidence = gesture.Value<int>("Confidence")
                        });
                    }
                }
            }
            //Console.WriteLine(@"GetGestureInfo : {0}, Confidence : {1}", gestureName, ret.Confidence);
            return ret;
        }

        public VoiceCommandInfo GetVoiceCommand(string voiceCommand)
        {
            var ret = new VoiceCommandInfo
            {
                Active = false,
                Confidence = 0,
                Name = voiceCommand
            };
            var voiceCommandStr = GetContextJsonString(ContextServer, RecvTimeout, "voice_command");
            if (!string.IsNullOrEmpty(voiceCommandStr))
            {
                var voiceCommandObj = JObject.Parse(voiceCommandStr);
                if (voiceCommandObj != null)
                {
                    var current = voiceCommandObj.SelectToken("$.Current");
                    if (current != null && current.HasValues)
                    {
                        var command = current.Value<string>("Command");
                        var confidence = current.Value<int>("Confidence");
                        var triggerAt = current.Value<DateTime>("TriggerAt");
                        var now = DateTime.Now;
                        var span = now - triggerAt;
                        if (span > new TimeSpan(0, 0, 0, 0, SpeechDuration))
                        {
                        }
                        else
                        {
                            if (String.Compare(command, voiceCommand, StringComparison.OrdinalIgnoreCase) == 0)
                            {
                                ret.Active = true;
                                ret.Confidence = confidence;
                            }
                        }
                    }
                }
            }
            return ret;
        }

        public VoiceCommandInfo GetVoiceCommand()
        {
            var ret = new VoiceCommandInfo
            {
                Active = false,
                Confidence = 0
            };
            var voiceCommandStr = GetContextJsonString(ContextServer, RecvTimeout, "voice_command");
            if (!string.IsNullOrEmpty(voiceCommandStr))
            {
                var voiceCommandObj = JObject.Parse(voiceCommandStr);
                if (voiceCommandObj != null)
                {
                    var current = voiceCommandObj.SelectToken("$.Current");
                    if (current != null && current.HasValues)
                    {
                        var command = current.Value<string>("Command");
                        var active = current.Value<bool>("Active");
                        var confidence = current.Value<int>("Confidence");
                        var triggerAt = current.Value<DateTime>("TriggerAt");
                        var now = DateTime.Now;
                        var span = now - triggerAt;
                        if (span > new TimeSpan(0, 0, 0, 1))
                        {
                        }
                        else
                        {
                            ret.Active = active;
                            ret.Confidence = confidence;
                            ret.Name = command;
                            //if (String.Compare(command, voiceCommand, StringComparison.OrdinalIgnoreCase) == 0)
                            //{
                            //    ret.Active = true;
                            //    ret.Confidence = confidence;
                            //}
                        }
                    }
                }
            }
            return ret;
        }

        public bool RefreshApproachParameters(BehaviorInfo behaviorInfo, TriggerResult trigger)
        {
            bool ret = false;
            if (behaviorInfo != null && trigger != null && trigger.HumanInLoop)
            {
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

                    // Get Robot String
                    var robotString = GetContextJsonString(ContextServer, RecvTimeout, "robot");

                    // Get World String
                    var worldFrame = GetContextJsonString(ContextServer, RecvTimeout, "world_frame");


                    var humanInfo = GetContextJsonString(ContextServer, RecvTimeout,
                        string.Format("human/{0}", trigger.HumanId));
                    if (isHuman > 0 && isRotation > 0)
                    {

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

                        var headingVec = new Vector2((float) Math.Cos(rWorldYaw), (float) Math.Sin(rWorldYaw));
                        // Next we would like to align the X-Axis of the robot with that of this unit vector
                        //var yUnit = Vector2.UnitY;
                        //var xUnit = Vector2.UnitX;
                        // Now we find the angle of rotation needed to do this alignment
                        //var angle = Math.Acos(Vector2.Dot(toHumanVec, yUnit));
                        var angle = GetRelativeAngle(headingVec, toHumanVec);

#if USE_YAW
                    if (rWorldYaw > 0)
                        angle += rWorldYaw;
                    else
                        angle -= rWorldYaw;
#endif
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
                        ret = true;
                    }
                    else if (isHuman > 0 && isTranslation > 0)
                    {
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
                            float.TryParse(distDict.TryGetAndReturn("value").ToString(),
                                out threshold);
                        }

                        var residual = 0.0f;
                        if (distance > threshold)
                        {
                            residual = distance - threshold;

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
                                yDict["value"] = 0.0f;
                            }
                            if (thetaDict != null)
                            {
                                thetaDict["value"] = 0.0f;
                            }
                            ret = true;
                        }
                    }
                }
            }
            return ret;
        }

        public void DisplayRobotPose()
        {

            // Get Robot String
            var robotString = GetContextJsonString(ContextServer, RecvTimeout, "robot");

            // Get World String
            var worldFrame = GetContextJsonString(ContextServer, RecvTimeout, "world_frame");


            Matrix3x3 robotRot;
            Matrix3x3 worldRot;

            Quaternion robotQ;
            Quaternion worldQ;

            Vector3 robotTrans;
            Vector3 worldTrans;

            // Get the transformation from the JSON strings
            GetLocalizationFromRobotJson(robotString, out robotTrans, out robotRot,
                out robotQ);
            GetWorldFrameMatrix(worldFrame, out worldTrans, out worldRot, out worldQ);

            var worldMat = GetMatrixFromPose(worldQ, new Vector3(0, 0, 0));
            var robotMat = GetMatrixFromPose(robotQ, new Vector3(0, 0, 0));

            worldMat.Invert();
            var hRobot = worldMat*robotMat;

            var rWorldQ = Quaternion.RotationMatrix(hRobot);

            var rWorldYaw = GetHeading(rWorldQ);

            // Compute the displacement of Robot and Human wrt to world frame
            worldRot.Invert();


            var rDisp =
                new Vector3(Vector3.Dot(worldRot.Column1, robotTrans),
                    Vector3.Dot(worldRot.Column2, robotTrans),
                    Vector3.Dot(worldRot.Column3, robotTrans)) -
                new Vector3(Vector3.Dot(worldRot.Column1, worldTrans),
                    Vector3.Dot(worldRot.Column2, worldTrans),
                    Vector3.Dot(worldRot.Column3, worldTrans));

            Log.InfoFormat("X:{0}, Y:{1}, Theta:{2}", rDisp.X, rDisp.Y, rWorldYaw);
        }

        public bool CancelRequest
        {
            get
            {
                bool ret;
                lock (_object)
                {
                    ret = _cancelRequest;
                }
                return ret;
            }
            set
            {
                lock (_object)
                {
                    _cancelRequest = value;
                }
            }
        }

        public static Matrix GetMatrixFromPose(Quaternion q, Vector3 t)
        {
            Matrix m = Matrix.RotationQuaternion(q);
            m.TranslationVector = t;
            return m;
        }

        public static float GetHeading(Quaternion q)
        {
            //var yaw = Math.Atan2(2.0*(q.Y*q.Z + q.W*q.X),
            //    q.W*q.W - q.X*q.X - q.Y*q.Y + q.Z*q.Z);
            var yaw = Math.Atan2(2.0 * (q.Y * q.W - q.X * q.Z),
                1 - 2 * q.Y * q.Y - 2 * q.Z * q.Z);
            return (float)yaw;
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
            if (angle > Math.PI) angle -= Math.PI * 2;
            if (angle < -Math.PI) angle += Math.PI * 2;
            return angle;
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
                translation.X = pos.Value<float>("x") / 1000;
                translation.Y = pos.Value<float>("y") / 1000;
                translation.Z = pos.Value<float>("z") / 1000;
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
                translation.X = pos.Value<float>("x") / 1000;
                translation.Y = pos.Value<float>("y") / 1000;
                translation.Z = pos.Value<float>("z") / 1000;
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

        public static void GetHumanPoseFromJson(string humanInfo, out Vector3 translation, out Matrix3x3 rotation,
            out Quaternion q)
        {
            var jObj = JObject.Parse(humanInfo);
            GetHumanPoseFromJson(jObj, out translation, out rotation, out q);
        }

        public static void GetHumanPoseFromJson(JToken jObj, out Vector3 translation, out Matrix3x3 rotation, out Quaternion q)
        {
            translation = new Vector3(0, 0, 0);
            rotation = Matrix3x3.Identity;
            q = Quaternion.Identity;

            if (jObj != null)
            {
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
        }
    }
}