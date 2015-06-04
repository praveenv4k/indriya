using System;
using System.Collections.Generic;
using System.Runtime;
using System.Text;
using Common.Logging;
using NetMQ;

public class BehaviorInfo: ICloneable
{
    private static readonly ILog Log = LogManager.GetLogger(typeof(SimpleBehaviorTask));
    public BehaviorInfo()
    {
        Parameters = new Dictionary<string, object>();
    }

    public string ModuleName { get; set; }
    public string Ip { get; set; }
    public int Port { get; set; }
    public string BehaviorName { get; set; }
    public string FunctionName { get; set; }
    public IDictionary<string, object> Parameters { get; set; }
    public string ExecutionEvalExpression { get; set; }

    public override string ToString()
    {
        var builder = new StringBuilder();
        builder.Append(string.Format("Name :{0}, Function: {1}", BehaviorName, FunctionName))
            .AppendLine()
            .Append(string.Format("Module :{0}, Address: {1}:{2}", ModuleName, Ip, Port))
            .AppendLine()
            .Append("Parameters")
            .AppendLine();
        foreach (var parameter in Parameters)
        {
            var valueDict = parameter.Value as Dictionary<string, object>;
            builder.Append(string.Format("Key: {0}, Value:{1}", parameter.Key, valueDict!=null?valueDict["value"]:"Emptys"
                )).AppendLine();
        }
        return builder.ToString();
    }

    public object Clone()
    {
        return MemberwiseClone();
    }
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
    private bool _initActionsComplete;
    private bool _cyclicActionsComplete;
    private bool _exitActionsComplete;
    private bool _executionComplete;

    public MotionBasedBehavior()
    {
        Name = string.Empty;
        Trigger = string.Empty;
        Priority = BehaviorExecutionPriority.normal;

        InitActions = new List<BehaviorInfo>();
        RobotActions = new List<BehaviorInfo>();
        ExitActions = new List<BehaviorInfo>();

        InitActionsComplete = false;
        ExitActionsComplete = false;
        CyclicActionsComplete = false;
    }

    public string Name { get; set; }
    public BehaviorType BehaviorType { get; set; }
    public BehaviorExecutionPriority Priority { get; set; }
    public BehaviorExecutionLifetime ExecutionLifetime { get; set; }
    public string ExecutionEvalExpression { get; set; }
    public string Trigger { get; set; }
    public string TriggerCountVariable { get; set; }
    public int Id { get; set; }
    public Guid Guid { get; set; }
    public int ConfidenceLevel { get; set; }
    public IList<BehaviorInfo> InitActions { get; set; }

    public bool InitActionsComplete
    {
        get { return _initActionsComplete; }
        set { _initActionsComplete = value; }
    }

    public IList<BehaviorInfo> RobotActions { get; set; }

    public bool CyclicActionsComplete
    {
        get { return _cyclicActionsComplete; }
        set { _cyclicActionsComplete = value; }
    }

    public IList<BehaviorInfo> ExitActions { get; set; }

    public bool ExitActionsComplete
    {
        get { return _exitActionsComplete; }
        set { _exitActionsComplete = value; }
    }

    public bool ExecutionComplete
    {
        get { return InitActionsComplete & CyclicActionsComplete & ExitActionsComplete; }
    }

    public object Clone()
    {
        return MemberwiseClone();
    }

}