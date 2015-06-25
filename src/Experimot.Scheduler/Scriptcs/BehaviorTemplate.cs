// ReSharper disable CheckNamespace

using System;

public class BehaviorTemplate : ITriggerBehavior
{
    public string Name { get; set; }

    protected static BehaviorExecutionPriority Priority;

    public BehaviorTemplate()
    {
        GetPriority();
        GetExecutionLifetime();
        GetUid();
    }

    public static BehaviorExecutionPriority GetPriority()
    {
        // SET_PRIORITY
        // SET_PRIORITY_HERE
        return Priority;
    }

    protected static BehaviorExecutionLifetime ExecutionLifetime;

    public static BehaviorExecutionLifetime GetExecutionLifetime()
    {
        // SET_EXECUTION_LIFETIME
        // SET_EXECUTION_LIFETIME_HERE
        return ExecutionLifetime;
    }

    public int Id { get; set; }

    protected static string Uid;

    public static string GetUid()
    {
        // SET_UID
        // SET_UID_HERE
        return Uid;
    }

    private static bool _initActionsComplete;
    private static bool _cyclicActionsComplete;
    private static bool _exitActionsComplete;

    public static TriggerResult CheckTrigger(IBehaviorExecutionContext context)
    {
        var result = new TriggerResult {Active = false};

        if (context != null && !ExecutionComplete)
        {
            // SET_TRIGGER_HERE
        }
        return result;
    }

    public bool ExecutionUntil(IBehaviorExecutionContext context)
    {
        if (context != null)
        {
            // EXECUTE_UNTIL
            // EXECUTE_UNTIL_HERE
        }
        return true;
    }

    public string ActiveResource { get; set; }

    public static bool InitActionsComplete
    {
        get { return _initActionsComplete; }
        set { _initActionsComplete = value; }
    }

    public static bool CyclicActionsComplete
    {
        get { return _cyclicActionsComplete; }
        set { _cyclicActionsComplete = value; }
    }

    public static bool ExitActionsComplete
    {
        get { return _exitActionsComplete; }
        set { _exitActionsComplete = value; }
    }

    public static bool ExecutionComplete
    {
        get { return InitActionsComplete & CyclicActionsComplete & ExitActionsComplete; }
    }

    public bool ExecuteInit(IBehaviorExecutionContext context, TriggerResult trigger)
    {
        if (!InitActionsComplete)
        {
            // INIT_BLOCK
            // INIT_BLOCK_HERE
            InitActionsComplete = true;
        }
        return InitActionsComplete;
    }

    public bool ExecuteCyclic(IBehaviorExecutionContext context, TriggerResult trigger)
    {
        if (!CyclicActionsComplete && InitActionsComplete)
        {
            // CYCLIC_BLOCK
            // CYCLIC_BLOCK_HERE

            if (ExecutionLifetime == BehaviorExecutionLifetime.once)
            {
                CyclicActionsComplete = true;
            }
            else if (ExecutionLifetime == BehaviorExecutionLifetime.until)
            {
                var complete = ExecutionUntil(context);
                CyclicActionsComplete = !complete;
            }
        }
        return CyclicActionsComplete;
    }

    public bool ExecuteExit(IBehaviorExecutionContext context, TriggerResult trigger)
    {
        if (!ExitActionsComplete && CyclicActionsComplete)
        {
            // EXIT_BLOCK
            // EXIT_BLOCK_HERE
            ExitActionsComplete = true;
        }
        return ExitActionsComplete;
    }

    public bool Execute(IBehaviorExecutionContext context, TriggerResult trigger)
    {
        try
        {
            ExecuteInit(context, trigger);
            ExecuteCyclic(context, trigger);
            ExecuteExit(context, trigger);
            System.Console.WriteLine(@"Lifetime: {3} Init : {0}, Cyclic: {1}, Exit: {2}", InitActionsComplete,
                CyclicActionsComplete,
                ExitActionsComplete, ExecutionLifetime);
        }
        catch (BehaviorCanceledException ex)
        {
            Console.WriteLine(@"Execution canceled : {0}, {1} ,{2}", GetUid(), ex.Message, ex.StackTrace);
        }
        return ExecutionComplete;
    }
}