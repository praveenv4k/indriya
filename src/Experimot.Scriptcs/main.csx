using System;
using NetMQ;
using Common.Logging;
using ProtoBuf;
using System.Collections.Generic;
using System.Collections.Specialized;
using Quartz;
using Quartz.Impl;
using Quartz.Impl.Matchers;

public class SimpleTask : IJob
{
	public void Execute(IJobExecutionContext context)
	{
		if (context != null)
		{
			Console.WriteLine("Simple Task Executed!");
		}
	}
}

public class SimpleBehaviorTask : IJob
{
	private static readonly ILog Log = LogManager.GetLogger(typeof (SimpleBehaviorTask));

	public void Execute(IJobExecutionContext context)
	{
		if (context != null)
		{
			try
			{
				var ip = context.MergedJobDataMap.GetString("BehaviorServerIp");
				var port = context.MergedJobDataMap.GetIntValue("BehaviorServerPort");
				var behaviorName = context.MergedJobDataMap.GetString("BehaviorName");
				if (!string.IsNullOrEmpty(ip) && port != 0)
				{
					using (var ctx = NetMQ.NetMQContext.Create())
					{
						using (var sock = ctx.CreateRequestSocket())
						{
							var addr = string.Format("{0}:{1}", ip, port);
							Log.InfoFormat("Connecting to behavior server: {0}", addr);
							sock.Connect(addr);
							Log.InfoFormat("Connected to behavior server: {0}", addr);
							sock.Send(behaviorName);
							Log.InfoFormat("Sent behavior execution request: {0}", behaviorName);
							var reply = sock.ReceiveString();
							Log.InfoFormat("Behavior execution response: {0}", reply);
						}
					}
				}
			}
			catch (Exception ex)
			{
				Log.ErrorFormat("Simple behavior error : {0}", ex.Message);
			}
		}
	}
}
	
public class Util{
	private static readonly ILog Log = LogManager.GetLogger(typeof (Util));
	
	public static string GetNodeInfo(string name, string server, int timeout = 1000)
	{
		try
		{
			using (var context = NetMQContext.Create())
			{
				using (var socket = context.CreateRequestSocket())
				{
					socket.Connect(server);
					socket.Send(name);

					var msg = socket.ReceiveString(new TimeSpan(0, 0, 0, 0, timeout));
					if (msg != null)
					{
						return msg;
					}
					else
					{
						Console.WriteLine("Message buffer empty!");
					}
				}
			}
		}
		catch (Exception ex)
		{
			Console.WriteLine(ex.StackTrace,"Parameter retrieve");
		}
		return "";
	}
	
	public static IScheduler GetScheduler(){
		// our properties that enable XML configuration plugin
		// and makes it watch for changes every two minutes (120 seconds)
		var properties = new NameValueCollection();
		properties["quartz.plugin.triggHistory.type"] = "Quartz.Plugin.History.LoggingJobHistoryPlugin";

		//properties["quartz.plugin.jobInitializer.type"] = "Quartz.Plugin.Xml.XMLSchedulingDataProcessorPlugin";
		//properties["quartz.plugin.jobInitializer.fileNames"] = "quartz_config.xml";
		//properties["quartz.plugin.jobInitializer.failOnFileNotFound"] = "true";
		//properties["quartz.plugin.jobInitializer.scanInterval"] = "120";

		var factory = new StdSchedulerFactory(properties);
		var scheduler = factory.GetScheduler();
		
		Console.WriteLine("Scheduler created");
		
		return scheduler;
	}
}

var scheduler = Util.GetScheduler();
scheduler.Start();
var jobKey = JobKey.Create(string.Format("Task{0}", 1), "MainGroup");
IJobDetail detail = JobBuilder.Create<SimpleTask>()
							.WithIdentity(jobKey)
							.Build();

//detail.JobDataMap.Add("BehaviorServerIp", module.responder.Host);
//detail.JobDataMap.Add("BehaviorServerPort", module.responder.Port);
//detail.JobDataMap.Add("BehaviorName", "wish");
//detail.JobDataMap.Add("BehaviorName", "greet");

ITrigger trigger = TriggerBuilder.Create().ForJob(detail).StartNow().Build();
scheduler.ScheduleJob(detail, trigger);
										
if(Env.ScriptArgs.Count <=0)
{
	Console.WriteLine("Need parameter server info!");
}
else
{
	var name = Env.ScriptArgs[0];
	var context_server = Env.ScriptArgs[1];
	var resp = Util.GetNodeInfo("node_"+name,context_server);
	Console.WriteLine(resp);
}