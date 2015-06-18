public interface IBehaviorExecutionContext
{
    string ContextServer { get; set; }
    bool GetHumanExists();
    void GetNearestHuman(out int id, out double distance);
    void GetRelativePose(int id, out double dx, out double dy, out double dTheta);
    bool CheckHumanProximity(double threshold, out int id);
    void UpdateBehaviorResponderInfo(BehaviorInfo info);
    void SyncExecuteBehavior(BehaviorInfo behaviorInfo);
    bool RefreshApproachParameters(BehaviorInfo behaviorInfo, TriggerResult trigger);
    GestureInfo GetGestureInfo(string gestureName);
    VoiceCommandInfo GetVoiceCommand(string voiceCommand);
    VoiceCommandInfo GetVoiceCommand();
}