#r "System.Runtime.dll"
#load "BehaviorInfo.csx"
#load "SimpleBehaviorTask.csx"
#load "MotionBehaviorTask.csx"
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
	try{
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
				Console.WriteLine(@"	-> Action Name : {0}", behaviorInfo.BehaviorName);
			}
		}

		dict.Add("BehaviorList",motionBehaviors);
		var scheduler = MainProgramUtil.GetScheduler();
		scheduler.Start();

		var main = new MainProgram(dict,scheduler);
		var tasks = new List<Task>
					{
						Task.Factory.StartNew(() => main.RunBehaviors())
					};

		Task.WaitAll(tasks.ToArray());
	}
	catch(Exception ex){
		Console.WriteLine("Exception occured : {0}", ex.StackTrace);
	}
	Console.WriteLine("Program Terminating ... ");
	Console.WriteLine("Press any key to continue ...");
	Console.ReadKey();
}