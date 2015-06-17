using System;
using System.Collections.Generic;
using NCalc;

// Main Behavior Program

public class StartupBehavior : IExecuteOnceBehavior
{
    public void Execute(IBehaviorExecutionContext context)
    {
        // STARTUP_BLOCK
        var var_47fa9a3b_b591_cd07_8e32_a5dfee921ad0 = new BehaviorInfo { BehaviorName = "greet" };

        BehaviorModuleHelper.Execute(context, var_47fa9a3b_b591_cd07_8e32_a5dfee921ad0);

    }
}
public class Behavior_752da8d5_ea40_4e80_ba03_7a4c803d396a : ITriggerBehavior
{
    public string Name { get; set; }
    public static BehaviorExecutionPriority Priority { get; set; }
    public static BehaviorExecutionLifetime ExecutionLifetime { get; set; }
    public static string ExecutionEvalExpression { get; set; }
    public int Id { get; set; }
    public static string Uid { get; set; }
    private static bool _initActionsComplete;
    private static bool _cyclicActionsComplete;
    private static bool _exitActionsComplete;
    private static CheckTriggerDelegate _triggerDelegate;
    private static CheckLifetimeDelegate _checkLifetimeDelegate;

    public Behavior_752da8d5_ea40_4e80_ba03_7a4c803d396a()
    {
        Uid = "752da8d5_ea40_4e80_ba03_7a4c803d396a";


        // SET_PRIORITY
        Priority = BehaviorExecutionPriority.low
;

        // SET_TRIGGER
        // The trigger delegate should not access any member variables
        _triggerDelegate = delegate(IBehaviorExecutionContext ctx, out TriggerResult result)
        {
            result = new TriggerResult();
            if (ctx != null)
            {
                var gestureInfo = ctx.GetGestureInfo("Greet_Left");
                if (gestureInfo.Active && gestureInfo.Confidence > 90)
                {
                    result.HumanId = gestureInfo.HumanId;
                    result.HumanInLoop = true;
                    return true;
                }

            }
            return false;
        };

        // SET_EXECUTION_LIFETIME
        ExecutionLifetime = BehaviorExecutionLifetime.forever;


        _checkLifetimeDelegate = CheckExecution;
    }

    private void SampleTriggerSetting()
    {
        // Gesture trigger
        _triggerDelegate = delegate(IBehaviorExecutionContext ctx, out TriggerResult result)
        {
            result = new TriggerResult();
            if (ctx != null)
            {
                var gestureInfo = ctx.GetGestureInfo("");
                if (gestureInfo.Active && gestureInfo.Confidence > 90)
                {
                    result.HumanId = gestureInfo.HumanId;
                    result.HumanInLoop = true;
                    return true;
                }
            }
            return false;
        };

        // Voice Trigger
        _triggerDelegate = delegate(IBehaviorExecutionContext ctx, out TriggerResult result)
        {
            result = new TriggerResult();
            if (ctx != null)
            {
                var voiceCommand = ctx.GetVoiceCommand("");
                if (voiceCommand.Active && voiceCommand.Confidence > 70)
                {
                    return true;
                }
            }
            return false;
        };
    }

    public bool CheckExecution(IBehaviorExecutionContext context)
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

    public static CheckTriggerDelegate TriggerDelegate
    {
        get { return _triggerDelegate; }
    }

    public static CheckLifetimeDelegate LifetimeDelegate
    {
        get { return _checkLifetimeDelegate; }
    }

    public bool ExecuteInit(IBehaviorExecutionContext context)
    {
        if (!InitActionsComplete)
        {
            // INIT_BLOCK
            var var_f4441218_e11a_2677_98e3_58b6283f43b6 = new BehaviorInfo { BehaviorName = "greet" };

            BehaviorModuleHelper.Execute(context, var_f4441218_e11a_2677_98e3_58b6283f43b6);

            InitActionsComplete = true;
        }
        return InitActionsComplete;
    }

    public bool ExecuteCyclic(IBehaviorExecutionContext context)
    {
        if (!CyclicActionsComplete && InitActionsComplete)
        {
            // CYCLIC_BLOCK
            var var_365aaf59_10c4_6856_9acb_4ebaf643b303 = new BehaviorInfo { BehaviorName = "Say Expressively", Parameters = new Dictionary<string, object> { { "msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("text", true, "string") } } };

            BehaviorModuleHelper.Execute(context, var_365aaf59_10c4_6856_9acb_4ebaf643b303);

        }
        return CyclicActionsComplete;
    }

    public bool ExecuteExit(IBehaviorExecutionContext context)
    {
        if (!ExitActionsComplete && CyclicActionsComplete)
        {
            // EXIT_BLOCK
            var var_5b6081c5_7b13_5759_bda7_8825e22a1ee7 = new BehaviorInfo { BehaviorName = "Say Expressively", Parameters = new Dictionary<string, object> { { "msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("text", true, "string") } } };

            BehaviorModuleHelper.Execute(context, var_5b6081c5_7b13_5759_bda7_8825e22a1ee7);

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
public class ExitBehavior : IExecuteOnceBehavior
{
    public void Execute(IBehaviorExecutionContext context)
    {
        // EXIT_BLOCK
        var var_46800d03_64bf_819d_98b7_10bd8e87557d = new BehaviorInfo { BehaviorName = "greet" };

        BehaviorModuleHelper.Execute(context, var_46800d03_64bf_819d_98b7_10bd8e87557d);

    }
}
public class Behavior_9598143a_3b94_6c60_8d4a_ee7d3ec9c7eb : ITriggerBehavior
{
    public string Name { get; set; }
    public static BehaviorExecutionPriority Priority { get; set; }
    public static BehaviorExecutionLifetime ExecutionLifetime { get; set; }
    public static string ExecutionEvalExpression { get; set; }
    public int Id { get; set; }
    public static string Uid { get; set; }
    private static bool _initActionsComplete;
    private static bool _cyclicActionsComplete;
    private static bool _exitActionsComplete;
    private static CheckTriggerDelegate _triggerDelegate;
    private static CheckLifetimeDelegate _checkLifetimeDelegate;

    public Behavior_9598143a_3b94_6c60_8d4a_ee7d3ec9c7eb()
    {
        Uid = "9598143a_3b94_6c60_8d4a_ee7d3ec9c7eb";


        // SET_PRIORITY
        Priority = BehaviorExecutionPriority.normal
;

        // SET_TRIGGER
        // The trigger delegate should not access any member variables
        _triggerDelegate = delegate(IBehaviorExecutionContext ctx, out TriggerResult result)
        {
            result = new TriggerResult();
            if (ctx != null)
            {
                var gestureInfo = ctx.GetGestureInfo("Greet_Right");
                if (gestureInfo.Active && gestureInfo.Confidence > 90)
                {
                    result.HumanId = gestureInfo.HumanId;
                    result.HumanInLoop = true;
                    return true;
                }

            }
            return false;
        };

        // SET_EXECUTION_LIFETIME
        ExecutionLifetime = BehaviorExecutionLifetime.forever;


        _checkLifetimeDelegate = CheckExecution;
    }

    private void SampleTriggerSetting()
    {
        // Gesture trigger
        _triggerDelegate = delegate(IBehaviorExecutionContext ctx, out TriggerResult result)
        {
            result = new TriggerResult();
            if (ctx != null)
            {
                var gestureInfo = ctx.GetGestureInfo("");
                if (gestureInfo.Active && gestureInfo.Confidence > 90)
                {
                    result.HumanId = gestureInfo.HumanId;
                    result.HumanInLoop = true;
                    return true;
                }
            }
            return false;
        };

        // Voice Trigger
        _triggerDelegate = delegate(IBehaviorExecutionContext ctx, out TriggerResult result)
        {
            result = new TriggerResult();
            if (ctx != null)
            {
                var voiceCommand = ctx.GetVoiceCommand("");
                if (voiceCommand.Active && voiceCommand.Confidence > 70)
                {
                    return true;
                }
            }
            return false;
        };
    }

    public bool CheckExecution(IBehaviorExecutionContext context)
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

    public static CheckTriggerDelegate TriggerDelegate
    {
        get { return _triggerDelegate; }
    }

    public static CheckLifetimeDelegate LifetimeDelegate
    {
        get { return _checkLifetimeDelegate; }
    }

    public bool ExecuteInit(IBehaviorExecutionContext context)
    {
        if (!InitActionsComplete)
        {
            // INIT_BLOCK
            var var_9cb50daa_e417_4525_8cc8_344c0b1b86e2 = new BehaviorInfo { BehaviorName = "crouch" };

            BehaviorModuleHelper.Execute(context, var_9cb50daa_e417_4525_8cc8_344c0b1b86e2);

            InitActionsComplete = true;
        }
        return InitActionsComplete;
    }

    public bool ExecuteCyclic(IBehaviorExecutionContext context)
    {
        if (!CyclicActionsComplete && InitActionsComplete)
        {
            // CYCLIC_BLOCK
            var var_9f18334c_a343_d5ab_b793_bffa1fc16270 = new BehaviorInfo { BehaviorName = "Say Expressively", Parameters = new Dictionary<string, object> { { "msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("text", true, "string") } } };

            BehaviorModuleHelper.Execute(context, var_9f18334c_a343_d5ab_b793_bffa1fc16270);

        }
        return CyclicActionsComplete;
    }

    public bool ExecuteExit(IBehaviorExecutionContext context)
    {
        if (!ExitActionsComplete && CyclicActionsComplete)
        {
            // EXIT_BLOCK
            var var_31c878bd_da36_bf47_99ae_163f09553e53 = new BehaviorInfo { BehaviorName = "Say Expressively", Parameters = new Dictionary<string, object> { { "msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("bye", true, "string") } } };

            BehaviorModuleHelper.Execute(context, var_31c878bd_da36_bf47_99ae_163f09553e53);

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
public class Behavior_e9272626_fdf9_c8ab_881b_5285a4ad1023 : ITriggerBehavior
{
    public string Name { get; set; }
    public static BehaviorExecutionPriority Priority { get; set; }
    public static BehaviorExecutionLifetime ExecutionLifetime { get; set; }
    public static string ExecutionEvalExpression { get; set; }
    public int Id { get; set; }
    public static string Uid { get; set; }
    private static bool _initActionsComplete;
    private static bool _cyclicActionsComplete;
    private static bool _exitActionsComplete;
    private static CheckTriggerDelegate _triggerDelegate;
    private static CheckLifetimeDelegate _checkLifetimeDelegate;

    public Behavior_e9272626_fdf9_c8ab_881b_5285a4ad1023()
    {
        Uid = "e9272626_fdf9_c8ab_881b_5285a4ad1023";


        // SET_PRIORITY
        Priority = BehaviorExecutionPriority.high
;

        // SET_TRIGGER
        // The trigger delegate should not access any member variables
        _triggerDelegate = delegate(IBehaviorExecutionContext ctx, out TriggerResult result)
        {
            result = new TriggerResult();
            if (ctx != null)
            {
                var voiceCommand = ctx.GetVoiceCommand("Stop");
                if (voiceCommand.Active && voiceCommand.Confidence > 70)
                {
                    return true;
                }

            }
            return false;
        };

        // SET_EXECUTION_LIFETIME
        ExecutionLifetime = BehaviorExecutionLifetime.once;


        _checkLifetimeDelegate = CheckExecution;
    }

    private void SampleTriggerSetting()
    {
        // Gesture trigger
        _triggerDelegate = delegate(IBehaviorExecutionContext ctx, out TriggerResult result)
        {
            result = new TriggerResult();
            if (ctx != null)
            {
                var gestureInfo = ctx.GetGestureInfo("");
                if (gestureInfo.Active && gestureInfo.Confidence > 90)
                {
                    result.HumanId = gestureInfo.HumanId;
                    result.HumanInLoop = true;
                    return true;
                }
            }
            return false;
        };

        // Voice Trigger
        _triggerDelegate = delegate(IBehaviorExecutionContext ctx, out TriggerResult result)
        {
            result = new TriggerResult();
            if (ctx != null)
            {
                var voiceCommand = ctx.GetVoiceCommand("");
                if (voiceCommand.Active && voiceCommand.Confidence > 70)
                {
                    return true;
                }
            }
            return false;
        };
    }

    public bool CheckExecution(IBehaviorExecutionContext context)
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

    public static CheckTriggerDelegate TriggerDelegate
    {
        get { return _triggerDelegate; }
    }

    public static CheckLifetimeDelegate LifetimeDelegate
    {
        get { return _checkLifetimeDelegate; }
    }

    public bool ExecuteInit(IBehaviorExecutionContext context)
    {
        if (!InitActionsComplete)
        {
            // INIT_BLOCK
            var var_2b4c68a5_eee5_1764_85da_f28d5d06bbc7 = new BehaviorInfo { BehaviorName = "Say Expressively", Parameters = new Dictionary<string, object> { { "msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("I will stop now!", true, "string") } } };

            BehaviorModuleHelper.Execute(context, var_2b4c68a5_eee5_1764_85da_f28d5d06bbc7);

            InitActionsComplete = true;
        }
        return InitActionsComplete;
    }

    public bool ExecuteCyclic(IBehaviorExecutionContext context)
    {
        if (!CyclicActionsComplete && InitActionsComplete)
        {
            // CYCLIC_BLOCK
            var var_be50873a_8e50_3c5f_8d33_6b45138104b5 = new BehaviorInfo { BehaviorName = "crouch" };

            BehaviorModuleHelper.Execute(context, var_be50873a_8e50_3c5f_8d33_6b45138104b5);

        }
        return CyclicActionsComplete;
    }

    public bool ExecuteExit(IBehaviorExecutionContext context)
    {
        if (!ExitActionsComplete && CyclicActionsComplete)
        {
            // EXIT_BLOCK
            var var_e4345253_94c4_58b4_980c_9a2441f92a2d = new BehaviorInfo { BehaviorName = "Say Expressively", Parameters = new Dictionary<string, object> { { "msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("bye", true, "string") } } };

            BehaviorModuleHelper.Execute(context, var_e4345253_94c4_58b4_980c_9a2441f92a2d);

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