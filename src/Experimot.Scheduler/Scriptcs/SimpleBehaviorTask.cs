using System;
using System.Collections.Generic;
using Common.Logging;
using NetMQ;

public class SimpleBehaviorTask : Quartz.IJob
{
    private static readonly ILog Log = LogManager.GetLogger(typeof (SimpleBehaviorTask));

    public void Execute(Quartz.IJobExecutionContext context)
    {
        if (context != null)
        {
            try
            {
                var behaviorInfoList = context.MergedJobDataMap.Get("BehaviorInfoList") as IList<BehaviorInfo>;
                
                //var ip = context.MergedJobDataMap.GetString("BehaviorServerIp");
                //var port = context.MergedJobDataMap.GetIntValue("BehaviorServerPort");
                //var behaviorName = context.MergedJobDataMap.GetString("BehaviorName");
                //if (!string.IsNullOrEmpty(ip) && port != 0)
                {
                    if (behaviorInfoList != null)
                    {
                        foreach (var behaviorInfo in behaviorInfoList)
                        {
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
            }
            catch (Exception ex)
            {
                Log.ErrorFormat("Simple behavior error : {0}", ex.Message);
            }
        }
    }
}