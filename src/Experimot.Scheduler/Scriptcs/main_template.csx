#load "BehaviorInfo.csx"
#load "SimpleBehaviorTask.csx"
#load "MainProgramUtil.csx"
#load "MainProgram.csx"

using System;
using NetMQ;
using Common.Logging;
using ProtoBuf;
using System.Collections.Generic;
using System.Collections.Specialized;
using Quartz;
using Quartz.Impl;
using Quartz.Impl.Matchers;
using System.Threading.Tasks;
using Newtonsoft.Json.Linq;
						
Common.Logging.LogManager.Adapter = new Common.Logging.Simple.ConsoleOutLoggerFactoryAdapter { Level = Common.Logging.LogLevel.Info };				

if(Env.ScriptArgs.Count <=0)
{
	Console.WriteLine("Need parameter server info!");
}
else
{
	var node_name = Env.ScriptArgs[0];
	var context_server = Env.ScriptArgs[1];
	var resp = MainProgramUtil.GetNodeInfo("node_"+node_name,context_server);
	Console.WriteLine(resp);

	var dict = new Dictionary<string,object>();
	dict.Add("ContextServer",context_server);

	var motionBehaviors = MainProgramUtil.ReadBehaviorXmlFile("behavior.xml");
	foreach (var motionBehavior in motionBehaviors)
        {
            Console.WriteLine(@"Motion Behavior : {0}, Trigger : {1}, Confidence: {2}, Priority: {3}",
                motionBehavior.Name, motionBehavior.Trigger, motionBehavior.ConfidenceLevel, motionBehavior.Priority);
            foreach (var behaviorInfo in motionBehavior.RobotActions)
            {
                Console.WriteLine(@"\t -> Action Name : {0}", behaviorInfo.BehaviorName);
            }
        }

	var gestBehaviorMap = new Dictionary<string, List<BehaviorInfo>>();

	// The dynamic JSON string will be put here
	var behavior = "<% MODIFY_HERE %>";

	var obj = JObject.Parse(behavior);
	if (obj != null)
	{
		var name = obj.Value<string>("name");
		var trigger = obj.Value<string>("trigger");
		Console.WriteLine("Behavior Info - Name: {0}, Trigger: {1}, Priority: {2}", name,
			obj.Value<string>("trigger"), obj.Value<string>("priority"));
		gestBehaviorMap.Add(trigger, new List<BehaviorInfo>());
		var actions = obj.SelectToken("$.actions"); 
		foreach (var action in actions)
		{
			var actionName = action.Value<string>("name");
			gestBehaviorMap[trigger].Add(new BehaviorInfo()
			{
				BehaviorName = actionName
			});
			Console.WriteLine("Action Info - Name: {0}", actionName);
		}
	}

	dict.Add("TriggerBehaviorMap",gestBehaviorMap);

	var scheduler = MainProgramUtil.GetScheduler();
	scheduler.Start();

	var main = new MainProgram(dict,scheduler);
	var tasks = new List<Task>
				{
					Task.Factory.StartNew(() => main.Run())
				};

	Task.WaitAll(tasks.ToArray());

	Console.WriteLine(resp);
}