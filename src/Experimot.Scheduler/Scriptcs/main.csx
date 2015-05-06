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

var dict = new Dictionary<string,object>();
dict.Add("ContextServer","tcp://localhost:5800");

var gestBehaviorMap = new Dictionary<string,string>();
gestBehaviorMap.Add("Greet_Right","greet");
gestBehaviorMap.Add("Greet_Left","wish");

dict.Add("TriggerBehaviorMap",gestBehaviorMap);

var scheduler = MainProgramUtil.GetScheduler();
scheduler.Start();

var main = new MainProgram(dict,scheduler);
var tasks = new List<Task>
            {
				Task.Factory.StartNew(() => main.Run())
            };

Task.WaitAll(tasks.ToArray());

//detail.JobDataMap.Add("BehaviorServerIp", module.responder.Host);
//detail.JobDataMap.Add("BehaviorServerPort", module.responder.Port);
//detail.JobDataMap.Add("BehaviorName", "wish");
//detail.JobDataMap.Add("BehaviorName", "greet");

//ITrigger trigger = TriggerBuilder.Create().ForJob(detail).StartNow().Build();
//scheduler.ScheduleJob(detail, trigger);
										
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

	var scheduler = MainProgramUtil.GetScheduler();
	scheduler.Start();
	
	//var jobKey = JobKey.Create(string.Format("Task{0}", 1), "MainGroup");
	//IJobDetail detail = JobBuilder.Create<SimpleTask>()
	//							.WithIdentity(jobKey)
	//							.Build();

	//var tasks = new List<Task>();

}