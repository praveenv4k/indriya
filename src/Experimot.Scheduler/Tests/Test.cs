using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml.Linq;
using Common.Logging;
using Experimot.Core;
using Experimot.Core.Util;
using Experimot.Scheduler.Scriptcs;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Quartz.Util;

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


        public static void ReadBehaviorXmlFile(string xmlFile)
        {
            var root = XElement.Load(xmlFile);
            //var doc = XmlDocumentUtil.RemoveXmlns(xmlFile);

            var blocks = root.ElementsAnyNS("block");
            Console.WriteLine(@"Number of behavior blocks : {0}", blocks.Count());

            var motionBehaviorList = new List<MotionBasedBehavior>();
            foreach (var block in blocks)
            {
                var type = block.Attribute("type");
                if (type.Value == "behavior_sleek")
                {
                    var motionBehavior = new MotionBasedBehavior();
                    var fields = block.ElementsAnyNS("field");
                    foreach (var field in fields)
                    {
                        var nameAttribute = field.Attribute("name");
                        if (nameAttribute != null)
                        {
                            if (nameAttribute.Value == "behavior_name")
                            {
                                motionBehavior.Name = field.Value;
                            }
                            else if (nameAttribute.Value == "priorities")
                            {
                                BehaviorExecutionPriority priority = BehaviorExecutionPriority.normal;
                                Enum.TryParse(field.Value, out priority);
                                motionBehavior.Priority = priority;
                            }
                            else if (nameAttribute.Value == "execution")
                            {
                                BehaviorExecutionLifetime execution = BehaviorExecutionLifetime.forever;
                                Enum.TryParse(field.Value, out execution);
                                motionBehavior.ExecutionLifetime = execution;
                                if (execution == BehaviorExecutionLifetime.until)
                                {
                                    var mutationBlock = block.ElementsAnyNS("mutation").ToList();
                                    if (mutationBlock.Count > 0)
                                    {
                                        var mutation = mutationBlock[0];
                                        var runLogicAttr = mutation.Attribute("run_logic");
                                        if (runLogicAttr != null)
                                        {
                                            motionBehavior.ExecutionEvalExpression =
                                                runLogicAttr.Value;
                                        }
                                    }
                                }
                            }
                            else if (nameAttribute.Value == "triggers")
                            {
                                motionBehavior.Trigger = field.Value;
                            }
                            else if (nameAttribute.Value == "confidence_levels")
                            {
                                int confidence = 90;
                                int.TryParse(field.Value, out confidence);
                                motionBehavior.ConfidenceLevel = confidence;
                            }
                        }
                    }
                    var statements = block.ElementsAnyNS("statement").ToArray();
                    for (int s = 0; s < statements.Length; s++)
                    {
                        var currStatement = statements[s];
                        IList<BehaviorInfo> tempList = null;
                        if (currStatement.Attribute("name").Value == "INIT_DO")
                        {
                            tempList = motionBehavior.InitActions;
                        }
                        if (currStatement.Attribute("name").Value == "DO")
                        {
                            tempList = motionBehavior.RobotActions;
                        }
                        if (currStatement.Attribute("name").Value == "EXIT_DO")
                        {
                            tempList = motionBehavior.ExitActions;
                        }
                        if (tempList != null)
                        {
                            var statementBlocks = currStatement.ElementsAnyNS("block").ToArray();
                            for (int i = 0; i < statementBlocks.Length; i++)
                            {
                                var tempBlock = statementBlocks[i];
                                var behaviorInfo = GetBehaviorInfo(tempBlock);
                                if (behaviorInfo != null)
                                {
                                    tempList.Add(behaviorInfo);
                                    var nextBlock = tempBlock.ElementsAnyNS("next");
                                    while (nextBlock != null && nextBlock.Any())
                                    {
                                        var childBlock = nextBlock.ElementsAnyNS("block").FirstOrDefault();
                                        if (childBlock != null)
                                        {
                                            behaviorInfo = GetBehaviorInfo(childBlock);
                                            tempList.Add(behaviorInfo);
                                            Console.WriteLine(childBlock);
                                            nextBlock = childBlock.ElementsAnyNS("next");
                                            Console.WriteLine(nextBlock);
                                        }
                                        else
                                        {
                                            nextBlock = null;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // Check cloning
                    //var temp = motionBehavior.Clone() as MotionBasedBehavior;
                    //if (temp != null)
                    //{
                        
                    //}
                    motionBehaviorList.Add(motionBehavior);
                }
            }
        }

        public static BehaviorInfo GetBehaviorInfo(XElement behaviorBlock)
        {
            if (behaviorBlock != null)
            {
                var blockType = behaviorBlock.Attribute("type");
                if (blockType.Value == "robot_action")
                {
                    var robotActions = behaviorBlock.ElementsAnyNS("field");
                    if (robotActions != null)
                    {
                        foreach (var robotAction in robotActions)
                        {
                            var actionType = robotAction.Attribute("name");
                            if (actionType.Value == "actions")
                            {
                                return new BehaviorInfo
                                {
                                    BehaviorName = robotAction.Value
                                };
                            }
                        }
                    }
                }
            }
            return null;
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
