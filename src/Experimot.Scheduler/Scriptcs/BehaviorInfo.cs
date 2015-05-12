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


public class MotionBasedBehavior
{
    public MotionBasedBehavior()
    {
        Name = string.Empty;
        Trigger = string.Empty;
        Priority = BehaviorExecutionPriority.normal;

        RobotActions = new List<BehaviorInfo>();
    }

    public string Name { get; set; }
    public BehaviorExecutionPriority Priority { get; set; }
    public string Trigger { get; set; }
    public int ConfidenceLevel { get; set; }
    public IList<BehaviorInfo> RobotActions { get; set; }
}