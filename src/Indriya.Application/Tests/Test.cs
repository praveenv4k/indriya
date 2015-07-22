using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Common.Logging;
using Experimot.Core;
using Experimot.Core.Util;
using Experimot.Scheduler.Data;
using Indriya.Core.BehaviorEngine;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using SharpDX;
// ReSharper disable FunctionComplexityOverflow
// ReSharper disable once LoopCanBeConvertedToQuery
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
                    var token2 = obj.SelectToken("$.parameters");
                    if (token2 != null)
                    {

                    }
                    var token = obj.SelectToken("$.parameters[?(@.key == 'ApplicationName')]");
                    if (token != null)
                    {
                        Log.InfoFormat("Value : {0}", token.Value<string>("value"));

                    }
                }
            }
        }

        public static void MultihumanGestureTest()
        {
            var list = GetGestureInfoList("Greet_Left");
            var first = list.FirstOrDefault(s => s.Confidence > 80);
            Console.WriteLine(first.HumanId);
        }

        public static List<GestureInfo> GetGestureInfoList(string gestureName)
        {
            var ret = new List<GestureInfo>();
            var humanStr = File.ReadAllText("humans.json");
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

        public static void ExecuteParallel()
        {
            var list = new List<Task>();
            int a = 10, b = 20;
            Action<int, int> taskAction1 = delegate(int a1, int b1)
            {
                Console.WriteLine(@"StartTask1 : {0}", DateTime.Now);
                System.Threading.Thread.Sleep(2000);
                Console.WriteLine(@"EndTask1 : {0}", DateTime.Now);
                Console.WriteLine(@"{0}, {1}", a1, b1);
            };
            Action<int, int> taskAction2 = delegate(int a1, int b1)
            {
                Console.WriteLine(@"StartTask2: {0}", DateTime.Now);
                System.Threading.Thread.Sleep(5000);
                Console.WriteLine(@"EndTask2: {0}", DateTime.Now);
                Console.WriteLine(@"{0}, {1}", a1, b1);
            };
            Action taskAction3 = delegate
            {
                Console.WriteLine(@"StartTask2: {0}", DateTime.Now);
                System.Threading.Thread.Sleep(5000);
                Console.WriteLine(@"EndTask2: {0}", DateTime.Now);
            };

            Action taskAction4 = delegate
            {
                Console.WriteLine(@"StartTask2: {0}", DateTime.Now);
                System.Threading.Thread.Sleep(5000);
                Console.WriteLine(@"EndTask2: {0}", DateTime.Now);
            };

            list.Add(Task.Factory.StartNew(() => taskAction1(a, b)));
            list.Add(Task.Factory.StartNew(() => taskAction2(a, b)));
            list.Add(Task.Factory.StartNew(() => taskAction3));
            list.Add(Task.Factory.StartNew(() => taskAction4));
            Task.WaitAll(list.ToArray());
        }

        public static void TestVoiceCommandJson()
        {
            var vcm = new VoiceCommandManager();
            var voiceCommandStr = JsonConvert.SerializeObject(vcm);
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
                        Console.WriteLine(@"Confidence : {0}, Triggerat : {1}", confidence, triggerAt);
                        if (String.Compare(command, "", StringComparison.OrdinalIgnoreCase) == 0)
                        {
                            
                        }
                    }
                }
            }
        }

        public static void CheckRelativeAngle()
        {
            Vector2 v1 = new Vector2(-0.05f,0.86f);
            Vector2 v2 = new Vector2(-0.7f, 1f);
            var angle = BehaviorExecutionContext.GetRelativeAngle(v1, v2);
            Console.WriteLine(@"Relative Angle : {0}",angle);
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
            var world = new Quaternion
            {
                X = 0.496099710464478f,
                Y = -0.641970217227936f,
                Z = -0.461962938308716f,
                W = -0.358258932828903f
            };

            var robot = new Quaternion
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

            //var humanRot =  Matrix3x3.RotationQuaternion(q);
            var worldRot =  Matrix3x3.RotationQuaternion(world);
            //var robotRot = Matrix3x3.RotationQuaternion(robot);

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
            var yUnit = Vector2.UnitX;
            // Now we find the angle of rotation needed to do this alignment
            var angle = Math.Acos(Vector2.Dot(toHumanVec,Vector2.UnitY));
            angle = MotionBehaviorTask.AngleBetween(xUnit, toHumanVec);
            angle = MotionBehaviorTask.AngleBetween(Vector2.UnitY, toHumanVec);

            var relAngle = MotionBehaviorTask.GetRelativeAngle(yUnit, toHumanVec);


            Console.WriteLine(@"Robot: {0}, Human: {1}, Angle: {2}, Relative Angle: {3}", rDisp, hDisp,
                MathUtil.RadiansToDegrees((float)angle), MathUtil.RadiansToDegrees((float)relAngle));

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
                var behaviors = MainProgramUtil.ReadBehaviorXmlFile(Path.Combine(outputPath, "behavior.xml"));
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
                                    Console.WriteLine(@"Value : {0}", cloned.Parameters[key]);
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

        public static void TestReadSkeletonFile()
        {
            var path = @"C:\Work\Develop\sdk_2013\experimot\bin\nodes\Experimot.Localization.Logger\skeleton3.bin";
            var skeleton = IoUtils.ReadSkeletonBinFile(path);

            if (skeleton.Body.Count > 0)
            {
                var list = new List<object>();
                list.AddRange(skeleton.Body);
                Console.WriteLine(JsonConvert.SerializeObject(list));   
            }
        }

        //public static void ParseSkeletonString()
        //{
        //    string skeleton =
        //        "[{\"TrackingId\":0,\"IsTracked\":true,\"JointCount\":25,\"Joints\":[{\"Type\":0,\"State\":2,\"Position\":{\"x\":0.1249847337603569,\"y\":-0.11825757473707199,\"z\":2.0625252723693848},\"Orientation\":{\"x\":-0.0074656009674072266,\"y\":0.994424045085907,\"z\":-0.097892805933952332,\"w\":-0.038496285676956177},\"Angle\":-1000.0},{\"Type\":1,\"State\":2,\"Position\":{\"x\":0.11765184998512268,\"y\":0.203008234500885,\"z\":1.9989355802536011},\"Orientation\":{\"x\":-0.00657985545694828,\"y\":0.99403524398803711,\"z\":-0.0979563295841217,\"w\":-0.047489270567893982},\"Angle\":-1000.0},{\"Type\":2,\"State\":2,\"Position\":{\"x\":0.10996883362531662,\"y\":0.51213032007217407,\"z\":1.9208577871322632},\"Orientation\":{\"x\":-0.0050320285372436047,\"y\":0.988418698310852,\"z\":-0.14094266295433044,\"w\":-0.05602056160569191},\"Angle\":-1000.0},{\"Type\":3,\"State\":2,\"Position\":{\"x\":0.11100767552852631,\"y\":0.65268588066101074,\"z\":1.8685903549194336},\"Orientation\":{\"x\":0.0,\"y\":0.0,\"z\":0.0,\"w\":0.0},\"Angle\":-1000.0},{\"Type\":4,\"State\":2,\"Position\":{\"x\":-0.072081379592418671,\"y\":0.4020199179649353,\"z\":1.9540755748748779},\"Orientation\":{\"x\":0.7670518159866333,\"y\":-0.632301926612854,\"z\":0.061224404722452164,\"w\":0.089873649179935455},\"Angle\":-1000.0},{\"Type\":5,\"State\":2,\"Position\":{\"x\":-0.12330306321382523,\"y\":0.11945255100727081,\"z\":2.05051851272583},\"Orientation\":{\"x\":0.73542362451553345,\"y\":-0.17178833484649658,\"z\":-0.65233117341995239,\"w\":0.064069680869579315},\"Angle\":-1000.0},{\"Type\":6,\"State\":2,\"Position\":{\"x\":-0.15616711974143982,\"y\":-0.12857961654663086,\"z\":2.0507967472076416},\"Orientation\":{\"x\":0.92765551805496216,\"y\":-0.060984104871749878,\"z\":0.36759054660797119,\"w\":0.024764804169535637},\"Angle\":-1000.0},{\"Type\":7,\"State\":2,\"Position\":{\"x\":-0.1523086279630661,\"y\":-0.21819016337394714,\"z\":2.0551552772521973},\"Orientation\":{\"x\":0.92823714017868042,\"y\":0.028965773060917854,\"z\":0.37057283520698547,\"w\":0.014580557122826576},\"Angle\":-1000.0},{\"Type\":8,\"State\":2,\"Position\":{\"x\":0.27921488881111145,\"y\":0.37990257143974304,\"z\":1.9194412231445313},\"Orientation\":{\"x\":0.79949504137039185,\"y\":0.58344054222106934,\"z\":-0.14125023782253265,\"w\":0.021289864555001259},\"Angle\":-1000.0},{\"Type\":9,\"State\":2,\"Position\":{\"x\":0.3518061637878418,\"y\":0.11258499324321747,\"z\":1.994931697845459},\"Orientation\":{\"x\":0.90514588356018066,\"y\":0.17058581113815308,\"z\":0.38243570923805237,\"w\":0.073172867298126221},\"Angle\":-1000.0},{\"Type\":10,\"State\":2,\"Position\":{\"x\":0.38414722681045532,\"y\":-0.14147576689720154,\"z\":2.028949499130249},\"Orientation\":{\"x\":0.82764512300491333,\"y\":0.015472088009119034,\"z\":-0.55378943681716919,\"w\":0.089896410703659058},\"Angle\":-1000.0},{\"Type\":11,\"State\":2,\"Position\":{\"x\":0.39050894975662231,\"y\":-0.23987813293933868,\"z\":2.0402326583862305},\"Orientation\":{\"x\":0.82969772815704346,\"y\":-0.00494163203984499,\"z\":-0.55436939001083374,\"w\":0.06520678848028183},\"Angle\":-1000.0},{\"Type\":12,\"State\":2,\"Position\":{\"x\":0.042388316243886948,\"y\":-0.11569768190383911,\"z\":2.0310888290405273},\"Orientation\":{\"x\":-0.67155742645263672,\"y\":0.71412324905395508,\"z\":-0.18583275377750397,\"w\":0.0671171322464943},\"Angle\":-1000.0},{\"Type\":13,\"State\":2,\"Position\":{\"x\":0.016902543604373932,\"y\":-0.54638540744781494,\"z\":2.1400647163391113},\"Orientation\":{\"x\":-0.67750316858291626,\"y\":0.10988163203001022,\"z\":0.72451204061508179,\"w\":-0.063227236270904541},\"Angle\":-1000.0},{\"Type\":14,\"State\":2,\"Position\":{\"x\":0.019744889810681343,\"y\":-0.94153130054473877,\"z\":2.2733347415924072},\"Orientation\":{\"x\":-0.47902095317840576,\"y\":0.13989044725894928,\"z\":0.86273252964019775,\"w\":-0.081622451543807983},\"Angle\":-1000.0},{\"Type\":15,\"State\":2,\"Position\":{\"x\":-0.030965633690357208,\"y\":-1.002164363861084,\"z\":2.2072350978851318},\"Orientation\":{\"x\":0.0,\"y\":0.0,\"z\":0.0,\"w\":0.0},\"Angle\":-1000.0},{\"Type\":16,\"State\":2,\"Position\":{\"x\":0.20302265882492065,\"y\":-0.11659203469753265,\"z\":2.0189299583435059},\"Orientation\":{\"x\":0.65893334150314331,\"y\":0.704171359539032,\"z\":-0.23768116533756256,\"w\":-0.11600561439990997},\"Angle\":-1000.0},{\"Type\":17,\"State\":2,\"Position\":{\"x\":0.23478332161903381,\"y\":-0.54882222414016724,\"z\":2.1385741233825684},\"Orientation\":{\"x\":0.72868585586547852,\"y\":0.11722782999277115,\"z\":0.67059111595153809,\"w\":0.074712879955768585},\"Angle\":-1000.0},{\"Type\":18,\"State\":2,\"Position\":{\"x\":0.24888120591640472,\"y\":-0.9450414776802063,\"z\":2.2931602001190186},\"Orientation\":{\"x\":0.6585991382598877,\"y\":0.14848074316978455,\"z\":0.72924256324768066,\"w\":0.11138219386339188},\"Angle\":-1000.0},{\"Type\":19,\"State\":2,\"Position\":{\"x\":0.26045051217079163,\"y\":-1.0068831443786621,\"z\":2.2119810581207275},\"Orientation\":{\"x\":0.0,\"y\":0.0,\"z\":0.0,\"w\":0.0},\"Angle\":-1000.0},{\"Type\":20,\"State\":2,\"Position\":{\"x\":0.11199373751878738,\"y\":0.436588853597641,\"z\":1.9427328109741211},\"Orientation\":{\"x\":-0.0051533849909901619,\"y\":0.9913705587387085,\"z\":-0.11824706941843033,\"w\":-0.056351780891418457},\"Angle\":-1000.0},{\"Type\":21,\"State\":2,\"Position\":{\"x\":-0.15046697854995728,\"y\":-0.31152123212814331,\"z\":2.0728788375854492},\"Orientation\":{\"x\":0.0,\"y\":0.0,\"z\":0.0,\"w\":0.0},\"Angle\":-1000.0},{\"Type\":22,\"State\":2,\"Position\":{\"x\":-0.11904703080654144,\"y\":-0.25189891457557678,\"z\":2.0134797096252441},\"Orientation\":{\"x\":0.0,\"y\":0.0,\"z\":0.0,\"w\":0.0},\"Angle\":-1000.0},{\"Type\":23,\"State\":2,\"Position\":{\"x\":0.3890744149684906,\"y\":-0.32848110795021057,\"z\":2.0569159984588623},\"Orientation\":{\"x\":0.0,\"y\":0.0,\"z\":0.0,\"w\":0.0},\"Angle\":-1000.0},{\"Type\":24,\"State\":2,\"Position\":{\"x\":0.35649600625038147,\"y\":-0.27371099591255188,\"z\":2.019277811050415},\"Orientation\":{\"x\":0.0,\"y\":0.0,\"z\":0.0,\"w\":0.0},\"Angle\":-1000.0}],\"ClippedEdges\":0,\"HandLeftConfidence\":0,\"HandLeftState\":0,\"HandRightConfidence\":0,\"HandRightState\":0,\"IsRestricted\":false,\"Lean\":null,\"LeanTrackingState\":0}]";
        //}

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
            var lines = File.ReadAllLines(@"datalog.csv");
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
