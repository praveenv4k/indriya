// ReSharper disable RedundantUsingDirective
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

// Main Behavior Program

// ReSharper disable CheckNamespace

using System;

public class Behavior_ebf51ad4_62d1_ac61_b7a4_4b097fbc867a : ITriggerBehavior
{
    public string Name { get; set; }

    protected static BehaviorExecutionPriority Priority;

    public Behavior_ebf51ad4_62d1_ac61_b7a4_4b097fbc867a()
    {
        GetPriority();
        GetExecutionLifetime();
        GetUid();
    }

    public static BehaviorExecutionPriority GetPriority()
    {
        // SET_PRIORITY
        Priority = BehaviorExecutionPriority.normal;

        return Priority;
    }

    protected static BehaviorExecutionLifetime ExecutionLifetime;

    public static BehaviorExecutionLifetime GetExecutionLifetime()
    {
        // SET_EXECUTION_LIFETIME
        ExecutionLifetime = BehaviorExecutionLifetime.forever;

        return ExecutionLifetime;
    }

    public int Id { get; set; }

    protected static string Uid;

    public static string GetUid()
    {
        // SET_UID
        Uid = "ebf51ad4_62d1_ac61_b7a4_4b097fbc867a";

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
            var gestureInfoList = context.GetGestureInfoList("Greet_Left");
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
              var var_e13f4a25_80e3_f7f2_a729_20d6aee5d4ba= new BehaviorInfo
  {
  BehaviorName = "Move To",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"translation", BehaviorModuleHelper.CreateBehaviorParameterOptions("0", false, "float")},
  {"rotation", BehaviorModuleHelper.CreateBehaviorParameterOptions("1", false, "float")},
  {"human", BehaviorModuleHelper.CreateBehaviorParameterOptions("1", false, "float")},
  {"dist", BehaviorModuleHelper.CreateBehaviorParameterOptions(1.50, false, "float")},
  {"x", BehaviorModuleHelper.CreateBehaviorParameterOptions(0.0, true, "float")},
  {"y", BehaviorModuleHelper.CreateBehaviorParameterOptions(0.0, true, "float")},
  {"theta", BehaviorModuleHelper.CreateBehaviorParameterOptions(0.0, true, "float")}
  }
  };

  if (context.RefreshApproachParameters(var_e13f4a25_80e3_f7f2_a729_20d6aee5d4ba, trigger)) {
  BehaviorModuleHelper.Execute(context, var_e13f4a25_80e3_f7f2_a729_20d6aee5d4ba);
  }
  var var_32c9179f_0614_11f8_bd1a_a0649c1d0667= new BehaviorInfo
  {
  BehaviorName = "Move To",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"translation", BehaviorModuleHelper.CreateBehaviorParameterOptions("1", false, "float")},
  {"rotation", BehaviorModuleHelper.CreateBehaviorParameterOptions("0", false, "float")},
  {"human", BehaviorModuleHelper.CreateBehaviorParameterOptions("1", false, "float")},
  {"dist", BehaviorModuleHelper.CreateBehaviorParameterOptions(1.50, false, "float")},
  {"x", BehaviorModuleHelper.CreateBehaviorParameterOptions(1.50, true, "float")},
  {"y", BehaviorModuleHelper.CreateBehaviorParameterOptions(0.0, true, "float")},
  {"theta", BehaviorModuleHelper.CreateBehaviorParameterOptions(0.0, true, "float")}
  }
  };

  if (context.RefreshApproachParameters(var_32c9179f_0614_11f8_bd1a_a0649c1d0667, trigger)) {
  BehaviorModuleHelper.Execute(context, var_32c9179f_0614_11f8_bd1a_a0649c1d0667);
  }
  var var_d2a5e02f_8c19_33cc_b240_3413036630d9= new BehaviorInfo{BehaviorName = "wish",RobotName = "Hiro"};

  BehaviorModuleHelper.Execute(context, var_d2a5e02f_8c19_33cc_b240_3413036630d9);
  var var_4330a2d9_5d64_7429_b18b_06083d44a70c= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("I am Nao! Welcome to Edo-Tokyo museum.", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_4330a2d9_5d64_7429_b18b_06083d44a70c);
  var var_dcbc2f6b_2259_fd93_8d04_797fa191107c= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("The Edo-Tokyo museum is a museum of the history of Tokyo during the Edo period", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_dcbc2f6b_2259_fd93_8d04_797fa191107c);
  var var_d6b52600_4ab0_f757_af15_6dd8587e5942= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("It was established in 1993", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_d6b52600_4ab0_f757_af15_6dd8587e5942);
  var var_22bdaaf8_a7e1_dca9_b981_f684fe9a8dc3= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("It has lifetime replica of the Nihonbashi, which was the bridge leading into Edo", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_22bdaaf8_a7e1_dca9_b981_f684fe9a8dc3);
  var var_6bb0f235_782b_5862_b6ac_80bd1345d345= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("It also has scaled down models of towns and building from the Edo, Meiji and Showa periods", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_6bb0f235_782b_5862_b6ac_80bd1345d345);
  var var_37cdbb14_89b3_3d26_a4a5_a1d9bc2ec861= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("The museum was designed by Kiyonori Kikutake", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_37cdbb14_89b3_3d26_a4a5_a1d9bc2ec861);
  var var_2c28ab2f_d8fa_9b1f_820e_bd3f802bf637= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("I hope you will enjoy your visit to Edo-Tokyo museum", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_2c28ab2f_d8fa_9b1f_820e_bd3f802bf637);
  var var_c76e0ccc_3577_ba62_9f4d_394436f0b6cc= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("Have a nice day!", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_c76e0ccc_3577_ba62_9f4d_394436f0b6cc);


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