using System;
using System.Collections.Generic;
using System.Linq;
using NetMQ;
using Newtonsoft.Json.Linq;
using Quartz;

// ReSharper disable once CheckNamespace
public class MainProgram
{
    private static volatile bool _requestStop;
    private readonly IDictionary<string, object> _props;
    private readonly IScheduler _scheduler;
    private const int RecvTimeout = 200;
    private const int Period = 200;

    public MainProgram(IDictionary<string, object> props, IScheduler scheduler)
    {
        _props = props;
        _scheduler = scheduler;
        _requestStop = false;
    }

    private static object GetValue(IDictionary<string, object> props, string key, object defaultValue)
    {
        var ret = defaultValue;
        if (props != null)
        {
            if (props.ContainsKey(key))
            {
                ret = props[key];
            }
        }
        return ret;
    }

    private static Dictionary<string, List<BehaviorInfo>> CheckGestureTrigger(NetMQSocket socket, JArray humanArray,
        Dictionary<string, List<BehaviorInfo>> gestBehaviorMap)
    {
        var ret = new Dictionary<string, List<BehaviorInfo>>();
        if (humanArray != null && socket != null && humanArray.Count > 0)
        {
            foreach (var human in humanArray)
            {
                var gestures = human.SelectToken("$.Gestures");
                foreach (var gesture in gestures)
                {
                    string name = gesture.Value<string>("Name");
                    if (gestBehaviorMap.ContainsKey(name))
                    {
                        bool active = gesture.Value<bool>("Active");
                        int confidence = gesture.Value<int>("Confidence");
                        if (active && confidence > 95)
                        {
                            ret.Add(name, gestBehaviorMap[name]);
                            Console.WriteLine(@"Name : {0}, Confidence: {1}", name, confidence);
                        }
                    }

                }
            }
        }
        return ret;
    }

    private static List<MotionBasedBehavior> CheckGestureTrigger(NetMQSocket socket, JArray humanArray,
        List<MotionBasedBehavior> gestBehaviorMap)
    {
        var ret = new List<MotionBasedBehavior>();
        if (humanArray != null && socket != null && humanArray.Count > 0)
        {
            foreach (var human in humanArray)
            {
                var gestures = human.SelectToken("$.Gestures");
                foreach (var gesture in gestures)
                {
                    string name = gesture.Value<string>("Name");
                    var motionBehavior = gestBehaviorMap.FirstOrDefault(s => s.Trigger == name);
                    if (motionBehavior != null)
                    {
                        bool active = gesture.Value<bool>("Active");
                        int confidence = gesture.Value<int>("Confidence");
                        if (active && confidence > motionBehavior.ConfidenceLevel)
                        {
                            motionBehavior.Id = human.Value<int>("Id");
                            ret.Add(motionBehavior);
                            Console.WriteLine(@"Name : {0}, Confidence: {1}", name, confidence);
                        }
                    }

                }
            }
        }
        return ret;
    }

    private static IList<BehaviorInfo> GetBehaviorModules(NetMQSocket socket,
        IList<BehaviorInfo> behaviorList)
    {
        var ret = new List<BehaviorInfo>();
        var dict = new Dictionary<string, BehaviorInfo>();
        //behavior_modules
        if (socket != null && behaviorList != null && behaviorList.Count > 0)
        {
            socket.Send("behavior_modules");
            var resp = socket.ReceiveString(new TimeSpan(0, 0, 0, 0, RecvTimeout));
            if (!string.IsNullOrEmpty(resp))
            {
                var modules = JArray.Parse(resp);
                if (modules != null && modules.Count > 0)
                {
                    //Console.WriteLine(resp);
                    foreach (var module in modules)
                    {
                        var moduleName = module.Value<string>("name");
                        var responder = module.SelectToken("$.responder");
                        string host = string.Empty;
                        int port = 0;
                        if (responder != null)
                        {
                            host = responder.Value<string>("Host");
                            port = responder.Value<int>("Port");
                        }
                        var behaviors = module.SelectToken("$.behaviors");
                        foreach (var behavior in behaviors)
                        {
                            string name = behavior.Value<string>("name");
                            if (!dict.ContainsKey(name))
                            {
                                dict.Add(name, new BehaviorInfo
                                {
                                    BehaviorName = name,
                                    Ip = host,
                                    Port = port
                                });
                            }
                        }
                    }
                }
            }
            if (dict.Count > 0)
            {
                // ReSharper disable once LoopCanBeConvertedToQuery
                foreach (var item in behaviorList)
                {
                    if (dict.ContainsKey(item.BehaviorName))
                    {
                        ret.Add(dict[item.BehaviorName]);
                    }
                }
            }
        }
        return ret;
    }

    private static void ScheduleBehaviorExecution(IScheduler scheduler, IList<BehaviorInfo> behaviorInfo,
        string triggerName)
    {
        Console.WriteLine(@"Behavior Execution for trigger : {0}", triggerName);
        if (behaviorInfo != null && behaviorInfo.Count > 0 && scheduler != null)
        {
            var moduleName = behaviorInfo[0].ModuleName;
            var jobKey = JobKey.Create(string.Format("Task_{0}", moduleName), moduleName);
            if (!scheduler.CheckExists(jobKey))
            {
                IJobDetail detail = JobBuilder.Create<SimpleBehaviorTask>()
                    .WithIdentity(jobKey)
                    .Build();
                detail.JobDataMap.Add("BehaviorInfoList", behaviorInfo);
                ITrigger trigger = TriggerBuilder.Create().ForJob(detail).StartNow().Build();
                scheduler.ScheduleJob(detail, trigger);
                Console.WriteLine(@"New job about to be scheduled Job : {0}, Module : {1}", jobKey.Name,
                    jobKey.Group);
            }
        }
    }

    private static void ScheduleBehaviorExecution(IScheduler scheduler, MotionBasedBehavior behavior,
        string triggerName, IDictionary<string, object> props)
    {
        Console.WriteLine(@"Behavior Execution for trigger : {0}", triggerName);
        if (behavior != null && behavior.RobotActions.Count > 0 && scheduler != null)
        {
            var moduleName = behavior.RobotActions[0].ModuleName;
            var jobKey = JobKey.Create(string.Format("Task_{0}", moduleName), moduleName);
            if (!scheduler.CheckExists(jobKey))
            {
                IJobDetail detail = JobBuilder.Create<MotionBehaviorTask>()
                    .WithIdentity(jobKey)
                    .Build();
                detail.JobDataMap.Add("MotionBasedBehavior", behavior);
                var contextServer = GetValue(props, "ContextServer", "tcp://localhost:5800").ToString();
                if (!string.IsNullOrEmpty(contextServer))
                {
                    detail.JobDataMap.Add("ContextServer", contextServer);
                }
                ITrigger trigger = TriggerBuilder.Create().ForJob(detail).StartNow().Build();
                scheduler.ScheduleJob(detail, trigger);
                Console.WriteLine(@"New job about to be scheduled Job : {0}, Module : {1}", jobKey.Name,
                    jobKey.Group);
            }
        }
    }

    private static void ScheduleBehaviorExecution(IScheduler scheduler, JToken behaviorModule, string behaviorName)
    {
        Console.WriteLine(@"Behavior Execution request : {0}", behaviorName);
        if (behaviorModule != null)
        {
            var moduleName = behaviorModule.Value<string>("name");
            if (!string.IsNullOrEmpty(moduleName))
            {
                var jobKey = JobKey.Create(string.Format("Task_{0}", behaviorName), moduleName);
                if (scheduler != null && !scheduler.CheckExists(jobKey))
                {
                    var responder = behaviorModule.SelectToken("$.responder");
                    if (responder != null)
                    {
                        string host = responder.Value<string>("Host");
                        int port = responder.Value<int>("Port");
                        // Console.WriteLine(@"Host : {0}, Port : {1}", host, port);

                        IJobDetail detail = JobBuilder.Create<SimpleBehaviorTask>()
                            .WithIdentity(jobKey)
                            .Build();

                        IList<BehaviorInfo> info = new List<BehaviorInfo>();
                        info.Add(new BehaviorInfo()
                        {
                            BehaviorName = behaviorName,
                            Ip = host,
                            Port = port,
                            ModuleName = moduleName
                        });
                        detail.JobDataMap.Add("BehaviorInfoList", info);
                        detail.JobDataMap.Add("BehaviorServerIp", host);
                        detail.JobDataMap.Add("BehaviorServerPort", port);
                        detail.JobDataMap.Add("BehaviorName", behaviorName);

                        ITrigger trigger = TriggerBuilder.Create().ForJob(detail).StartNow().Build();
                        scheduler.ScheduleJob(detail, trigger);
                        Console.WriteLine(@"New job about to be scheduled Job : {0}, Module : {1}", jobKey.Name,
                            jobKey.Group);
                    }
                }
            }
        }
    }

    public void Run()
    {
        Console.WriteLine(@"About to start running main program");
        try
        {
            if (_props != null && _props.Count > 0)
            {
                var contextServer = GetValue(_props, "ContextServer", "tcp://localhost:5800").ToString();
                if (!string.IsNullOrEmpty(contextServer))
                {
                    var triggerBehaviorMap = GetValue(_props, "TriggerBehaviorMap",
                        new Dictionary<string, List<BehaviorInfo>>());
                    var dict = triggerBehaviorMap as Dictionary<string, List<BehaviorInfo>>;
                    if (dict != null && dict.Count > 0)
                    {
                        foreach (var item in dict)
                        {
                            Console.WriteLine(@"Gesture: {0} -> ", item.Key);
                            foreach (var value in item.Value)
                            {
                                Console.WriteLine(@"Action: {0} -> ", value.BehaviorName);
                            }
                        }

                        using (var ctx = NetMQContext.Create())
                        {
                            using (var socket = ctx.CreateRequestSocket())
                            {
                                socket.Connect(contextServer);
                                while (!_requestStop)
                                {
                                    socket.Send("human");
                                    var resp = socket.ReceiveString(new TimeSpan(0, 0, 0, 0, RecvTimeout));
                                    if (!string.IsNullOrEmpty(resp))
                                    {
                                        try
                                        {
                                            JArray obj = JArray.Parse(resp);
                                            //Console.WriteLine(resp);
                                            var behaviorMap = CheckGestureTrigger(socket, obj, dict);
                                            if (behaviorMap.Count == 0)
                                            {
                                                //Console.WriteLine(@"No gesture detected!");
                                            }
                                            foreach (var behavior in behaviorMap)
                                            {
                                                Console.WriteLine(@"Detected Gesture: {0} -> ", behavior.Key);
                                                foreach (var value in behavior.Value)
                                                {
                                                    Console.WriteLine(@"Action: {0} -> ", value.BehaviorName);
                                                }
                                            }
                                            if (behaviorMap.Count > 0)
                                            {
                                                foreach (var behavior in behaviorMap)
                                                {
                                                    var modules = GetBehaviorModules(socket, behavior.Value);
                                                    if (modules != null && modules.Count > 0)
                                                    {
                                                        ScheduleBehaviorExecution(_scheduler, modules,
                                                            behavior.Key);
                                                    }
                                                }
                                                //var modules = GetBehaviorModules(socket, behaviorMap.Values);
                                                //if (modules != null && modules.Count > 0)
                                                //{
                                                //    foreach (var module in modules)
                                                //    {
                                                //        ScheduleBehaviorExecution(_scheduler, module.Value,
                                                //            module.Key);
                                                //    }
                                                //}
                                            }
                                        }
                                        catch (Exception ex)
                                        {
                                            Console.WriteLine(ex.Message);
                                        }
                                    }
                                    System.Threading.Thread.Sleep(Period);
                                }
                            }
                        }
                    }
                }
                else
                {
                    Console.WriteLine(@"Configuration information not available! Program will end now!");
                }
            }
            else
            {
                Console.WriteLine(@"Configuration information missing!");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine(@"Main Program Run exception: {0}", ex.StackTrace);
        }
        Console.WriteLine(@"About to complete main program");
    }

    public void RunBehaviors()
    {
        Console.WriteLine(@"About to start running main program");
        try
        {
            if (_props != null && _props.Count > 0)
            {
                var contextServer = GetValue(_props, "ContextServer", "tcp://localhost:5800").ToString();
                if (!string.IsNullOrEmpty(contextServer))
                {
                    var triggerBehaviorMap = GetValue(_props, "BehaviorList", new List<MotionBasedBehavior>());
                    var list = triggerBehaviorMap as List<MotionBasedBehavior>;
                    if (list != null && list.Count > 0)
                    {
                        foreach (var item in list)
                        {
                            switch (item.BehaviorType)
                            {
                                case BehaviorType.Startup:
                                case BehaviorType.Exit:
                                    Console.WriteLine(@"Behavior Type: {0} -> ", item.BehaviorType);
                                    foreach (var value in item.RobotActions)
                                    {
                                        Console.WriteLine(@"Action: {0} -> ", value.BehaviorName);
                                    }
                                    break;
                                case BehaviorType.Behavior:
                                    Console.WriteLine(@"Gesture: {0} count with {1}", item.Trigger, item.TriggerCount);
                                    Console.WriteLine(@"Startup Actions -> ");
                                    foreach (var value in item.InitActions)
                                    {
                                        Console.WriteLine(@"    Action: {0}", value.BehaviorName);
                                    }
                                    Console.WriteLine(@"Cyclic Actions -> ");
                                    foreach (var value in item.RobotActions)
                                    {
                                        Console.WriteLine(@"    Action: {0}", value.BehaviorName);
                                    }
                                    Console.WriteLine(@"Exit Actions -> ");
                                    foreach (var value in item.RobotActions)
                                    {
                                        Console.WriteLine(@"    Action: {0}", value.BehaviorName);
                                    }
                                    break;
                                default:
                                    throw new ArgumentOutOfRangeException();
                            }
                        }

                        using (var ctx = NetMQContext.Create())
                        {
                            using (var socket = ctx.CreateRequestSocket())
                            {
                                socket.Connect(contextServer);
                                while (!_requestStop)
                                {
                                    socket.Send("humans");
                                    var resp = socket.ReceiveString(new TimeSpan(0, 0, 0, 0, RecvTimeout));
                                    if (!string.IsNullOrEmpty(resp))
                                    {
                                        try
                                        {
                                            JArray obj = JArray.Parse(resp);
                                            //Console.WriteLine(resp);
                                            var behaviorMap = CheckGestureTrigger(socket, obj, list);
                                            if (behaviorMap.Count == 0)
                                            {
                                                //Console.WriteLine(@"No gesture detected!");
                                            }
                                            foreach (var behavior in behaviorMap)
                                            {
                                                Console.WriteLine(@"Detected Gesture: {0} -> ", behavior.Trigger);
                                                foreach (var value in behavior.RobotActions)
                                                {
                                                    Console.WriteLine(@"Action: {0} -> ", value.BehaviorName);
                                                }
                                            }
                                            if (behaviorMap.Count > 0)
                                            {
                                                foreach (var behavior in behaviorMap)
                                                {
                                                    var modules = GetBehaviorModules(socket, behavior.RobotActions);
                                                    if (modules != null && modules.Count > 0)
                                                    {
                                                        var motionBasedBehavior =
                                                            behavior.Clone() as MotionBasedBehavior;
                                                        if (motionBasedBehavior != null)
                                                        {
                                                            motionBasedBehavior.RobotActions = modules;
                                                            ScheduleBehaviorExecution(_scheduler, motionBasedBehavior,
                                                                behavior.Trigger, _props);
                                                        }
                                                    }
                                                }
                                                //var modules = GetBehaviorModules(socket, behaviorMap.Values);
                                                //if (modules != null && modules.Count > 0)
                                                //{
                                                //    foreach (var module in modules)
                                                //    {
                                                //        ScheduleBehaviorExecution(_scheduler, module.Value,
                                                //            module.Key);
                                                //    }
                                                //}
                                            }
                                        }
                                        catch (Exception ex)
                                        {
                                            Console.WriteLine(ex.Message);
                                        }
                                    }
                                    System.Threading.Thread.Sleep(Period);
                                }
                            }
                        }
                    }
                }
                else
                {
                    Console.WriteLine(@"Configuration information not available! Program will end now!");
                }
            }
            else
            {
                Console.WriteLine(@"Configuration information missing!");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine(@"Main Program Run exception: {0}", ex.StackTrace);
        }
        Console.WriteLine(@"About to complete main program");
    }
}