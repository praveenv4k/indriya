// ReSharper disable RedundantUsingDirective
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

// Main Behavior Program

dynamic count;


public class StartupBehavior : IExecuteOnceBehavior
{
    public void Execute(IBehaviorExecutionContext context)
    {
        // STARTUP_BLOCK
          var var_6717280f_6dd1_692b_860c_f3d59bee0edb= new BehaviorInfo{BehaviorName = "stand",RobotName = "Hiro"};

  BehaviorModuleHelper.Execute(context, var_6717280f_6dd1_692b_860c_f3d59bee0edb);
  var var_bb61d711_7af2_c618_870c_a7505dff05e5= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("Hello! I am Nao!", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_bb61d711_7af2_c618_870c_a7505dff05e5);
  var var_778f900e_0853_13a8_b1b6_7e19fdddcb83= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("The doctor asked me to guide your therapy today!", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_778f900e_0853_13a8_b1b6_7e19fdddcb83);
  var var_0c670167_94d8_aedf_969e_a493738905fe= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("At first I will demonstrate the exercise routine", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_0c670167_94d8_aedf_969e_a493738905fe);
  var var_d666dcfe_0bac_4133_b1a5_42b8b29891eb= new BehaviorInfo{BehaviorName = "liftLeftHand",RobotName = "Hiro"};

  BehaviorModuleHelper.Execute(context, var_d666dcfe_0bac_4133_b1a5_42b8b29891eb);
  var var_ded8b18b_cca7_3037_b4dd_04885555a3b8= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("Please do this exercise five times. I will count for you!", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_ded8b18b_cca7_3037_b4dd_04885555a3b8);
  var var_9affd26b_d86e_7ed7_b48f_9393f29c83cf= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("Make yourself comfortable", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_9affd26b_d86e_7ed7_b48f_9393f29c83cf);
  var var_fc085727_4d3e_6efc_96fa_231ffb70bae4= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("Start doing the routine slowly", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_fc085727_4d3e_6efc_96fa_231ffb70bae4);
  count = 0;

    }
}
// ReSharper disable CheckNamespace

using System;

public class Behavior_da046cfe_9ef0_ec65_a2cc_dfb938de8921 : ITriggerBehavior
{
    public string Name { get; set; }

    protected static BehaviorExecutionPriority Priority;

    public Behavior_da046cfe_9ef0_ec65_a2cc_dfb938de8921()
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
        ExecutionLifetime = BehaviorExecutionLifetime.until;

        return ExecutionLifetime;
    }

    public int Id { get; set; }

    protected static string Uid;

    public static string GetUid()
    {
        // SET_UID
        Uid = "da046cfe_9ef0_ec65_a2cc_dfb938de8921";

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
            var gestureInfoList = context.GetGestureInfoList("LiftHand_Left");
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
            return (count <= 5);
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
              if (count == 1) {
    var var_4cb4bb22_b20c_ffff_82d4_9a629b6d9712= string.Format("You have completed the exercise {0}  time!",count);
    var var_aab31148_d989_dbc4_99a9_607c437ff1f9= new BehaviorInfo
    {
    BehaviorName = "Say Expressively",
    RobotName = "Hiro",Parameters = new Dictionary<string, object>
    {
    {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions(var_4cb4bb22_b20c_ffff_82d4_9a629b6d9712, true, "string")},
    }
    };

    BehaviorModuleHelper.Execute(context, var_aab31148_d989_dbc4_99a9_607c437ff1f9);
  } else {
    var var_474e66e3_dfef_9670_b4a0_9dca1102d7ba= string.Format("You have completed the exercise {0}  times!",count);
    var var_64f27bb6_60e3_0d16_b68b_52c3ee3e11ed= new BehaviorInfo
    {
    BehaviorName = "Say Expressively",
    RobotName = "Hiro",Parameters = new Dictionary<string, object>
    {
    {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions(var_474e66e3_dfef_9670_b4a0_9dca1102d7ba, true, "string")},
    }
    };

    BehaviorModuleHelper.Execute(context, var_64f27bb6_60e3_0d16_b68b_52c3ee3e11ed);
  }



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
          var var_75eef517_3148_a1f8_9ac8_3401e951ac76= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("You did a great job today!", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_75eef517_3148_a1f8_9ac8_3401e951ac76);
  var var_11dadac2_feb0_e652_9e9a_9aeded062c88= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("I am looking forward to guide you next time.", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_11dadac2_feb0_e652_9e9a_9aeded062c88);
  var var_57f046be_007c_da14_877a_07dc80a6e261= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("Thank you and have a nice day!", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_57f046be_007c_da14_877a_07dc80a6e261);

    }
}