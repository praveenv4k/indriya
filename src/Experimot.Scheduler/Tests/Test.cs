using System;
using System.Collections.Generic;
using Common.Logging;
using Experimot.Core;
using Experimot.Core.Util;
using Experimot.Scheduler.Scriptcs;
using Newtonsoft.Json.Linq;

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
    }
}
