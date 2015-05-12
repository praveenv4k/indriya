using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Xml.Linq;
using Common.Logging;
using NetMQ;
using Quartz;
using Quartz.Impl;

public static class LinqXmlUtil
{
    //public static XAttribute AttributeAnyNS<T>(this T source, string localName)
    //    where T : XElement
    //{
    //    return source.Attributes().SingleOrDefault(e => e.Name.LocalName == localName);
    //}

    public static IEnumerable<XElement> GetElementsAnyNS(IEnumerable<XContainer> source, string localName)
    {
        return source.Elements().Where(e => e.Name.LocalName == localName);
    }

    public static IEnumerable<XElement> GetElementsAnyNS(XContainer source, string localName)
    {
        return source.Elements().Where(e => e.Name.LocalName == localName);
    }
}

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

    public static IList<MotionBasedBehavior> ReadBehaviorXmlFile(string xmlFile)
    {
        var root = XElement.Load(xmlFile);
        //var doc = XmlDocumentUtil.RemoveXmlns(xmlFile);

        var blocks = LinqXmlUtil.GetElementsAnyNS(root, "block");
        Console.WriteLine(@"Number of behavior blocks : {0}", blocks.Count());

        var motionBehaviorList = new List<MotionBasedBehavior>();
        foreach (var block in blocks)
        {
            var type = block.Attribute("type");
            if (type.Value == "behavior_sleek")
            {
                var motionBehavior = new MotionBasedBehavior();
                var fields = LinqXmlUtil.GetElementsAnyNS(block, "field");
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
                var statements = LinqXmlUtil.GetElementsAnyNS(block, "statement");
                var statementBlocks = LinqXmlUtil.GetElementsAnyNS(statements, "block").ToArray();
                for (int i = 0; i < statementBlocks.Length; i++)
                {
                    var tempBlock = statementBlocks[i];
                    var behaviorInfo = GetBehaviorInfo(tempBlock);
                    if (behaviorInfo != null)
                    {
                        motionBehavior.RobotActions.Add(behaviorInfo);
                        var nextBlock = LinqXmlUtil.GetElementsAnyNS(tempBlock, "next");
                        while (nextBlock != null && nextBlock.Any())
                        {
                            var childBlock = LinqXmlUtil.GetElementsAnyNS(nextBlock, "block").FirstOrDefault();
                            if (childBlock != null)
                            {
                                behaviorInfo = GetBehaviorInfo(childBlock);
                                if (behaviorInfo != null)
                                {
                                    motionBehavior.RobotActions.Add(behaviorInfo);
                                    Console.WriteLine(childBlock);
                                    nextBlock = LinqXmlUtil.GetElementsAnyNS(childBlock, "next");
                                    Console.WriteLine(nextBlock);
                                }
                                else
                                {
                                    nextBlock = null;
                                }
                            }
                            else
                            {
                                nextBlock = null;
                            }
                        }
                    }
                }
                motionBehaviorList.Add(motionBehavior);
            }
        }
        //foreach (var motionBehavior in motionBehaviorList)
        //{
        //    Console.WriteLine(@"Motion Behavior : {0}, Trigger : {1}, Confidence: {2}, Priority: {3}",
        //        motionBehavior.Name, motionBehavior.Trigger, motionBehavior.ConfidenceLevel, motionBehavior.Priority);
        //    foreach (var behaviorInfo in motionBehavior.RobotActions)
        //    {
        //        Console.WriteLine(@"\t -> Action Name : {0}", behaviorInfo.BehaviorName);
        //    }
        //}
        return motionBehaviorList;
    }

    public static BehaviorInfo GetBehaviorInfo(XElement behaviorBlock)
    {
        if (behaviorBlock != null)
        {
            var blockType = behaviorBlock.Attribute("type");
            if (blockType.Value == "robot_action")
            {
                var robotActions = LinqXmlUtil.GetElementsAnyNS(behaviorBlock,"field");
                //var robotActions = behaviorBlock.ElementsAnyNS("field");
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