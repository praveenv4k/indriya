using System;
using Common.Logging;
using NetMQ;
using Newtonsoft.Json.Linq;
using SharpDX;

public class BehaviorExecutionContext : IBehaviorExecutionContext
{
    private static readonly ILog Log = LogManager.GetLogger(typeof(BehaviorInfo));

    public string ContextServer { get; set; }

    public static string GetContextJsonString(string contextServer,int timeout, string reqName)
    {
        var resp = string.Empty;
        using (var ctx = NetMQContext.Create())
        {
            using (var socket = ctx.CreateRequestSocket())
            {
                socket.Connect(contextServer);
                resp = socket.ReceiveString(new TimeSpan(0, 0, 0, 0, timeout));
            }
        }
        return resp;
    }

    public bool GetHumanExists()
    {
        var humansStr = GetContextJsonString(ContextServer, 100, "humans");
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

        var humansStr = GetContextJsonString(ContextServer, 100, "humans");
        var robotStr = GetContextJsonString(ContextServer, 100, "robot");
        var worldFrameStr = GetContextJsonString(ContextServer, 100, "world_frame");
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
        var humanStr = GetContextJsonString(ContextServer, 100, "humans");
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
        var humanStr = GetContextJsonString(ContextServer, 100, "voice_command");
        if (!string.IsNullOrEmpty(humanStr))
        {
            var humanArray = JArray.Parse(humanStr);
            foreach (var human in humanArray)
            {
                var gestures = human.SelectToken("$.Gestures");
                foreach (var gesture in gestures)
                {
                    string name = gesture.Value<string>("Name");
                    if (name != voiceCommand)
                    {
                        continue;
                    }
                    ret.Active = gesture.Value<bool>("Active");
                    ret.Confidence = gesture.Value<int>("Confidence");
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