using System;
using System.Collections.Generic;
using NCalc;

public class BehaviorTemplate: ITriggerBehavior
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

    public BehaviorTemplate()
    {
        // SET_UID

        // SET_PRIORITY
        // SET_PRIORITY_HERE

        // SET_TRIGGER
        // The trigger delegate should not access any member variables
        _triggerDelegate = delegate(IBehaviorExecutionContext ctx, out TriggerResult result)
        {
            result = new TriggerResult();
            if (ctx != null)
            {
                // SET_TRIGGER_HERE
            }
            return false;
        };

        // SET_EXECUTION_LIFETIME
        // SET_EXECUTION_LIFETIME_HERE

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
            // INIT_BLOCK_HERE
            InitActionsComplete = true;
        }
        return InitActionsComplete;
    }

    public bool ExecuteCyclic(IBehaviorExecutionContext context)
    {
        if (!CyclicActionsComplete && InitActionsComplete)
        {
            // CYCLIC_BLOCK
            // CYCLIC_BLOCK_HERE
        }
        return CyclicActionsComplete;
    }

    public bool ExecuteExit(IBehaviorExecutionContext context)
    {
        if (!ExitActionsComplete && CyclicActionsComplete)
        {
            // EXIT_BLOCK
            // EXIT_BLOCK_HERE
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