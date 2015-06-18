using System;
using System.Collections.Generic;
using Common.Logging;
using NetMQ;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using SharpDX;

// ReSharper disable once CheckNamespace
public class BehaviorExecutionContext : IBehaviorExecutionContext
{
    private static readonly ILog Log = LogManager.GetLogger(typeof(BehaviorExecutionContext));
    private const int RecvTimeout = 200;

    public string ContextServer { get; set; }

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
                            if (info.BehaviorName == name)
                            {
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

    public void SyncExecuteBehavior(BehaviorInfo behaviorInfo)
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
                    if (span > new TimeSpan(0, 0, 0, 1))
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