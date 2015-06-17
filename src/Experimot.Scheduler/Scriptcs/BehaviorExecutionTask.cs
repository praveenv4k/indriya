using Common.Logging;
using System;

public class BehaviorExecutionTask : Quartz.IJob
{
    private static readonly ILog Log = LogManager.GetLogger(typeof(BehaviorExecutionTask));

    public void Execute(Quartz.IJobExecutionContext context)
    {
        if (context != null)
        {
            var behaviorType = context.MergedJobDataMap.Get("BehaviorType") as Type;
            var execContext = context.MergedJobDataMap.Get("ExecutionContext") as IBehaviorExecutionContext;
            if (behaviorType != null && execContext != null)
            {
                var execMethodInfo = behaviorType.GetMethod("Execute");
                if (execMethodInfo != null)
                {
                    // Create the instance of the Startupbehavior type
                    var startupInstance = Activator.CreateInstance(behaviorType);
                    if (startupInstance != null)
                    {
                        Log.Info(@"------------- Task Details --------------");
                        Log.InfoFormat(@"Behavior type Name : {0}", behaviorType.Name);
                        // Invoke the execute method
                        execMethodInfo.Invoke(startupInstance, new object[] {execContext});
                    }
                }
            }
        }
    }
}