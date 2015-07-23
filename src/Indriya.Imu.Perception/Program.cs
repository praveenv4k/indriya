using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CommandLine;
using Common.Logging;
using Experimot.Core.Util;
using Indriya.Core.Msgs;
using NetMQ;
using Newtonsoft.Json.Linq;
using ProtoBuf;

namespace Experimot.Imu.Perception
{
    class Program
    {
        private static readonly ILog Log = LogManager.GetLogger<Program>();
        private  static GestureTrigger _imuTrigger = new GestureTrigger();
        private static DateTime _lastUpdate = new DateTime();
        internal class CommandLineOptions
        {
            [Option('n', "name", DefaultValue = "localization_logger", HelpText = "This is the name of the node!")]
            public string Name { get; set; }

            [Option('p', "param", DefaultValue = "tcp://localhost:5560",
                HelpText = "This is the address of parameter server!")]
            public string ParameterServer { get; set; }
        }

        private static volatile bool _stopTask;
        private static readonly object _object = new object();

        private static void Main(string[] args)
        {
            _imuTrigger.motion = new GestureDescription();
            _imuTrigger.motion.name = "IMU_WAVE";
            _stopTask = false;
            Node info = null;
            var options = new CommandLineOptions();
            try
            {
                if (args.Length > 0)
                {
                    Parser.Default.ParseArguments(args, options);
                    info = GetNodeInfo(options.Name, options.ParameterServer);

                    if (info != null)
                    {
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Retrieving the parameter from server failed : {0}", ex.StackTrace);
            }
            try
            {
                if (info != null)
                {
                    SendMotionRecognitionModuleInfo(info, options.ParameterServer);
                    var tasks = new List<Task>();
                    tasks.Add(Task.Run(() => CollectData(info)));
                    tasks.Add(Task.Run(() => PublishData(info)));
                    Task.WaitAll(tasks.ToArray());
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception : {0}", ex.StackTrace);
            }
            Console.WriteLine("About to exit. Press enter to close the console window.");
            Console.Read();
        }

        private static void CollectData(object nodeInfo)
        {
            try
            {
                var info = nodeInfo as Node;
                if (info != null)
                {
                    if (info.subscriber != null && info.subscriber.Count > 0)
                    {
                        var subscriber = info.subscriber.FirstOrDefault(s => s.topic == "motionarm1");
                        {
                            if (subscriber != null)
                            {
                                using (var ctx = NetMQContext.Create())
                                using (var socket = ctx.CreateSubscriberSocket())
                                {
                                    string addr = string.Format("{0}:{1}", subscriber.host, subscriber.port);
                                    socket.Connect(addr);
                                    socket.Subscribe(subscriber.topic);
                                    while (!_stopTask)
                                    {
                                        var topic = socket.ReceiveString(new TimeSpan(0, 0, 0, 0, 100));
                                        if (topic != null)
                                        {
                                            string str = socket.ReceiveString();
                                            Console.WriteLine(str);
                                            var jObj = JObject.Parse(str);
                                            if (jObj != null)
                                            {
                                                var token = jObj.SelectToken("motion");
                                                if (token != null && token.HasValues)
                                                {
                                                    lock (_object)
                                                    {
                                                        _imuTrigger.motion.name = token.Value<string>("name");
                                                        _imuTrigger.motion.active = true;
                                                        _imuTrigger.motion.confidence = token.Value<int>("confidence");
                                                        _lastUpdate = DateTime.Now;
                                                    }
                                                }

                                            }
                                        }
                                        else
                                        {
                                            var span = DateTime.Now - _lastUpdate;
                                            if (span > new TimeSpan(0, 0, 0, 0,1500))
                                            {
                                                lock (_object)
                                                {
                                                    _imuTrigger.motion.active = false;
                                                    _imuTrigger.motion.confidence = 0;
                                                    _lastUpdate = DateTime.Now;
                                                }
                                            }
                                        }
                                        //Console.WriteLine("Collecting ...");
                                        System.Threading.Thread.Sleep(100);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Log.InfoFormat(ex.Message);
            }
        }

        private static void PublishData(object nodeInfo)
        {
            try
            {
                Console.WriteLine("Publish data start");
                var info = nodeInfo as Node;
                if (info != null)
                {
                    Console.WriteLine("Publish info ok");
                    if (info.publisher != null && info.publisher.Count > 0)
                    {
                        Console.WriteLine("Publish publisher ok");
                        var publisher = info.publisher.FirstOrDefault(s => s.msg_type == "GestureTrigger");
                        {
                            if (publisher != null)
                            {
                                Console.WriteLine("PublishData Create ...");
                                using (var ctx = NetMQContext.Create())
                                using (var socket = ctx.CreatePublisherSocket())
                                {
                                    string addr = string.Format("{0}:{1}", publisher.host, publisher.port);
                                    socket.Bind(addr);

                                    while (!_stopTask)
                                    {
                                        Console.WriteLine("Publishing start ...");
                                        lock (_object)
                                        {
                                            socket.SendMore(publisher.topic);
                                            using (var ms = new MemoryStream())
                                            {
                                                //_imuTrigger.motion.confidence = 50;
                                                Serializer.Serialize(ms, _imuTrigger);
                                                socket.Send(ms.GetBuffer(), (int) ms.Length);
                                            }
                                        }
                                        Console.WriteLine("Publishing ...");
                                        System.Threading.Thread.Sleep(100);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            catch
                (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Log.InfoFormat(ex.Message);
            }
        }

        private static Node GetNodeInfo(string name, string server, int timeout = 1000)
        {
            try
            {
                using (var context = NetMQContext.Create())
                {
                    using (var socket = context.CreateRequestSocket())
                    {
                        socket.Connect(server);
                        socket.Send(name);

                        var msg = socket.ReceiveMessage();
                        if (msg != null)
                        {
                            if (msg.FrameCount > 0)
                            {
                                using (var memStream = new MemoryStream(msg.First.Buffer))
                                {
                                    var nodeInfo = Serializer.Deserialize<Node>(memStream);
                                    return nodeInfo;
                                }
                            }
                        }
                        else
                        {
                            Console.WriteLine("Message buffer empty!");
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("{1} : {0}", ex.StackTrace, ex.Message);
            }
            return null;
        }

        private static void SendMotionRecognitionModuleInfo(Node node, string server, int timeout = 1000)
        {
            try
            {
                if (node == null)
                {
                    return;
                }

                var module = new GestureRecognitionModule { name = node.name };
                var desc = new GestureDescription
                {
                    name = "IMU_WAVE",
                    type = GestureDescription.GestureType.Discrete
                };

                module.motions.Add(desc);

               

                using (var context = NetMQContext.Create())
                {
                    using (var socket = context.CreateRequestSocket())
                    {
                        socket.Connect(server);
                        socket.SendMore("register_motions");
                        socket.SendMore(node.name);
                        using (var ms = new MemoryStream())
                        {
                            Serializer.Serialize(ms, module);
                            socket.Send(ms.GetBuffer(), (int)ms.Length);
                        }

                        var msg = socket.ReceiveString(new TimeSpan(0, 0, 0, 0, timeout));
                        if (msg != null)
                        {
                            Log.InfoFormat("Motion registration response: {0}", msg);
                        }
                        else
                        {
                            Log.Info("Message buffer empty!");
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Log.InfoFormat("{1} : {0}", ex.StackTrace, ex.Message);
            }
        }
    }
}
