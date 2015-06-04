using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Xml.Linq;
using Common.Logging;
using NetMQ;
using Quartz;
using Quartz.Impl;
// ReSharper disable LoopCanBeConvertedToQuery

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

    public static List<MotionBasedBehavior> ReadBehaviorXmlFile(string xmlFile)
    {
        var root = XElement.Load(xmlFile);
        //var doc = XmlDocumentUtil.RemoveXmlns(xmlFile);

        var blocks = LinqXmlUtil.GetElementsAnyNS(root, "block").ToList();
        Console.WriteLine(@"Number of behavior blocks : {0}", blocks.Count);

        var motionBehaviorList = new List<MotionBasedBehavior>();
        foreach (var block in blocks)
        {
            var type = block.Attribute("type");
            MotionBasedBehavior motionBehavior = null;
            if (type.Value == "behavior_sleek" || type.Value == "behavior_simple")
            {
                motionBehavior = GetMotionBasedBehavior(block);
                motionBehavior.BehaviorType = BehaviorType.Behavior;
            }
            else if (type.Value == "behavior_startup")
            {
                motionBehavior = GetMotionBasedBehavior(block);
                motionBehavior.BehaviorType = BehaviorType.Startup;
            }
            else if (type.Value == "behavior_exit")
            {
                motionBehavior = GetMotionBasedBehavior(block);
                motionBehavior.BehaviorType = BehaviorType.Exit;
            }
            if (motionBehavior != null)
            {
                if (motionBehavior.RobotActions.Count > 0)
                {
                    motionBehaviorList.Add(motionBehavior);
                }
            }
        }

        Console.WriteLine(@"Number of behaviors parsed : {0}", motionBehaviorList.Count);
        return motionBehaviorList;
    }

    public static MotionBasedBehavior GetMotionBasedBehavior(XElement block)
    {
        if (block == null)
        {
            return null;
        }
        var motionBehavior = new MotionBasedBehavior {Guid = Guid.NewGuid()};

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
                else if (nameAttribute.Value == "trigger_count")
                {
                    motionBehavior.TriggerCountVariable = field.Value;
                }
                else if (nameAttribute.Value == "execution")
                {
                    BehaviorExecutionLifetime execution = BehaviorExecutionLifetime.forever;
                    Enum.TryParse(field.Value, out execution);
                    motionBehavior.ExecutionLifetime = execution;
                    if (execution == BehaviorExecutionLifetime.until)
                    {
                        var mutationBlock = LinqXmlUtil.GetElementsAnyNS(block, "mutation").ToList();
                        if (mutationBlock.Count > 0)
                        {
                            var mutation = mutationBlock[0];
                            var runLogicAttr = mutation.Attribute("run_logic");
                            if (runLogicAttr != null)
                            {
                                motionBehavior.ExecutionEvalExpression =
                                    runLogicAttr.Value;
                            }
                        }
                    }
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
        var statements = LinqXmlUtil.GetElementsAnyNS(block, "statement").ToArray();
        for (int s = 0; s < statements.Length; s++)
        {
            var currStatement = statements[s];
            IList<BehaviorInfo> tempList = null;
            if (currStatement.Attribute("name").Value == "INIT_DO")
            {
                tempList = motionBehavior.InitActions;
            }
            if (currStatement.Attribute("name").Value == "DO")
            {
                tempList = motionBehavior.RobotActions;
            }
            if (currStatement.Attribute("name").Value == "EXIT_DO")
            {
                tempList = motionBehavior.ExitActions;
            }
            if (tempList != null)
            {
                var statementBlocks = LinqXmlUtil.GetElementsAnyNS(currStatement, "block").ToArray();
                for (int i = 0; i < statementBlocks.Length; i++)
                {
                    var tempBlock = statementBlocks[i];
                    var behaviorInfo = GetBehaviorInfo(tempBlock);
                    if (behaviorInfo != null)
                    {
                        tempList.Add(behaviorInfo);
                        var nextBlock = LinqXmlUtil.GetElementsAnyNS(tempBlock, "next");
                        while (nextBlock != null && nextBlock.Any())
                        {
                            var childBlock = LinqXmlUtil.GetElementsAnyNS(nextBlock, "block").FirstOrDefault();
                            if (childBlock != null)
                            {
                                behaviorInfo = GetBehaviorInfo(childBlock);
                                tempList.Add(behaviorInfo);
                                Console.WriteLine(childBlock);
                                nextBlock = LinqXmlUtil.GetElementsAnyNS(childBlock, "next");
                                Console.WriteLine(nextBlock);
                            }
                            else
                            {
                                nextBlock = null;
                            }
                        }
                    }
                }
            }
        }
        // Check cloning
        //var temp = motionBehavior.Clone() as MotionBasedBehavior;
        //if (temp != null)
        //{

        //}
        return motionBehavior;
    }

    public static KeyValuePair<string, object> CreateBehaviorParameter(string name, object value, bool place_holder,
        string type)
    {
        return new KeyValuePair<string, object>(
            name, new Dictionary<string, object>
            {
                {"value", value},
                {"place_holder", place_holder},
                {"type", type}
            });
    }

    public static object CreateBehaviorParameterOptions(object value, bool place_holder,
        string type)
    {
        return new Dictionary<string, object>
        {
            {"value", value},
            {"place_holder", place_holder},
            {"type", type}
        };
    }

    public static BehaviorInfo GetBehaviorInfo(XElement behaviorBlock)
    {
        if (behaviorBlock != null)
        {
            var blockType = behaviorBlock.Attribute("type");
            if (blockType.Value == "robot_action")
            {
                var robotActions = LinqXmlUtil.GetElementsAnyNS(behaviorBlock, "field");
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
            else if (blockType.Value == "animated_say_action")
            {
                var robotActions = LinqXmlUtil.GetElementsAnyNS(behaviorBlock, "field");
                if (robotActions != null)
                {
                    foreach (var robotAction in robotActions)
                    {
                        var actionType = robotAction.Attribute("name");
                        if (actionType.Value == "SAY_TEXT")
                        {
                            return new BehaviorInfo
                            {
                                BehaviorName = "Say Expressively",
                                Parameters =
                                    new Dictionary<string, object>()
                                    {
                                        {"msg", CreateBehaviorParameterOptions(robotAction.Value, true, "string")}
                                    }
                            };
                        }
                    }
                }
            }
            else if (blockType.Value == "approach_action")
            {
                var robotActions = LinqXmlUtil.GetElementsAnyNS(behaviorBlock, "field");
                if (robotActions != null)
                {
                    foreach (var robotAction in robotActions)
                    {
                        var actionType = robotAction.Attribute("name");
                        if (actionType.Value == "approach_distance")
                        {
                            return new BehaviorInfo
                            {
                                BehaviorName = "Move To",
                                Parameters = new Dictionary<string, object>
                                {
                                    {"dist", CreateBehaviorParameterOptions(robotAction.Value, false, "float")},
                                    {"x", CreateBehaviorParameterOptions(0.5, true, "float")},
                                    {"y", CreateBehaviorParameterOptions(0.0, true, "float")},
                                    {"z", CreateBehaviorParameterOptions(0.0, true, "float")}
                                }
                            };
                        }
                    }
                }
            }
        }
        return null;
    }
}