using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Windows.Navigation;
using System.Xml.Linq;
using Common.Logging;
using Experimot.Core;
using Experimot.Core.Util;
using Experimot.Scheduler.Data;
using Experimot.Scheduler.Scriptcs;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Quartz.Util;
using SharpDX;

namespace Experimot.Scheduler.Tests
{
    internal class Test
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof (Test));

        public static void TestJson(string str)
        {
            const string humanStr =
                "[{\"Id\":2,\"HeadPosition\":null,\"TorsoPosition\":null,\"TorsoOrientation\":null,\"Gestures\":[{\"Name\":\"Greet_Left\",\"Mode\":1,\"Active\":false,\"Progress\":0,\"Confidence\":0,\"Count\":0},{\"Name\":\"Greet_Right\",\"Mode\":1,\"Active\":false,\"Progress\":0,\"Confidence\":0,\"Count\":0}]}]";
            JArray humanArray = JArray.Parse(humanStr);
            if (humanArray != null && humanArray.Count > 0)
            {
                foreach (var human in humanArray)
                {
                    var gestures = human.SelectToken("$.Gestures");
                    foreach (var gesture in gestures)
                    {
                        string name = gesture.Value<string>("Name");
                        bool active = gesture.Value<bool>("Active");
                        int confidence = gesture.Value<int>("Confidence");
                        Log.InfoFormat(@"Name : {0}, Active : {1}, Confidence: {2}", name, active, confidence);
                    }
                }
            }
            const string behaviorStr =
                "[{\"name\":\"nao_behavior_manager\",\"param\":[],\"behaviors\":[{\"name\":\"crouch\",\"type\":0,\"state\":0},{\"name\":\"stand\",\"type\":0,\"state\":0},{\"name\":\"wave\",\"type\":0,\"state\":0},{\"name\":\"greet\",\"type\":0,\"state\":0}],\"responder\":{\"Host\":\"tcp://localhost\",\"Port\":5590}}]";
            JArray behaviorArray = JArray.Parse(behaviorStr);
            if (behaviorArray != null && behaviorArray.Count > 0)
            {
                foreach (var module in behaviorArray)
                {
                    //var moduleName = module.Value<string>("name");
                    var behaviors = module.SelectToken("$.behaviors");
                    foreach (var behavior in behaviors)
                    {
                        string name = behavior.Value<string>("name");
                        int type = behavior.Value<int>("type");
                        int state = behavior.Value<int>("state");
                        Log.InfoFormat(@"Name : {0}, Active : {1}, Confidence: {2}", name, type, state);
                    }
                    var responder = module.SelectToken("$.responder");
                    if (responder != null)
                    {
                        string host = responder.Value<string>("Host");
                        int port = responder.Value<int>("Port");
                        Log.InfoFormat(@"Host : {0}, Port : {1}", host, port);
                    }
                }
            }
            if (!string.IsNullOrEmpty(str))
            {
                var obj = JObject.Parse(str);
                if (obj != null)
                {
                    Log.InfoFormat("Json object count : {0}", obj.Count);
                    var token2 = obj.SelectToken("$.parameters"); //$.Manufacturers[?(@.Name == 'Acme Co')]
                    if (token2 != null)
                    {

                    }
                    var token = obj.SelectToken("$.parameters[?(@.key == 'ApplicationName')]");
                    //$.Manufacturers[?(@.Name == 'Acme Co')]
                    if (token != null)
                    {
                        Log.InfoFormat("Value : {0}", token.Value<string>("value"));

                    }
                }
            }
        }

        public static void GestureConfidenceDataIterate()
        {
            var gesture = new Gesture("test", GestureMode.Discrete);
            var str = JsonConvert.SerializeObject(gesture);
            if (!string.IsNullOrEmpty(str))
            {
                JObject obj = JObject.Parse(str);
                if (obj != null)
                {
                    JToken token = obj.SelectToken("$.ConfidenceDict");
                    foreach (var item in token)
                    {
                        if (item.HasValues)
                        {
                            var level = item.First.Value<int>("Level");

                            Console.WriteLine(level);
                        }
                    }
                    //if (token != null)
                    //{
                    //    //token.Where()
                    //}
                }
            }
        }

        public static void TestProgramGeneration(experimot_config config)
        {
            var outputPath = ParameterUtil.Get(config.parameters, "MainProgramFilePath", "");
            if (!string.IsNullOrEmpty(outputPath))
            {
                outputPath = Environment.ExpandEnvironmentVariables(outputPath);
                var dict = new Dictionary<string, string> {{"Greet_Left", "wave"}};
                ProgramGenerator.GeneratePrograms(dict, outputPath);
            }
        }

        public static void TestSharpDxMatrixRotation()
        {
            // Human Torso
            // 0.4264857172966,0.482540011405945,2.79593229293823,-0.436887833085438,0.553701125621802,0.36664267310498,0.606726655954306
            var q = new Quaternion
            {
                W = 0.606726655954306f,
                X = -0.436887833085438f,
                Y = 0.553701125621802f,
                Z = 0.36664267310498f
            };
            //-0.418618727	0.403053236	0.350150562	0.734643474
            //world_frame_kinect,0,251.437573434929,-735.386669475668,2164.29300194067,0.496099710464478,-0.641970217227936,-0.461962938308716,-0.358258932828903
            //torso_frame_kinect,0,-162.226432126277,-510.568576421518,2058.52739944453,-0.725971817970276,0.322613894939423,0.246974587440491,0.554877161979675
            //torso_frame_world,0,131.927854697293,393.702612672757,245.855610297709,-0.00544274205055237,0.0278509132097885,0.473493447583182,-0.880340081041494
            //world_frame,0,0,0,0,0,0,0,1
            var world = new Quaternion()
            {
                X = 0.496099710464478f,
                Y = -0.641970217227936f,
                Z = -0.461962938308716f,
                W = -0.358258932828903f
            };

            var robot = new Quaternion()
            {
                X = -0.725971817970276f,
                Y = 0.322613894939423f,
                Z = 0.246974587440491f,
                W = 0.554877161979675f
            };

            
            var humanmat = MotionBehaviorTask.GetMatrixFromPose(q,
                new Vector3(0,0,0));
            var worldMat = MotionBehaviorTask.GetMatrixFromPose(world,
                new Vector3(0, 0, 0));
            var robotMat = MotionBehaviorTask.GetMatrixFromPose(robot,
                new Vector3(0, 0, 0));

            var humanRot =  Matrix3x3.RotationQuaternion(q);
            var worldRot =  Matrix3x3.RotationQuaternion(world);
            var robotRot = Matrix3x3.RotationQuaternion(robot);

            var humanVec = 
                new Vector3(0.4264857172966f, 0.482540011405945f, 2.79593229293823f);
            var worldVec = 
                new Vector3(0.251437573434929f, -0.735386669475668f, 2.16429300194067f);
            var robotVec = 
                new Vector3(-0.162226432126277f, -0.510568576421518f, 2.05852739944453f);

            worldRot.Invert();

            var hDisp =
                new Vector3(Vector3.Dot(worldRot.Column1, humanVec), Vector3.Dot(worldRot.Column2, humanVec),
                    Vector3.Dot(worldRot.Column3, humanVec)) -
                new Vector3(Vector3.Dot(worldRot.Column1, worldVec), Vector3.Dot(worldRot.Column2, worldVec),
                    Vector3.Dot(worldRot.Column3, worldVec));

            var rDisp =
                new Vector3(Vector3.Dot(worldRot.Column1, robotVec), Vector3.Dot(worldRot.Column2, robotVec),
                    Vector3.Dot(worldRot.Column3, robotVec)) -
                new Vector3(Vector3.Dot(worldRot.Column1, worldVec), Vector3.Dot(worldRot.Column2, worldVec),
                    Vector3.Dot(worldRot.Column3, worldVec));

            // We get the unit vector from Robot pointing towards human
            var toHumanVec = new Vector2(hDisp.X, hDisp.Y) - new Vector2(rDisp.X, rDisp.Y);
            toHumanVec.Normalize();
            // Next we would like to align the X-Axis of the robot with that of this unit vector
            var xUnit = Vector2.UnitX;
            // Now we find the angle of rotation needed to do this alignment
            var angle = Math.Acos(Vector2.Dot(toHumanVec,Vector2.UnitY));


            Console.WriteLine(@"Robot: {0}, Human: {1}, Angle: {2}", rDisp, hDisp,
                MathUtil.RadiansToDegrees((float) angle));

            worldMat.Invert();
            var hWorld = worldMat*humanmat;
            var hRobot = worldMat*robotMat;

            var hWorldQ = Quaternion.RotationMatrix(hWorld);
            var hRobotQ = Quaternion.RotationMatrix(hRobot);

            var hWorldYaw = GetHeading(hWorldQ);
            var hRobotYaw = GetHeading(hRobotQ);
            //Console.WriteLine(@"Torso Mat : {0}", string.Join(", ", mat.ToArray()));
            //Console.WriteLine(@"World Mat : {0}", string.Join(", ", world_mat.ToArray()));
            //Console.WriteLine(@"Human wrt World : {0}", string.Join(", ", hWorld.ToArray()));
            Console.WriteLine(@"Human Torso Mat : {0}", humanmat);
            Console.WriteLine(@"Robot Torso Mat : {0}", robotMat);
            Console.WriteLine(@"World Frame wrt kinect Mat : {0}", worldMat);
            Console.WriteLine(@"Human wrt World : {0}, ZAngle:{3}, Axis: {1}, Angle: {2}", hWorld, hWorldQ.Axis,
                hWorldQ.Angle, MathUtil.RadiansToDegrees(hWorldYaw));
            Console.WriteLine(@"Robot wrt World : {0}, ZAngle:{3}, Axis: {1}, Angle: {2}", hRobot, hRobotQ.Axis,
                hRobotQ.Angle, MathUtil.RadiansToDegrees(hRobotYaw));

            var humanTrans = MotionBehaviorTask.GetMatrixFromPose(Quaternion.Identity,
                new Vector3(0.4264857172966f, 0.482540011405945f, 2.79593229293823f));
            var worldTrans = MotionBehaviorTask.GetMatrixFromPose(Quaternion.Identity,
                new Vector3(0.251437573434929f, -0.735386669475668f, 2.16429300194067f));
            var robotTrans = MotionBehaviorTask.GetMatrixFromPose(Quaternion.Identity,
                new Vector3(-0.162226432126277f, -0.510568576421518f, 2.05852739944453f));

            worldTrans.Invert();
            hWorld.Invert();
            hRobot.Invert();
            var hTrans = hWorld*humanTrans;
            var rTrans = hRobot*robotTrans;

            Console.Write(@"Human : {0}, Robot: {1}", hTrans.TranslationVector, rTrans.TranslationVector);
            // 2D transform matrix
            //var hTransWorld = 
        }

        public static float GetHeading(Quaternion q)
        {
            //var yaw = Math.Atan2(2.0*(q.Y*q.Z + q.W*q.X),
            //    q.W*q.W - q.X*q.X - q.Y*q.Y + q.Z*q.Z);
            var yaw = Math.Atan2(2.0*(q.Y*q.W - q.X*q.Z),
                1 - 2*q.Y*q.Y - 2*q.Z*q.Z);
            return (float)yaw;
        }

        public static void TestReadBehaviorXml(experimot_config config)
        {
            var outputPath = ParameterUtil.Get(config.parameters, "MainProgramFilePath", "");
            if (!string.IsNullOrEmpty(outputPath))
            {
                var dir = Path.GetDirectoryName(outputPath);
                outputPath = Environment.ExpandEnvironmentVariables(dir ?? "");
                var behaviors = MainProgramUtil.ReadBehaviorXmlFile(System.IO.Path.Combine(outputPath, "behavior.xml"));
                Console.WriteLine(@"Behaviors  : {0}", behaviors.Count);
                if (behaviors.Count > 0)
                {
                    var motionBehavior = behaviors[0];
                    if (motionBehavior.RobotActions.Count > 0)
                    {
                        var behavior = motionBehavior.RobotActions[0];
                        var cloned = (BehaviorInfo)behavior.Clone();
                        if (cloned.Parameters.Count > 0)
                        {
                            string key = cloned.Parameters.Keys.FirstOrDefault();
                            if (!string.IsNullOrEmpty(key))
                            {
                                var param = cloned.Parameters[key] as Dictionary<string, object>;
                                if (param != null)
                                {
                                    param["value"] = "New value";
                                    Console.WriteLine("Value : {0}", cloned.Parameters[key]);
                                }
                            }
                        }
                    }
                }
            }
        }

        public static void TestJsonToProgram(experimot_config config)
        {
            var behaviorInfoDict = new Dictionary<string, List<BehaviorInfo>>();

            const string behavior =
                @"{ name : 'behavior', trigger : 'Greet_Left',  priority : 'high',  actions  : [{ name : 'stand' }, { name : 'greet' }, { name : 'crouch' }] }";
            var obj = JObject.Parse(behavior);
            if (obj != null)
            {
                var name = obj.Value<string>("name");
                Log.InfoFormat("Behavior Info - Name: {0}, Trigger: {1}, Priority: {2}", name,
                    obj.Value<string>("trigger"), obj.Value<string>("priority"));
                behaviorInfoDict.Add(name, new List<BehaviorInfo>());
                var actions = obj.SelectToken("$.actions"); //$.Manufacturers[?(@.Name == 'Acme Co')]
                foreach (var action in actions)
                {
                    var actionName = action.Value<string>("name");
                    behaviorInfoDict[name].Add(new BehaviorInfo()
                    {
                        BehaviorName = actionName
                    });
                    Log.InfoFormat("Action Info - Name: {0}", actionName);
                }
            }
            Log.InfoFormat("Dictionary constructed: {0}", behaviorInfoDict.Count);
            var outputPath = ParameterUtil.Get(config.parameters, "MainProgramFilePath", "");
            if (!string.IsNullOrEmpty(outputPath))
            {
                outputPath = Environment.ExpandEnvironmentVariables(outputPath);
                ProgramGenerator.GeneratePrograms(behavior, outputPath);
            }
        }
    }

    internal class TestJointValues
    {
        private TestJointValues()
        {
            var dict = new Dictionary<int, int>()
            {
                {0, 1},
                {1, 0},
                {2, 9},
                {3, 8},
                {4, 7},
                {5, 10},
                {6, 2},
                {7, 3},
                {8, 11},
                {9, 12},
                {10, 5},
                {11, 4},
                {12, 13},
                {13, 6},
                {14, 20},
                {15, 19},
                {16, 21},
                {17, 14},
                {18, 15},
                {19, 22},
                {20, 23},
                {21, 17},
                {22, 16},
                {23, 24},
                {24, 18},
            };
            var lines = System.IO.File.ReadAllLines(@"datalog.csv");
            var csv = lines.Select(line => line.Split(',')).ToList(); // or, List<YourClass>
            _jointList = new List<List<double>>();
            for (int i = 0; i < csv.Count; i++)
            {
                if (i == 0) continue;
                //var list = new IndexVal() {id = i + 1};
                var list = new List<double>();
                for (int j = 4; j < 29; j++)
                {
                    list.Add(double.Parse(csv[i][dict[j - 4] + 4]));
                }
                _jointList.Add(list);
            }
        }

        private static TestJointValues _instance;
        private readonly List<List<double>> _jointList;

        public static TestJointValues Instance
        {
            get { return _instance ?? (_instance = new TestJointValues()); }
        }

        public string GetJointValues(int id)
        {
            var ret = string.Empty;
            if (_jointList != null && _jointList.Count > 0 && id >= 0 && id < _jointList.Count)
            {
                ret = JsonConvert.SerializeObject(_jointList[id]);
            }
            return ret;
        }
    }
}
