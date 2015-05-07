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