public interface IBehaviorExecutionContext
{
    string ContextServer { get; }
    bool GetHumanExists();
    void GetNearestHuman(out int id, out double distance);
    void GetRelativePose(int id, out double dx, out double dy, out double dTheta);
    bool CheckHumanProximity(double threshold, out int id);
    void UpdateBehaviorResponderInfo(BehaviorInfo info);
    void SyncExecuteBehavior(BehaviorInfo behaviorInfo);
    bool RefreshApproachParameters(BehaviorInfo behaviorInfo, TriggerResult trigger);
    bool CancelRequest { get; set; }
    GestureInfo GetGestureInfo(string gestureName);
    VoiceCommandInfo GetVoiceCommand(string voiceCommand);
    VoiceCommandInfo GetVoiceCommand();
}

public class BehaviorCanceledException : System.Exception
{
    public BehaviorCanceledException()
    {

    }

    public BehaviorCanceledException(string message) : base(message)
    {

    }

    public BehaviorCanceledException(string message, System.Exception inner) : base(message, inner)
    {

    }
}