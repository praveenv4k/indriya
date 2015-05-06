using System;
using System.Collections.Specialized;
using Common.Logging;
using NetMQ;
using Quartz;
using Quartz.Impl;

public class MainProgramUtil
{
    private static readonly ILog Log = LogManager.GetLogger(typeof (MainProgramUtil));

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
                        Console.WriteLine(@"Message buffer empty!");
                    }
                }
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.StackTrace, @"Parameter retrieve");
        }
        return "";
    }

    public static IScheduler GetScheduler()
    {
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

        Console.WriteLine(@"Scheduler created");

        return scheduler;
    }

}