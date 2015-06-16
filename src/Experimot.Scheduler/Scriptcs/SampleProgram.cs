using System.Collections.Generic;
using NCalc;

public class StartupBehavior : IExecuteOnceBehavior
{
    public void Execute(IBehaviorExecutionContext context)
    {
        // STARTUP_BLOCK
        var var_20644961_5b1e_984c_a019_7c9bd00fdc17 = new BehaviorInfo { BehaviorName = "greet" };

        BehaviorModuleHelper.Execute(context, var_20644961_5b1e_984c_a019_7c9bd00fdc17);

    }
}


public class Behavior_f60ffa5d_c813_8f0c_ae4b_4c3336c83c46 : ITriggerBehavior
{
    public string Name { get; set; }
    public BehaviorExecutionPriority Priority { get; set; }
    public BehaviorExecutionLifetime ExecutionLifetime { get; set; }
    public string ExecutionEvalExpression { get; set; }
    public string Trigger { get; set; }
    public int Id { get; set; }
    public string Uid { get; set; }
    private static bool _initActionsComplete;
    private static bool _cyclicActionsComplete;
    private static bool _exitActionsComplete;
    private static CheckTriggerDelegate _triggerDelegate;
    private readonly CheckLifetimeDelegate _checkLifetimeDelegate;

    public Behavior_f60ffa5d_c813_8f0c_ae4b_4c3336c83c46()
    {
        Uid = "f60ffa5d_c813_8f0c_ae4b_4c3336c83c46";


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

    public bool InitActionsComplete
    {
        get { return _initActionsComplete; }
        set { _initActionsComplete = value; }
    }

    public bool CyclicActionsComplete
    {
        get { return _cyclicActionsComplete; }
        set { _cyclicActionsComplete = value; }
    }

    public bool ExitActionsComplete
    {
        get { return _exitActionsComplete; }
        set { _exitActionsComplete = value; }
    }

    public bool ExecutionComplete
    {
        get { return InitActionsComplete & CyclicActionsComplete & ExitActionsComplete; }
    }

    public CheckTriggerDelegate TriggerDelegate
    {
        get { return _triggerDelegate; }
    }

    public CheckLifetimeDelegate LifetimeDelegate
    {
        get { return _checkLifetimeDelegate; }
    }

    public bool ExecuteInit(IBehaviorExecutionContext context)
    {
        if (!InitActionsComplete)
        {
            // INIT_BLOCK
            var var_50e59e99_2026_eaa6_943f_8e5dea7a4978 = new BehaviorInfo { BehaviorName = "greet" };

            BehaviorModuleHelper.Execute(context, var_50e59e99_2026_eaa6_943f_8e5dea7a4978);

            InitActionsComplete = true;
        }
        return InitActionsComplete;
    }

    public bool ExecuteCyclic(IBehaviorExecutionContext context)
    {
        if (!CyclicActionsComplete && InitActionsComplete)
        {
            // CYCLIC_BLOCK
            var var_296185e2_597b_ded0_914e_d9c22ab2334c = new BehaviorInfo { BehaviorName = "greet" };

            BehaviorModuleHelper.Execute(context, var_296185e2_597b_ded0_914e_d9c22ab2334c);
            var var_8fa0281c_0bad_a04a_8451_21b9c502e4b3 = new BehaviorInfo
            {
                BehaviorName = "Say Expressively",
                Parameters =
                    new Dictionary<string, object>
                    {
                        {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("text", true, "string")}
                    }
            };

            BehaviorModuleHelper.Execute(context, var_8fa0281c_0bad_a04a_8451_21b9c502e4b3);

        }
        return CyclicActionsComplete;
    }

    public bool ExecuteExit(IBehaviorExecutionContext context)
    {
        if (!ExitActionsComplete && CyclicActionsComplete)
        {
            // EXIT_BLOCK
            var var_5d520a9a_61ed_4728_b60c_eefb8e2f649a = new BehaviorInfo { BehaviorName = "greet" };

            BehaviorModuleHelper.Execute(context, var_5d520a9a_61ed_4728_b60c_eefb8e2f649a);

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
        var var_033ba942_6049_9176_bfcf_4e9391bee757 = new BehaviorInfo { BehaviorName = "greet" };

        BehaviorModuleHelper.Execute(context, var_033ba942_6049_9176_bfcf_4e9391bee757);

    }
}