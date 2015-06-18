using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using Common.Logging;
using Quartz;

public class BehaviorExecutionEngine
{
    private static readonly ILog Log = LogManager.GetLogger(typeof (BehaviorExecutionEngine));
    private readonly BehaviorExecutionContext _context;
    private readonly IScheduler _scheduler;
    private const int Period = 200;

    public BehaviorExecutionContext Context
    {
        get { return _context; }
    }

    public IScheduler Scheduler
    {
        get { return _scheduler; }
    }

    public BehaviorExecutionEngine(BehaviorExecutionContext context, IScheduler scheduler)
    {
        _context = context;
        _scheduler = scheduler;
    }

    public static void DisplayLoadedTypes()
    {
        //var types = Assembly.GetAssembly(typeof (StartupBehavior)).GetTypes().ToList();
        //Log.InfoFormat(@"Loaded Types : {0}", string.Join("\n", types.Select(s => s.Name)));

        var types = Assembly.GetCallingAssembly().GetTypes().ToList();
        Log.InfoFormat(@"Calling assembly Types : {0}", string.Join("\n", types.Select(s => s.Name)));

        types = Assembly.GetExecutingAssembly().GetTypes().ToList();
        Log.InfoFormat(@"Executing assembly Types : {0}", string.Join("\n", types.Select(s => s.Name)));

        types = Assembly.GetEntryAssembly().GetTypes().ToList();
        Log.InfoFormat(@"Entry assembly Types : {0}", string.Join("\n", types.Select(s => s.Name)));

        Log.InfoFormat(@"Startup Classes : {0}", string.Join(",", GetTypes("StartupBehavior").Select(s => s.Name)));

        Log.InfoFormat(@"Behavior Classes : {0}",
            string.Join(",", GetTypes(typeof (ITriggerBehavior)).Select(s => s.Name)));
        Log.InfoFormat(@"Exit Classes : {0}", string.Join(",", GetTypes("ExitBehavior").Select(s => s.Name)));
    }

    public void ExecuteInitExitBlock(string blockName)
    {
        try
        {
            var startupType = GetTypes(blockName).FirstOrDefault();
            // Check Startup behavior exists
            if (startupType != null)
            {
                Log.InfoFormat("{0} Exists", blockName);
                // Check Execute method exists
                var execMethodInfo = startupType.GetMethod("Execute");
                if (execMethodInfo != null)
                {
                    // Create the instance of the Startupbehavior type
                    var startupInstance = Activator.CreateInstance(startupType);
                    if (startupInstance != null)
                    {
                        // Invoke the execute method
                        execMethodInfo.Invoke(startupInstance, new object[] {_context});
                    }
                }
            }
        }
        catch (Exception ex)
        {
            Log.ErrorFormat("Message : {0}, StackTrace : {1}", ex.Message, ex.StackTrace);
        }
    }

    public object InvokeStaticMethod(Type typeName, string methodName, params object[] parameters)
    {
        if (typeName != null && !string.IsNullOrEmpty(methodName))
        {
            MethodInfo staticMethodInfo = typeName.GetMethod(methodName);
            if (staticMethodInfo!=null && staticMethodInfo.IsStatic)
            {
                return staticMethodInfo.Invoke(null, parameters);
            }
        }
        return null;
    }

    public object InvokeStaticProperty(Type typeName, string propName)
    {
        if (typeName != null && !string.IsNullOrEmpty(propName))
        {
            var staticPropertyInfo = typeName.GetProperty(propName);
            if (staticPropertyInfo != null)
            {
                return staticPropertyInfo.GetValue(null);
            }
        }
        return null;
    }

    private int GetBehaviorPriority(Type behaviorType)
    {
        var priorityObject = InvokeStaticMethod(behaviorType, "GetPriority");
        var ret = BehaviorExecutionPriority.low;
        
        if (priorityObject != null)
        {
            if (Enum.TryParse(priorityObject.ToString(), true, out ret))
            {
                Log.InfoFormat("Priority Parsed properly : {1} - {0}", priorityObject, ret);
            }
        }
        return (int)ret;
    }

    private IList<Type> SortByPriority(IList<Type> cyclicBehaviors)
    {
        return cyclicBehaviors.OrderByDescending(GetBehaviorPriority).ToList();
    }

    private bool CheckExecutionComplete(IList<Type> cyclicBehaviors)
    {
        if (cyclicBehaviors != null)
        {
            bool ret = true;
            // ReSharper disable once LoopCanBeConvertedToQuery
            foreach (var cyclicBehavior in cyclicBehaviors)
            {
                ret &= CheckExecutionComplete(cyclicBehavior);
            }
            return ret;
        }
        return false;
    }

    private bool InvokeBooleanProperty(Type cyclicBehavior, string methodName)
    {
        var priorityObject = InvokeStaticProperty(cyclicBehavior, methodName);
        var ret = false;

        if (priorityObject != null)
        {
            if (bool.TryParse(priorityObject.ToString(), out ret))
            {
            }
        }
        return ret;
    }

    private T InvokeGenericMethod<T>(Type cyclicBehavior, string methodName, params object[] parameters) where T: class 
    {
        var returnObject = InvokeStaticMethod(cyclicBehavior, methodName, parameters);
        return returnObject as T;
    }

    private bool CheckExecutionComplete(Type cyclicBehavior)
    {
        return InvokeBooleanProperty(cyclicBehavior, "ExecutionComplete");
    }

    private TriggerResult CheckTrigger(Type cyclicBehavior)
    {
        return InvokeGenericMethod<TriggerResult>(cyclicBehavior, "CheckTrigger", Context);
    }

    public void ExecuteCyclicBehavior()
    {
        try
        {
            var cyclicBehaviors = GetTypes(typeof (ITriggerBehavior));
            Log.InfoFormat(@"Cyclic Behaviors : \n {0}", string.Join("\n", cyclicBehaviors.Select(s => s.Name)));

            // Sort the behaviors based on the priority
            var sortedList = SortByPriority(cyclicBehaviors);
            Log.InfoFormat(@"Cyclic Behaviors : \n {0}", string.Join("\n", sortedList.Select(s => s.Name)));

            // ReSharper disable once LoopVariableIsNeverChangedInsideLoop
            while (!CheckExecutionComplete(sortedList))
            {
                foreach (var type in sortedList)
                {
                    var result = CheckTrigger(type);
                    if (result != null)
                    {
                        if (result.Active)
                        {
                            string uid = InvokeGenericMethod<string>(type, "GetUid");
                            if (!string.IsNullOrEmpty(uid) && Scheduler != null)
                            {
                                var jobKey = JobKey.Create(string.Format("Task_{0}", uid), uid);
                                if (!Scheduler.CheckExists(jobKey))
                                {
                                    IJobDetail detail = JobBuilder.Create<BehaviorExecutionTask>()
                                        .WithIdentity(jobKey)
                                        .Build();
                                    detail.JobDataMap.Add("BehaviorType", type);
                                    detail.JobDataMap.Add("ExecutionContext", Context);
                                    detail.JobDataMap.Add("TriggerResult", result);
                                    ITrigger trigger = TriggerBuilder.Create().ForJob(detail).StartNow().Build();
                                    Scheduler.ScheduleJob(detail, trigger);
                                    Console.WriteLine(@"New job about to be scheduled Job : {0}, Module : {1}",
                                        jobKey.Name,
                                        jobKey.Group);
                                }
                            }
                        }
                    }
                }
                System.Threading.Thread.Sleep(Period);
            }
        }
        catch (Exception ex)
        {
            Log.ErrorFormat("Message : {0} ; StackTrace: {1}", ex.Message, ex.StackTrace);
        }
    }

    public void Run()
    {
        Log.Info(@"Running ...");

        // Startup Behavior Execution
        ExecuteInitExitBlock("StartupBehavior");

        // Cyclic Behavior Execution
        ExecuteCyclicBehavior();

        // Exit Behavior Execution
        ExecuteInitExitBlock("ExitBehavior");
    }

    public static IList<Type> GetTypes(string className)
    {
        return Assembly.GetExecutingAssembly().GetTypes()
            .Where(t => t.IsClass && t.Name == className).ToList();
    }

    public static IList<Type> GetTypes(Type interfaceType)
    {
        return Assembly.GetExecutingAssembly().GetTypes()
            .Where(t => t.IsClass && interfaceType.IsAssignableFrom(t)).ToList();
    }
}