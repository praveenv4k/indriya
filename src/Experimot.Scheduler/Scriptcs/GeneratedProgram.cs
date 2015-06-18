// ReSharper disable RedundantUsingDirective
using System;
using System.Collections.Generic;

// Main Behavior Program

using System;
using NetMQ.zmq;

public class Behavior_20883956_6d3d_d340_a8d8_376167488600 : ITriggerBehavior
{
    public string Name { get; set; }

    protected static BehaviorExecutionPriority Priority;

    public Behavior_20883956_6d3d_d340_a8d8_376167488600()
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
        Uid = "20883956_6d3d_d340_a8d8_376167488600";

        return Uid;
    }

    private static bool _initActionsComplete;
    private static bool _cyclicActionsComplete;
    private static bool _exitActionsComplete;

    public static TriggerResult CheckTrigger(IBehaviorExecutionContext ctx)
    {
        var result = new TriggerResult { Active = false };
        if (ctx != null)
        {

        }
        return result;
    }

    public bool ExecutionUntil(IBehaviorExecutionContext ctx)
    {
        if (ctx != null)
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

    //public static void VoiceChoices(IBehaviorExecutionContext context)
    //{
    //    if (context != null)
    //    {
    //        while (true)
    //        {
    //            var voiceChoicesResponse = context.GetVoiceCommand();
    //            if (voiceChoicesResponse.Active && voiceChoicesResponse.Confidence > 0)
    //            {
    //                string dummyVar1;
    //                string dummyVar2;
    //                if (String.Compare(dummyVar1, voiceChoicesResponse.Name, StringComparison.OrdinalIgnoreCase))
    //                {
    //                    // DO_CHOICE1_HERE
    //                    break;
    //                }
    //                if (String.Compare(dummyVar2, voiceChoicesResponse.Name, StringComparison.OrdinalIgnoreCase))
    //                {
    //                    // DO_CHOICE2_HERE
    //                    break;
    //                }
    //            }
    //        }
    //    }
    //}

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
            while (true)
            {
                var var_fea8a8d8_9880_a1f2_abe1_d59380d60f13 = context.GetVoiceCommand();
                if (var_fea8a8d8_9880_a1f2_abe1_d59380d60f13.Active &&
                    var_fea8a8d8_9880_a1f2_abe1_d59380d60f13.Confidence > 0)
                {
                    string var_69cee829_8c79_7027_be42_1aadb31fccf8 = var_fea8a8d8_9880_a1f2_abe1_d59380d60f13.Name;
                    string var_98c4457c_0681_d379_99e0_dea541d5bb87 = "YES";
                    string var_1b3b1847_4ec5_2093_81fc_912e3b185169 = "NO";
                    if (
                        String.Compare(var_98c4457c_0681_d379_99e0_dea541d5bb87,
                            var_69cee829_8c79_7027_be42_1aadb31fccf8, StringComparison.OrdinalIgnoreCase) == 0)
                    {
                        var var_69cd4db0_4a88_4352_a165_9e17b4555f68 = new BehaviorInfo
                        {
                            BehaviorName = "Say Expressively",
                            Parameters =
                                new Dictionary<string, object>
                                {
                                    {
                                        "msg",
                                        BehaviorModuleHelper.CreateBehaviorParameterOptions("You said yes!", true,
                                            "string")
                                    }
                                }
                        };

                        BehaviorModuleHelper.Execute(context, var_69cd4db0_4a88_4352_a165_9e17b4555f68);

                        break;
                    }
                    if (
                        String.Compare(var_1b3b1847_4ec5_2093_81fc_912e3b185169,
                            var_69cee829_8c79_7027_be42_1aadb31fccf8, StringComparison.OrdinalIgnoreCase) == 0)
                    {
                        var var_0aef8516_5f5a_783a_ad61_669a6ff5dcd4 = new BehaviorInfo
                        {
                            BehaviorName = "Say Expressively",
                            Parameters =
                                new Dictionary<string, object>
                                {
                                    {
                                        "msg",
                                        BehaviorModuleHelper.CreateBehaviorParameterOptions("You said no!", true,
                                            "string")
                                    }
                                }
                        };

                        BehaviorModuleHelper.Execute(context, var_0aef8516_5f5a_783a_ad61_669a6ff5dcd4);

                        break;
                    }
                }
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
        System.Console.WriteLine(@"Lifetime: {3} Init : {0}, Cyclic: {1}, Exit: {2}", InitActionsComplete,
            CyclicActionsComplete,
            ExitActionsComplete, ExecutionLifetime);
        return ExecutionComplete;
    }
}