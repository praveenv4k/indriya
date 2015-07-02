// ReSharper disable RedundantUsingDirective
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

// Main Behavior Program

public class StartupBehavior : IExecuteOnceBehavior
{
    public void Execute(IBehaviorExecutionContext context)
    {
        // STARTUP_BLOCK
          var var_e1cb239b_6a8e_ce38_9b95_c93329855ecb= new BehaviorInfo{BehaviorName = "Greet",RobotName = "Hiro"};

  BehaviorModuleHelper.Execute(context, var_e1cb239b_6a8e_ce38_9b95_c93329855ecb);

    }
}
// ReSharper disable CheckNamespace

using System;

public class Behavior_b17d0044_6297_7b9a_8e11_3be035e9a5cb : ITriggerBehavior
{
    public string Name { get; set; }

    protected static BehaviorExecutionPriority Priority;

    public Behavior_b17d0044_6297_7b9a_8e11_3be035e9a5cb()
    {
        GetPriority();
        GetExecutionLifetime();
        GetUid();
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
        ExecutionLifetime = BehaviorExecutionLifetime.once;

        return ExecutionLifetime;
    }

    public int Id { get; set; }

    protected static string Uid;

    public static string GetUid()
    {
        // SET_UID
        Uid = "b17d0044_6297_7b9a_8e11_3be035e9a5cb";

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
            var gestureInfoList = context.GetGestureInfoList("Greet_Right");
var gestureInfo = gestureInfoList.FirstOrDefault(s=>s.Confidence > 90);
if (gestureInfo.Active && gestureInfo.Confidence > 90)
{
Console.WriteLine("Gesture trigger received : {0} - {1}", gestureInfo.Name, gestureInfo.Confidence);
result.HumanId = gestureInfo.HumanId;
result.HumanInLoop = true;
result.Active = true;
}

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
              var var_cd81f561_1c78_d528_bd69_1589aa129849= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("big up i am gangsta nao", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_cd81f561_1c78_d528_bd69_1589aa129849);


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
// ReSharper disable CheckNamespace

using System;

public class Behavior_3f926c31_c0eb_ff61_bf7c_a17928fadef4 : ITriggerBehavior
{
    public string Name { get; set; }

    protected static BehaviorExecutionPriority Priority;

    public Behavior_3f926c31_c0eb_ff61_bf7c_a17928fadef4()
    {
        GetPriority();
        GetExecutionLifetime();
        GetUid();
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
        ExecutionLifetime = BehaviorExecutionLifetime.once;

        return ExecutionLifetime;
    }

    public int Id { get; set; }

    protected static string Uid;

    public static string GetUid()
    {
        // SET_UID
        Uid = "3f926c31_c0eb_ff61_bf7c_a17928fadef4";

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
            var voiceCommand = context.GetVoiceCommand("START");
if (voiceCommand.Active && voiceCommand.Confidence > 80)
{
Console.WriteLine("Voice trigger received : {0} - {1}", voiceCommand.Name, voiceCommand.Confidence);
result.Active = true;
}

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
              var var_90ba2d5f_d55a_85c7_bee2_bf5a19adeb83= new BehaviorInfo
  {
  BehaviorName = "Move To",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"x", BehaviorModuleHelper.CreateBehaviorParameterOptions(0.5, false, "float")},
  {"y", BehaviorModuleHelper.CreateBehaviorParameterOptions(0.0, false, "float")},
  {"theta", BehaviorModuleHelper.CreateBehaviorParameterOptions(0.0, false, "float")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_90ba2d5f_d55a_85c7_bee2_bf5a19adeb83);


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
public class ExitBehavior : IExecuteOnceBehavior
{
    public void Execute(IBehaviorExecutionContext context)
    {
        // EXIT_BLOCK
          var var_6ef89b51_4051_397a_8363_12eac6b640c4= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("peace i am out ", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_6ef89b51_4051_397a_8363_12eac6b640c4);

    }
}