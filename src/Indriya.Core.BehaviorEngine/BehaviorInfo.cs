using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common.Logging;

namespace Indriya.Core.BehaviorEngine
{
    public class BehaviorInfo : ICloneable
    {
        //private static readonly ILog Log = LogManager.GetLogger(typeof (BehaviorInfo));

        public BehaviorInfo()
        {
            Parameters = new Dictionary<string, object>();
        }

        public string ModuleName { get; set; }
        public string Ip { get; set; }
        public int Port { get; set; }
        public string BehaviorName { get; set; }
        public string RobotName { get; set; }
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
                builder.Append(string.Format("Key: {0}, Value:{1}", parameter.Key,
                    valueDict != null ? valueDict["value"] : "Empty"
                    )).AppendLine();
            }
            return builder.ToString();
        }

        public object Clone()
        {
            //var newObject = (BehaviorInfo)this.MemberwiseClone();
            var newObject = new BehaviorInfo
            {
                ModuleName = ModuleName,
                Ip = Ip,
                Port = Port,
                BehaviorName = BehaviorName,
                FunctionName = FunctionName,
                Parameters = new Dictionary<string, object>(),
                ExecutionEvalExpression = ExecutionEvalExpression
            };
            foreach (var parameter in Parameters)
            {
                var value = parameter.Value as Dictionary<string, object>;
                var parameterDict = new Dictionary<string, object>();
                if (value != null)
                {
                    foreach (var o in value)
                    {
                        parameterDict.Add(o.Key, o.Value.ToString());
                    }
                }
                newObject.Parameters.Add(parameter.Key, parameterDict);
            }
            return newObject;
            //return DeepCopyHelper.DeepCopy(this);
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
        once,
        forever,
        until
    }

    public enum BehaviorType
    {
        Startup,
        Behavior,
        Exit
    }

    [Serializable()]
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
        public IList<BehaviorInfo> RobotActions { get; set; }
        public IList<BehaviorInfo> ExitActions { get; set; }

        public bool InitActionsComplete
        {
            get { return _initActionsComplete; }
            set { _initActionsComplete = value; }
        }

        public bool CyclicActionsComplete
        {
            get { return _cyclicActionsComplete; }
            set { _cyclicActionsComplete = value; }
        }

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
            var newObject = (MotionBasedBehavior) MemberwiseClone();
            return newObject;
        }
    }

    public class TriggerBasedBehavior : MotionBasedBehavior
    {
        public string InitBlock { get; set; }
        public string CyclicBlock { get; set; }
        public string ExitBlock { get; set; }
    }

    public enum BehaviorTriggerType
    {
        Gesture,
        Voice,
        Tactile,
        Olfactory,
        Other
    }

    public class BehaviorTrigger
    {
        public BehaviorTriggerType Trigger { get; set; }
    }

    public class SpeechRecognitionModule
    {
        public string WaitForVoiceResponse(IEnumerable<string> choices)
        {
            if (choices != null)
            {
                //TODO Get voice response for speech recognition
                //culture.CompareInfo.IndexOf(paragraph, word, CompareOptions.IgnoreCase) 
                var dummy = string.Empty;
                if (choices.Contains(dummy))
                {
                    return dummy;
                }
            }
            return string.Empty;
        }
    }

    public class NaoBehaviorModule
    {
        private static bool _canExecute;

        public string Name = "NaoBehaviorModule";

        public NaoBehaviorModule(Dictionary<string, string> parameters)
        {
            var name = parameters.FirstOrDefault(s => s.Key == "NaoBehaviorModule");
            Name = !string.IsNullOrEmpty(name.Value) ? name.Value : "nao_behavior_manager";
        }

        public static NaoBehaviorModule Create(string contextServer, int port)
        {
            return new NaoBehaviorModule(null);
        }

        public static void Execute(string function, params object[] args)
        {
            _canExecute = false;
        }

        public static bool CanExecute()
        {
            return _canExecute;
        }

        public static bool GetModuleInfo()
        {
            return false;
        }
    }

    public class BehaviorModuleHelper
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof(BehaviorModuleHelper));

        public static void Execute(IBehaviorExecutionContext context, BehaviorInfo info)
        {
            if (context != null && info != null)
            {
                Log.InfoFormat("Behavior Execution : {0} - {1}", info.BehaviorName, info.FunctionName);

                context.UpdateBehaviorResponderInfo(info);
                context.SyncExecuteBehavior(info);
            }
        }

        public static object CreateBehaviorParameterOptions(object value, bool placeHolder,
            string type)
        {
            return new Dictionary<string, object>
            {
                {"value", value},
                {"place_holder", placeHolder},
                {"type", type}
            };
        }
    }

    public struct GestureInfo
    {
        public int HumanId;
        public string Name;
        public bool Active;
        public int Confidence;
    }

    public struct VoiceCommandInfo
    {
        public string Name;
        public bool Active;
        public int Confidence;
    }

    public interface ITriggerBehavior
    {
        string Name { get; }
        //CheckTriggerDelegate TriggerDelegate { get; }
    }

    public class TriggerResult
    {
        public bool Active { get; set; }
        public bool HumanInLoop { get; set; }
        public int HumanId { get; set; }
    }

    public delegate bool CheckTriggerDelegate(IBehaviorExecutionContext context, out TriggerResult result);
    public delegate bool CheckLifetimeDelegate(IBehaviorExecutionContext context);
}