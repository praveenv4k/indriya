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
          var var_862fef01_d556_1537_a12a_be89ce762dfd = new List<Task>();
  var var_aca01bc5_b6ef_6c67_aa3c_f065ee993a92 = new Action( () =>
  {
    var var_3641a8a3_6179_2204_b150_d7359fe9260c= new BehaviorInfo{BehaviorName = "Greet",RobotName = "Hiro"};

    BehaviorModuleHelper.Execute(context, var_3641a8a3_6179_2204_b150_d7359fe9260c);

  });
  var var_853bcb58_acf7_ceb1_ab72_ee040ea19571 = new Action( () =>
  {
    var var_5ab5d4fd_7fe4_ff71_bc15_6f483055047c= new BehaviorInfo{BehaviorName = "Greet",RobotName = "Taro"};

    BehaviorModuleHelper.Execute(context, var_5ab5d4fd_7fe4_ff71_bc15_6f483055047c);

  });
  var_862fef01_d556_1537_a12a_be89ce762dfd.Add(Task.Run(var_aca01bc5_b6ef_6c67_aa3c_f065ee993a92));
  var_862fef01_d556_1537_a12a_be89ce762dfd.Add(Task.Run(var_853bcb58_acf7_ceb1_ab72_ee040ea19571));
  Task.WaitAll(var_862fef01_d556_1537_a12a_be89ce762dfd.ToArray());
  System.Console.WriteLine("Parallel action execution complete");var var_bf59f011_690d_eb2a_9701_a0bdf52ee6bd= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("I am Hiro", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_bf59f011_690d_eb2a_9701_a0bdf52ee6bd);
  var var_c01098b4_a9e2_468c_8b91_f8829c4d6fa3= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Taro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("And I am Taro", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_c01098b4_a9e2_468c_8b91_f8829c4d6fa3);
  var var_567e0153_ac87_6f4d_9b5d_bf0c1d2ddb8a= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("We want to introduce Indriya system. Taro, you want to start?", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_567e0153_ac87_6f4d_9b5d_bf0c1d2ddb8a);
  var var_ec1499f8_bafe_1869_a3da_24666d86581a= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Taro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("Yes sure.", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_ec1499f8_bafe_1869_a3da_24666d86581a);
  var var_1c66ef30_587d_b0fa_8fc9_1078f8201e7f= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Taro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("Indriya helps to design interaction scenario based on human behaviors", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_1c66ef30_587d_b0fa_8fc9_1078f8201e7f);
  var var_f3e0ffd0_259b_cec5_b455_c81c99bb5039= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("That's right! You can design program to respond to a gesture", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_f3e0ffd0_259b_cec5_b455_c81c99bb5039);
  var var_4eb698cb_6291_358a_b56d_7fe3c5a78cdf= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Taro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("And also to a voice command from the user", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_4eb698cb_6291_358a_b56d_7fe3c5a78cdf);
  var var_f119e276_0793_879e_80de_6ad27c0761d2= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("You can also program two robots operate in parallel", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_f119e276_0793_879e_80de_6ad27c0761d2);
  var var_62cddfa4_0f75_ef4a_8abe_531b414a056e= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Taro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("And finally you can design behaviors with priority", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_62cddfa4_0f75_ef4a_8abe_531b414a056e);
  var var_08335cda_77da_928e_8cc1_c80cc61c2753= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("If you want both of us to dance together, wave your right or left hand", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_08335cda_77da_928e_8cc1_c80cc61c2753);
  var var_8d75c052_b97a_1a4b_adea_5ab215014397= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Taro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("If you want to interrupt at any time, say STOP loudly", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_8d75c052_b97a_1a4b_adea_5ab215014397);

    }
}
// ReSharper disable CheckNamespace

using System;

public class Behavior_2d4feb47_5e06_1dc9_b61b_04482ccfcdf5 : ITriggerBehavior
{
    public string Name { get; set; }

    protected static BehaviorExecutionPriority Priority;

    public Behavior_2d4feb47_5e06_1dc9_b61b_04482ccfcdf5()
    {
        GetPriority();
        GetExecutionLifetime();
        GetUid();
    }

    public static BehaviorExecutionPriority GetPriority()
    {
        // SET_PRIORITY
        Priority = BehaviorExecutionPriority.high;

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
        Uid = "2d4feb47_5e06_1dc9_b61b_04482ccfcdf5";

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
            var voiceCommand = context.GetVoiceCommand("STOP");
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
              var var_af0d9ba5_7f8e_6560_8d24_b70a9ba0510b= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Hiro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("Taro, we received a stop command.", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_af0d9ba5_7f8e_6560_8d24_b70a9ba0510b);
  var var_3e5335a3_9a1f_a44a_be41_4d9a6ea6e64b= new BehaviorInfo
  {
  BehaviorName = "Say Expressively",
  RobotName = "Taro",Parameters = new Dictionary<string, object>
  {
  {"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions("Yes, Let us go to rest position", true, "string")}
  }
  };

  BehaviorModuleHelper.Execute(context, var_3e5335a3_9a1f_a44a_be41_4d9a6ea6e64b);
  var var_aa5dbbc8_6eea_8066_b55f_b7d1125178e2 = new List<Task>();
  var var_71a15906_a3c2_8bd7_9262_a96cf5b603aa = new Action( () =>
  {
    var var_eba9448d_1a8b_7cea_9257_b15d34f07cc1= new BehaviorInfo
    {
    BehaviorName = "Take Rest",
    RobotName = "Hiro",Parameters = new Dictionary<string, object>()
    };

    BehaviorModuleHelper.Execute(context, var_eba9448d_1a8b_7cea_9257_b15d34f07cc1);

  });
  var var_67c4371e_7f29_7ef8_83de_ba7819f3b264 = new Action( () =>
  {
    var var_189a9b7e_37dc_f4b2_9a38_b8bdbc780275= new BehaviorInfo
    {
    BehaviorName = "Take Rest",
    RobotName = "Taro",Parameters = new Dictionary<string, object>()
    };

    BehaviorModuleHelper.Execute(context, var_189a9b7e_37dc_f4b2_9a38_b8bdbc780275);

  });
  var_aa5dbbc8_6eea_8066_b55f_b7d1125178e2.Add(Task.Run(var_71a15906_a3c2_8bd7_9262_a96cf5b603aa));
  var_aa5dbbc8_6eea_8066_b55f_b7d1125178e2.Add(Task.Run(var_67c4371e_7f29_7ef8_83de_ba7819f3b264));
  Task.WaitAll(var_aa5dbbc8_6eea_8066_b55f_b7d1125178e2.ToArray());
  System.Console.WriteLine("Parallel action execution complete");

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

public class Behavior_cee3cc18_72f6_a236_b835_f0d2683cfac8 : ITriggerBehavior
{
    public string Name { get; set; }

    protected static BehaviorExecutionPriority Priority;

    public Behavior_cee3cc18_72f6_a236_b835_f0d2683cfac8()
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
        ExecutionLifetime = BehaviorExecutionLifetime.forever;

        return ExecutionLifetime;
    }

    public int Id { get; set; }

    protected static string Uid;

    public static string GetUid()
    {
        // SET_UID
        Uid = "cee3cc18_72f6_a236_b835_f0d2683cfac8";

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
            (var gestureInfoList = context.GetGestureInfoList("Greet_Right");
var gestureInfo = gestureInfoList.FirstOrDefault(s=>s.Confidence > 90);
if (gestureInfo.Active && gestureInfo.Confidence > 90)
{
Console.WriteLine("Gesture trigger received : {0} - {1}", gestureInfo.Name, gestureInfo.Confidence);
result.HumanId = gestureInfo.HumanId;
result.HumanInLoop = true;
result.Active = true;
}
 || var gestureInfoList = context.GetGestureInfoList("Greet_Left");
var gestureInfo = gestureInfoList.FirstOrDefault(s=>s.Confidence > 90);
if (gestureInfo.Active && gestureInfo.Confidence > 90)
{
Console.WriteLine("Gesture trigger received : {0} - {1}", gestureInfo.Name, gestureInfo.Confidence);
result.HumanId = gestureInfo.HumanId;
result.HumanInLoop = true;
result.Active = true;
}
)
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
              var var_ebbaffde_15bc_9860_a6bf_509b6d6a59a6 = new List<Task>();
  var var_c9a06f4b_8778_dcec_bbc4_38221887afe2 = new Action( () =>
  {
    var var_58933fdd_5ef9_050e_8b8c_4bbd0c74246c= new BehaviorInfo{BehaviorName = "Dance",RobotName = "Hiro"};

    BehaviorModuleHelper.Execute(context, var_58933fdd_5ef9_050e_8b8c_4bbd0c74246c);

  });
  var var_b0843968_09f4_bf69_b462_30f80c3d6d92 = new Action( () =>
  {
    var var_73dea3ca_51c6_79be_8608_d6d0d2e3743b= new BehaviorInfo{BehaviorName = "Dance",RobotName = "Taro"};

    BehaviorModuleHelper.Execute(context, var_73dea3ca_51c6_79be_8608_d6d0d2e3743b);

  });
  var_ebbaffde_15bc_9860_a6bf_509b6d6a59a6.Add(Task.Run(var_c9a06f4b_8778_dcec_bbc4_38221887afe2));
  var_ebbaffde_15bc_9860_a6bf_509b6d6a59a6.Add(Task.Run(var_b0843968_09f4_bf69_b462_30f80c3d6d92));
  Task.WaitAll(var_ebbaffde_15bc_9860_a6bf_509b6d6a59a6.ToArray());
  System.Console.WriteLine("Parallel action execution complete");

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