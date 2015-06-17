using System;
using System.Collections.Generic;
using NCalc;

// Main Behavior Program

public class StartupBehavior : IExecuteOnceBehavior
{
    public void Execute(IBehaviorExecutionContext context)
    {
        // STARTUP_BLOCK
        var var_2a7fdb8d_353f_9f6b_9fe8_0c8b21499a52 = new BehaviorInfo { BehaviorName = "greet" };

        BehaviorModuleHelper.Execute(context, var_2a7fdb8d_353f_9f6b_9fe8_0c8b21499a52);

    }
}
public class ExitBehavior : IExecuteOnceBehavior
{
    public void Execute(IBehaviorExecutionContext context)
    {
        // EXIT_BLOCK
        var var_92ed8b39_cd08_da73_87e0_d3ec12eaf5d3 = new BehaviorInfo { BehaviorName = "greet" };

        BehaviorModuleHelper.Execute(context, var_92ed8b39_cd08_da73_87e0_d3ec12eaf5d3);

    }
}
public class Behavior_d105a1fc_df96_09e0_aa60_e93eb56a4982 : ITriggerBehavior
{
    public string Name { get; set; }

    protected static BehaviorExecutionPriority Priority;

    public static BehaviorExecutionPriority GetPriority()
    {
        // SET_PRIORITY
        Priority = BehaviorExecutionPriority.low
;
        return Priority;
    }

    protected static BehaviorExecutionLifetime ExecutionLifetime;

    public static BehaviorExecutionLifetime GetExecutionLifetime()
    {
        // SET_EXECUTION_LIFETIME
        ExecutionLifetime = BehaviorExecutionLifetime.forever;

        return ExecutionLifetime;
    }

    public static string ExecutionEvalExpression { get; set; }
    public int Id { get; set; }

    protected static string Uid;

    public static string GetUid()
    {
        Uid = "d105a1fc_df96_09e0_aa60_e93eb56a4982";

        // SET_UID_HERE
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

    public static bool CheckExecution(IBehaviorExecutionContext context)
    {
        if (ExecutionLifetime == BehaviorExecutionLifetime.forever)
        {
        }
        else if (ExecutionLifetime == BehaviorExecutionLifetime.once)
        {
            if (ExecutionComplete)
            {
                return false;
            }
        }
        else if (ExecutionLifetime == BehaviorExecutionLifetime.until && !string.IsNullOrEmpty(ExecutionEvalExpression))
        {
            var expression = new Expression(ExecutionEvalExpression);
            var result = expression.Evaluate();
            bool complete;
            if (bool.TryParse(result.ToString(), out complete))
            {
                return !complete;
            }
        }
        return true;
    }

    public static TriggerResult CheckTrigger(IBehaviorExecutionContext ctx)
    {
        var result = new TriggerResult { Active = false };
        if (ctx != null)
        {
            var gestureInfo = ctx.GetGestureInfo("Greet_Left");
            if (gestureInfo.Active && gestureInfo.Confidence > 90)
            {
                result.HumanId = gestureInfo.HumanId;
                result.HumanInLoop = true;
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

    //public static CheckTriggerDelegate TriggerDelegate
    //{
    //    get { return _triggerDelegate; }
    //}

    //public static CheckLifetimeDelegate LifetimeDelegate
    //{
    //    get { return CheckLifetimeDelegate; }
    //}

    public bool ExecuteInit(IBehaviorExecutionContext context)
    {
        if (!InitActionsComplete)
        {
            // INIT_BLOCK
            var var_be3e4671_25da_2ae9_a20e_17f8eddd4dc8 = new BehaviorInfo { BehaviorName = "greet" };

            BehaviorModuleHelper.Execute(context, var_be3e4671_25da_2ae9_a20e_17f8eddd4dc8);

            InitActionsComplete = true;
        }
        return InitActionsComplete;
    }

    public bool ExecuteCyclic(IBehaviorExecutionContext context)
    {
        if (!CyclicActionsComplete && InitActionsComplete)
        {
            // CYCLIC_BLOCK
            var var_bce5f762_c843_4abb_8ff3_8534c4a8e247 = new BehaviorInfo { BehaviorName = "Say Expressively", Parameters = new Dictionary<string, object> { { "msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("text", true, "string") } } };

            BehaviorModuleHelper.Execute(context, var_bce5f762_c843_4abb_8ff3_8534c4a8e247);

        }
        return CyclicActionsComplete;
    }

    public bool ExecuteExit(IBehaviorExecutionContext context)
    {
        if (!ExitActionsComplete && CyclicActionsComplete)
        {
            // EXIT_BLOCK
            var var_4b3252c9_6018_dfbb_a829_b9503b8ec9f9 = new BehaviorInfo { BehaviorName = "Say Expressively", Parameters = new Dictionary<string, object> { { "msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("text", true, "string") } } };

            BehaviorModuleHelper.Execute(context, var_4b3252c9_6018_dfbb_a829_b9503b8ec9f9);

            ExitActionsComplete = true;
        }
        return ExitActionsComplete;
    }

    public bool Execute(IBehaviorExecutionContext context)
    {
        ExecuteInit(context);
        ExecuteCyclic(context);
        ExecuteExit(context);
        return ExecutionComplete;
    }
}