using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using CommandLine;
using CsvHelper;
using experimot.msgs;
using NetMQ;
using ProtoBuf;

namespace Experimot.Localization.Logger
{
    internal class CommandLineOptions
    {
        [Option('n', "name", DefaultValue = "localization_logger", HelpText = "This is the name of the node!")]
        public string Name { get; set; }

        [Option('p', "param", DefaultValue = "tcp://localhost:5560",
            HelpText = "This is the address of parameter server!")]
        public string ParameterServer { get; set; }
    }

    internal class Program
    {
        private static volatile bool _stopTask = false;

        private static void Main(string[] args)
        {
            Node info = null;
            try
            {
                if (args.Length > 0)
                {
                    var options = new CommandLineOptions();
                    Parser.Default.ParseArguments(args, options);
                    info = GetNodeInfo(options.Name, options.ParameterServer);

                    if (info != null)
                    {
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Retrieving the parameter from server failed : {0}",ex.StackTrace);
            }
            try
            {
                if (info != null)
                {
                    Console.WriteLine("Press Enter to start collecting information!");
                    string c = Console.ReadLine();
                    Task<IList<Pose>> logTask = Task.Factory.StartNew(() => LogLocalizationInfo(info));
                    Console.WriteLine("Enter stop to stop logging !");
                    string dummy = Console.ReadLine();
                    //Console.WriteLine("Received stop !");
                    //if (dummy == "stop")
                    //{
                        _stopTask = true;
                        
                    //}
                    logTask.Wait();
                    Console.WriteLine("Enter the file name to which the data has to be saved");
                    string fileName = Console.ReadLine();
                    if (!string.IsNullOrEmpty(fileName))
                    {
                        using (var writer = File.CreateText(fileName))
                        {
                            using (var csv = new CsvWriter(writer))
                            {
                                csv.WriteRecords(logTask.Result);
                            }

                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception : {0}", ex.StackTrace);
            }
            Console.WriteLine("About to exit. Press enter to close the console window.");
            Console.Read();
        }

        private static IList<Pose> LogLocalizationInfo(object info)
        {
            IList<Pose> poseList = new List<Pose>();
            Node nodeInfo = info as Node;
            if (nodeInfo != null)
            {
                Subscribe subscriber = nodeInfo.subscriber.FirstOrDefault(subscribe => subscribe.msg_type == "Pose");
                if (subscriber != null)
                {
                    Console.WriteLine("Creating context");
                    using (var context = NetMQContext.Create())
                    {
                        Console.WriteLine("Creating socket");
                        using (var socket = context.CreateSubscriberSocket())
                        {
                            var addr = string.Format("{0}:{1}", subscriber.host, subscriber.port);
                            Console.WriteLine("Connecting to {0}", addr);
                            socket.Connect(addr);
                            Console.WriteLine("Subscribing to {0}", subscriber.topic);
                            socket.Subscribe(subscriber.topic);
                            uint id = 1;
                            while (!_stopTask)
                            {
                                var topic = socket.ReceiveString(new TimeSpan(0, 0, 0, 0, 100));
                                if (topic != null)
                                {

                                    byte[] msg = socket.Receive();
                                    if (msg != null)
                                    {
                                        using (var memStream = new MemoryStream(msg))
                                        {
                                            var pose = Serializer.Deserialize<Pose>(memStream);
                                            pose.id = id++;
                                            pose.name = DateTime.Now.Ticks.ToString();
                                            Console.Write(".");
                                            poseList.Add(pose);
                                        }
                                    }
                                }
                            }
                        }
                        System.Threading.Thread.Sleep(50);
                    }
                }
                else
                {
                    Console.WriteLine("No valid publisher of Pose");
                }
            }
            else
            {
                Console.WriteLine("Node info empty");
            }
            Console.WriteLine("Completing the logging task");
            return poseList;
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

                        var msg = socket.ReceiveMessage(new TimeSpan(0, 0, 0, 0, timeout));
                        if (msg != null)
                        {
                            if (msg.FrameCount > 0)
                            {
                                //    var nodeInfo = Serializer.Deserialize<Node>(msg.First.Buffer);
                                //    MessageBox.Show(string.Format("Received node info!"));
                                //    return nodeInfo;
                                //}

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
    }
}
