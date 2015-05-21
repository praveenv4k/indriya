using System;
using System.Collections.Generic;
using Common.Logging;
using NetMQ;

public class BehaviorInfo
{
    public BehaviorInfo()
    {
        Parameters = new Dictionary<string, object>();
    }

    public string ModuleName { get; set; }
    public string Ip { get; set; }
    public int Port { get; set; }
    public string BehaviorName { get; set; }
    public IDictionary<string, object> Parameters { get; set; } 
}

public enum BehaviorExecutionPriority
{
    low,
    normal,
    high
}

public enum BehaviorExecutionLifetime
{
    forever,
    once,
    until
}

public enum BehaviorType
{
    Startup,
    Behavior,
    Exit
}

public class MotionBasedBehavior : ICloneable
{
    public MotionBasedBehavior()
    {
        Name = string.Empty;
        Trigger = string.Empty;
        Priority = BehaviorExecutionPriority.normal;

        InitActions = new List<BehaviorInfo>();
        RobotActions = new List<BehaviorInfo>();
        ExitActions = new List<BehaviorInfo>();
    }

    public string Name { get; set; }
    public BehaviorType BehaviorType { get; set; }
    public BehaviorExecutionPriority Priority { get; set; }
    public BehaviorExecutionLifetime ExecutionLifetime { get; set; }
    public string ExecutionEvalExpression { get; set; }
    public string Trigger { get; set; }
    public string TriggerCount { get; set; }
    public int Id { get; set; }
    public Guid Guid { get; set; }
    public int ConfidenceLevel { get; set; }
    public IList<BehaviorInfo> InitActions { get; set; }
    public IList<BehaviorInfo> RobotActions { get; set; }
    public IList<BehaviorInfo> ExitActions { get; set; }

    public object Clone()
    {
        var cloned = this.MemberwiseClone() as MotionBasedBehavior;
        return cloned;
    }
}