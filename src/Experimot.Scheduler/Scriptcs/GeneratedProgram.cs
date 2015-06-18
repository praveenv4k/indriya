// ReSharper disable RedundantUsingDirective
using System;
using System.Collections.Generic;
using NCalc;

// Main Behavior Program

using System;
using NCalc;

public class Behavior_a9740d35_5bcb_37d2_b258_868b50d0b01b : ITriggerBehavior
{
    public string Name { get; set; }

    protected static BehaviorExecutionPriority Priority;

    public Behavior_a9740d35_5bcb_37d2_b258_868b50d0b01b()
    {
        GetPriority();
        GetExecutionLifetime();
        GetUid();
        GetExecutionEvalExpression();
    }

    public static BehaviorExecutionPriority GetPriority()
    {
        // SET_PRIORITY
        Priority = BehaviorExecutionPriority.low;

        return Priority;
    }

    protected static BehaviorExecutionLifetime ExecutionLifetime;

    public static BehaviorExecutionLifetime GetExecutionLifetime()
    {
        // SET_EXECUTION_LIFETIME
        ExecutionLifetime = BehaviorExecutionLifetime.forever;

        return ExecutionLifetime;
    }

    protected static string ExecutionEvalExpression { get; set; }

    public static string GetExecutionEvalExpression()
    {
        // SET_EXEC_EVAL
        // SET_EXEC_EVAL_HERE
        return ExecutionEvalExpression;
    }

    public int Id { get; set; }

    protected static string Uid;

    public static string GetUid()
    {
        // SET_UID
        Uid = "a9740d35_5bcb_37d2_b258_868b50d0b01b";

        return Uid;
    }

    private static bool _initActionsComplete;
    private static bool _cyclicActionsComplete;
    private static bool _exitActionsComplete;

    //private void SampleTriggerSetting()
    //{
    //    // Gesture trigger
    //    _triggerDelegate = delegate(IBehaviorExecutionContext ctx, out TriggerResult result)
    //    {
    //        result = new TriggerResult();
    //        if (ctx != null)
    //        {
    //            var gestureInfo = ctx.GetGestureInfo("");
    //            if (gestureInfo.Active && gestureInfo.Confidence > 90)
    //            {
    //                result.HumanId = gestureInfo.HumanId;
    //                result.HumanInLoop = true;
    //                return true;
    //            }
    //        }
    //        return false;
    //    };

    //    // Voice Trigger
    //    _triggerDelegate = delegate(IBehaviorExecutionContext ctx, out TriggerResult result)
    //    {
    //        result = new TriggerResult();
    //        if (ctx != null)
    //        {
    //            var voiceCommand = ctx.GetVoiceCommand("");
    //            if (voiceCommand.Active && voiceCommand.Confidence > 70)
    //            {
    //                return true;
    //            }
    //        }
    //        return false;
    //    };
    //}

    //public static bool CheckExecution(IBehaviorExecutionContext context)
    //{
    //    if (ExecutionLifetime == BehaviorExecutionLifetime.forever)
    //    {
    //    }
    //    else if (ExecutionLifetime == BehaviorExecutionLifetime.once)
    //    {
    //        if (ExecutionComplete)
    //        {
    //            return false;
    //        }
    //    }
    //    else if (ExecutionLifetime == BehaviorExecutionLifetime.until && !string.IsNullOrEmpty(ExecutionEvalExpression))
    //    {
    //        var expression = new Expression(ExecutionEvalExpression);
    //        var result = expression.Evaluate();
    //        bool complete;
    //        if (bool.TryParse(result.ToString(), out complete))
    //        {
    //            return !complete;
    //        }
    //    }
    //    return true;
    //}

    public static TriggerResult CheckTrigger(IBehaviorExecutionContext ctx)
    {
        var result = new TriggerResult { Active = false };
        if (ctx != null)
        {
            var voiceCommand = ctx.GetVoiceCommand("Stop");
            if (voiceCommand.Active && voiceCommand.Confidence > 70)
            {
                result.Active = true;
            }

        }
        return result;
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

    public bool ExecuteInit(IBehaviorExecutionContext context)
    {
        if (!InitActionsComplete)
        {
            // INIT_BLOCK

            InitActionsComplete = true;
        }
        return InitActionsComplete;
    }

    public bool ExecuteCyclic(IBehaviorExecutionContext context)
    {
        if (!CyclicActionsComplete && InitActionsComplete)
        {
            // CYCLIC_BLOCK
            var var_a994e930_3b29_3d3d_8bd4_d1ea3508f88f = new BehaviorInfo { BehaviorName = "Say Expressively", Parameters = new Dictionary<string, object> { { "msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("Stop command received! I will stop now!", true, "string") } } };

            BehaviorModuleHelper.Execute(context, var_a994e930_3b29_3d3d_8bd4_d1ea3508f88f);


            if (ExecutionLifetime == BehaviorExecutionLifetime.once)
            {
                CyclicActionsComplete = true;
            }
            else if (ExecutionLifetime == BehaviorExecutionLifetime.until &&
                     !string.IsNullOrEmpty(ExecutionEvalExpression))
            {
                var expression = new Expression(ExecutionEvalExpression);
                var result = expression.Evaluate();
                bool complete;
                if (bool.TryParse(result.ToString(), out complete))
                {
                }
                CyclicActionsComplete = complete;
            }
        }
        return CyclicActionsComplete;
    }

    public bool ExecuteExit(IBehaviorExecutionContext context)
    {
        if (!ExitActionsComplete && CyclicActionsComplete)
        {
            // EXIT_BLOCK

            ExitActionsComplete = true;
        }
        return ExitActionsComplete;
    }

    public bool Execute(IBehaviorExecutionContext context)
    {
        ExecuteInit(context);
        ExecuteCyclic(context);
        ExecuteExit(context);
        Console.WriteLine(@"Lifetime: {3} Init : {0}, Cyclic: {1}, Exit: {2}", InitActionsComplete,
            CyclicActionsComplete,
            ExitActionsComplete, ExecutionLifetime);
        return ExecutionComplete;
    }
}