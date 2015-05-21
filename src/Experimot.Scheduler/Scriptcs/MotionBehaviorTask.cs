using System;
using System.Collections.Generic;
using Common.Logging;
using NetMQ;

public class MotionBehaviorTask : Quartz.IJob
{
    private static readonly ILog Log = LogManager.GetLogger(typeof (MotionBehaviorTask));

    public void Execute(Quartz.IJobExecutionContext context)
    {
        if (context != null)
        {
            var behavior = context.MergedJobDataMap.Get("MotionBasedBehavior") as MotionBasedBehavior;
            var contextServer = context.MergedJobDataMap.Get("ContextServer") as string;

            SyncExecuteBehavior(contextServer, behavior);
        }
    }

    public static void SyncExecuteBehavior(string contextServer, MotionBasedBehavior behavior)
    {
        try
        {
            if (!string.IsNullOrEmpty(contextServer) && behavior != null)
            {

                Console.WriteLine(@"------------- Task Details --------------");
                Console.WriteLine(@"Behavior Name : {0}", behavior.Name);
                Console.WriteLine(@"Human Id : {0}", behavior.Id);
                Console.WriteLine(@"Trigger Name : {0}", behavior.Trigger);
                Console.WriteLine(@"Confidence Level : {0}", behavior.ConfidenceLevel);
                Console.WriteLine(@"Priority : {0}", behavior.Priority);
                Console.WriteLine(@"-----------------------------------------");

                foreach (var behaviorInfo in behavior.RobotActions)
                {
                    // Before executing each action get the latest information about the human
                    string humanInfo = string.Empty;
                    if (!string.IsNullOrEmpty(contextServer))
                    {
                        using (var ctx = NetMQ.NetMQContext.Create())
                        {
                            using (var sock = ctx.CreateRequestSocket())
                            {
                                sock.Connect(contextServer);
                                Console.WriteLine(@"Getting updated information about the human : {0}",
                                    behavior.Id);
                                sock.Send(string.Format("human/{0}", behavior.Id));
                                humanInfo = sock.ReceiveString();
                            }
                        }
                    }
                    if (!string.IsNullOrEmpty(humanInfo))
                    {
                        Console.WriteLine(humanInfo);
                    }
                    using (var ctx = NetMQ.NetMQContext.Create())
                    {
                        using (var sock = ctx.CreateRequestSocket())
                        {
                            var ip = behaviorInfo.Ip;
                            var port = behaviorInfo.Port;
                            var behaviorName = behaviorInfo.BehaviorName;
                            var moduleName = behaviorInfo.ModuleName;

                            var addr = string.Format("{0}:{1}", ip, port);
                            Log.InfoFormat("Connecting to behavior server - Module: {0}, Address: {1}",
                                moduleName, addr);

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
        }
        catch (Exception ex)
        {
            Log.ErrorFormat("Simple behavior error : {0}", ex.Message);
        }
    }
}