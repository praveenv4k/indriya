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

    private static Dictionary<string, string> CheckGestureTrigger(NetMQSocket socket, JObject obj,
        Dictionary<string, string> gestBehaviorMap)
    {
        Dictionary<string, string> ret = new Dictionary<string, string>();
        if (obj != null && socket != null && obj.Count > 0)
        {
            var humans = obj.SelectToken("$.Human");
            if (humans != null)
            {
                foreach (var human in humans)
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
                            }
                        }
                    }
                }
            }
        }
        //num = len(humans)
        //use_scheduler = False
        //for human in humans:
        //    for gesture in human["Gestures"]:
        //        active = bool(gesture["Active"])
        //        if active == True:
        //            confidence = int(gesture["Confidence"])
        //            if confidence > 95:
        //                print "Gesture %s is detected" % gesture["Name"]
        //                if sock!= None:
        //                    try:
        //                        sock.send(b"behavior_modules")
        //                        #  Get the reply.
        //                        str = sock.recv(1024)
        //                        #print str
        //                        modules = json.loads(str)
        //                        for module in modules:
        //                            for behavior in module["behaviors"]:
        //                                behavior_name = behavior["name"].encode("utf-8")
        //                                if behavior_name == "greet":
        //                                    global scheduler
        //                                    id = "nao_behavior"
        //                                    ret = check_job_exists(id,scheduler)
        //                                    if ret == False:
        //                                        responder = module["responder"]
        //                                        if use_scheduler == True:
        //                                            #job = scheduler.add_job(execute_behavior_task,args=(behavior_name,responder),id=id)
        //                                            job = scheduler.add_job(myfunc,id=id,next_run_time=datetime.datetime.now() + datetime.timedelta(seconds=1))
        //                                            print job
        //                                        else:
        //                                            execute_behavior_task(behavior_name,responder)
        //                                    else:
        //                                        print "Job already exists"

        //                        #print modules
        //                    except:
        //                        print "Exception occured while retrieving modules : ", sys.exc_info()
        return ret;
    }

    public void Run()
    {
        Console.WriteLine(@"About to start running main program");
        if (_props != null && _props.Count > 0)
        {
            var contextServer = GetValue(_props, "ContextServer", "tcp://localhost:5800").ToString();
            if (!string.IsNullOrEmpty(contextServer))
            {
                var triggerBehaviorMap = GetValue(_props, "TriggerBehaviorMap", new Dictionary<string, string>());
                var dict = triggerBehaviorMap as Dictionary<string, string>;
                if (dict != null && dict.Count > 0)
                {
                    using (var ctx = NetMQContext.Create())
                    {
                        using (var socket = ctx.CreateRequestSocket())
                        {
                            while (!_requestStop)
                            {
                                socket.Send("human");
                                var resp = socket.ReceiveString(new TimeSpan(0, 0, 0, 0, RecvTimeout));
                                if (!string.IsNullOrEmpty(resp))
                                {
                                    JObject obj = JObject.Parse(resp);
                                    var behaviorMap = CheckGestureTrigger(socket, obj, dict);
                                    foreach (var behavior in behaviorMap)
                                    {
                                        Console.WriteLine(@"Gesture: {0} -> Behavior : {1}", behavior.Key,
                                            behavior.Value);
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
        Console.WriteLine(@"About to complete main program");
    }
}