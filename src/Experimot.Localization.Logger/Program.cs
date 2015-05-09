using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
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
                Console.WriteLine("Retrieving the parameter from server failed");
            }
            if (info != null)
            {
                Console.WriteLine("Press Enter to start collecting information!");
                Console.Read();
                Task<IList<experimot.msgs.Pose>> logTask = Task.Factory.StartNew(() => LogLocalizationInfo(info));
                Console.WriteLine("Press enter to stop logging !");
                Console.Read();
                _stopTask = true;
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
                logTask.Wait();
            }
            else
            {
            }
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
                    while (!_stopTask)
                    {
                        using (var context = NetMQ.NetMQContext.Create())
                        {
                            using (var socket = context.CreateSubscriberSocket())
                            {
                                var addr = string.Format("{0}:{1}", subscriber.host, subscriber.port);
                                socket.Connect(addr);

                                byte[] msg = socket.Receive();
                                if (msg != null && msg.Length > 0)
                                {
                                    using (var memStream = new MemoryStream(msg))
                                    {
                                        var pose = Serializer.Deserialize<Pose>(memStream);
                                        poseList.Add(pose);
                                    }
                                }
                            }
                        }
                        System.Threading.Thread.Sleep(50);
                    }
                }
            }
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
