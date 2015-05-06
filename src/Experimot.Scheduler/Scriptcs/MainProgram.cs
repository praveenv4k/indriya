using System;
using System.Collections.Generic;
using NetMQ;
using Newtonsoft.Json.Linq;

public class MainProgram
{
    private static volatile bool _requestStop;
    private readonly IDictionary<string, object> _props;
    private const int RecvTimeout = 200;
    private const int Period = 200;

    public MainProgram(IDictionary<string, object> props)
    {
        _props = props;
        _requestStop = false;
    }

    private static object GetValue(IDictionary<string, object> props, string key, object defaultValue)
    {
        var ret = defaultValue;
        if (props != null)
        {
            if (props.ContainsKey(key))
            {
                ret = props[key];
            }
        }
        return ret;
    }

    private static Dictionary<string, string> CheckGestureTrigger(NetMQSocket socket, JArray humanArray,
        Dictionary<string, string> gestBehaviorMap)
    {
        Dictionary<string, string> ret = new Dictionary<string, string>();
        if (humanArray != null && socket != null && humanArray.Count > 0)
        {
            foreach (var human in humanArray)
            {
                var gestures = human.SelectToken("$.Gestures");
                foreach (var gesture in gestures)
                {
                    string name = gesture.Value<string>("Name");
                    if (gestBehaviorMap.ContainsKey(name))
                    {
                        bool active = gesture.Value<bool>("Active");
                        int confidence = gesture.Value<int>("Confidence");
                        if (active && confidence > 95)
                        {
                            ret.Add(name, gestBehaviorMap[name]);
                            Console.WriteLine(@"Name : {0}, Confidence: {1}", name, confidence);
                        }
                    }

                }
            }
        }
        return ret;
    }

    public void Run()
    {
        Console.WriteLine(@"About to start running main program");
        try
        {
            if (_props != null && _props.Count > 0)
            {
                var contextServer = GetValue(_props, "ContextServer", "tcp://localhost:5800").ToString();
                if (!string.IsNullOrEmpty(contextServer))
                {
                    var triggerBehaviorMap = GetValue(_props, "TriggerBehaviorMap", new Dictionary<string, string>());
                    var dict = triggerBehaviorMap as Dictionary<string, string>;
                    if (dict != null && dict.Count > 0)
                    {
                        foreach (var item in dict)
                        {
                            Console.WriteLine(@"Gesture: {0} -> Behavior : {1}", item.Key,
                                item.Value);
                        }

                        using (var ctx = NetMQContext.Create())
                        {
                            using (var socket = ctx.CreateRequestSocket())
                            {
                                socket.Connect(contextServer);
                                while (!_requestStop)
                                {
                                    socket.Send("human");
                                    var resp = socket.ReceiveString(new TimeSpan(0, 0, 0, 0, RecvTimeout));
                                    if (!string.IsNullOrEmpty(resp))
                                    {
                                        try
                                        {
                                            JArray obj = JArray.Parse(resp);
                                            //Console.WriteLine(resp);
                                            var behaviorMap = CheckGestureTrigger(socket, obj, dict);
                                            if (behaviorMap.Count == 0)
                                            {
                                                //Console.WriteLine(@"No gesture detected!");
                                            }
                                            foreach (var behavior in behaviorMap)
                                            {
                                                Console.WriteLine(@"Gesture: {0} -> Behavior : {1}", behavior.Key,
                                                    behavior.Value);
                                            }
                                        }
                                        catch (Exception ex)
                                        {
                                            Console.WriteLine(ex.Message);
                                        }
                                    }
                                    System.Threading.Thread.Sleep(Period);
                                }
                            }
                        }
                    }
                }
                else
                {
                    Console.WriteLine(@"Configuration information not available! Program will end now!");
                }
            }
            else
            {
                Console.WriteLine(@"Configuration information missing!");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine(@"Main Program Run exception: {0}", ex.StackTrace);
        }
        Console.WriteLine(@"About to complete main program");
    }
}