#load "BehaviorInfo"
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
										
if(Env.ScriptArgs.Count <=0)
{
	Console.WriteLine("Need parameter server info!");
}
else
{
	var name = Env.ScriptArgs[0];
	var context_server = Env.ScriptArgs[1];
	var resp = MainProgramUtil.GetNodeInfo("node_"+name,context_server);
	Console.WriteLine(resp);

	var dict = new Dictionary<string,object>();
	dict.Add("ContextServer",context_server);

	var gestBehaviorMap = new Dictionary<string,string>();
	<% MODIFY_HERE %>

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