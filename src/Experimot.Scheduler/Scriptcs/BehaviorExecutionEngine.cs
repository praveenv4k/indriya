using System.Collections.Generic;

public class BehaviorExecutionEngine
{
    public static BehaviorExecutionContext Context { get; set; }
    public static Dictionary<string, object> Triggers = new Dictionary<string, object>();

    public static void RegisterTrigger(string name, object del)
    {
        if (!Triggers.ContainsKey(name))
        {
            Triggers.Add(name, del);
        }
        else
        {
            Triggers[name] = del;
        }
    }

    public static void Run()
    {

    }
}