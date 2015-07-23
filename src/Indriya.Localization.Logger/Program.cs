using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using CommandLine;
using CsvHelper;
using Experimot.Core.Util;
using Indriya.Core.Msgs;
using NetMQ;
using Newtonsoft.Json.Linq;
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

    internal class PlanarPose
    {
        public long TimeStamp { get; set; }
        public double X { get; set; }
        public double Y { get; set; }
        public double Theta { get; set; }
    }

    internal class PlanarPoseExt
    {
        public long TimeStamp { get; set; }
        public double X { get; set; }
        public double Y { get; set; }
        public double Theta { get; set; }
        public double TransError { get; set; }
        public double RotError { get; set; }
        public double Rx { get; set; }
        public double Ry { get; set; }
        public double Rz { get; set; }
    }

    internal class Program
    {
        private static volatile bool _stopTask;

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
                Console.WriteLine("Retrieving the parameter from server failed : {0}", ex.StackTrace);
            }
            try
            {
                if (info != null)
                {
                    //Task writeSkeleton = Task.Factory.StartNew(() => LogKinectSkeleton(info));
                    Console.WriteLine("Enter 0 for 6D pose and 1 for pose on a plane!");
                    //string c = Console.ReadLine();
                    string c = ParameterUtil.Get(info.param, "Localize6D", "0");
                    Task<IList<Pose>> logTask = null;
                    Task<IList<Pose>> humanTask = null;
                    Task<IList<PlanarPoseExt>> logPlanarTask = null;
                    if (c == "0")
                    {
                        logTask = Task.Factory.StartNew(() => LogLocalizationInfo(info));
                        //humanTask = Task.Factory.StartNew(() => LogTorsoInfo(info));
                    }
                    else
                    {
                        logPlanarTask = Task.Factory.StartNew(() => LogPlanarLocalizationInfo(info));
                    }
                    Console.WriteLine("Enter stop to stop logging !");

                    string dummy = Console.ReadLine();
                    Console.WriteLine("Received stop !");
                    if (dummy == "stop")
                    {
                        _stopTask = true;

                    }
                    if (logTask != null) logTask.Wait();
                    if (humanTask != null) humanTask.Wait();
                    if (logPlanarTask != null) logPlanarTask.Wait(new TimeSpan(0, 0, 5));
                    Console.WriteLine("Enter the file name to which the data has to be saved");
                    string fileName = Console.ReadLine();
                    if (!string.IsNullOrEmpty(fileName))
                    {
                        using (var writer = File.CreateText(fileName))
                        {
                            using (var csv = new CsvWriter(writer))
                            {
                                if (logTask != null)
                                {
                                    csv.WriteRecords(logTask.Result);
                                }
                                if (logPlanarTask != null)
                                {
                                    csv.WriteRecords(logPlanarTask.Result);
                                }
                            }

                        }
                        if (humanTask != null)
                        {
                            using (var writer = File.CreateText(fileName + "human"))
                            {
                                using (var csv = new CsvWriter(writer))
                                {
                                    csv.WriteRecords(humanTask.Result);
                                }
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
            List<Pose> poseList = new List<Pose>();
            Node nodeInfo = info as Node;
            if (nodeInfo != null)
            {
                Subscribe subscriber = nodeInfo.subscriber.FirstOrDefault(subscribe => subscribe.msg_type == "Pose_V");
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
                                            var poses = Serializer.Deserialize<Pose_V>(memStream);
                                            if (poses != null)
                                            {
                                                poseList.AddRange(poses.pose);
                                                Console.Write(".");
                                                //var pose = poses.pose.FirstOrDefault(s => s.name == "torso_frame_world");
                                                //if (pose != null)
                                                //{
                                                //    pose.id = id++;
                                                //    pose.name = DateTime.Now.Ticks.ToString();
                                                //    Console.Write(".");
                                                //    poseList.Add(pose);
                                                //}
                                            }
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

        private static IList<Pose> LogTorsoInfo(object info)
        {
            List<Pose> poseList = new List<Pose>();
            Node nodeInfo = info as Node;
            if (nodeInfo != null)
            {
                Subscribe subscriber = nodeInfo.subscriber.FirstOrDefault(subscribe => subscribe.msg_type == "Humans");
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
                                            var humans = Serializer.Deserialize<Humans>(memStream);
                                            foreach (var human in humans.human)
                                            {
                                                var pose = new Pose()
                                                {
                                                    id = (uint) human.id,
                                                    position = human.torso_position,
                                                    orientation = human.orientation
                                                };
                                                poseList.Add(pose);
                                            }
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

        private static IList<PlanarPoseExt> LogPlanarLocalizationInfo(object info)
        {
            IList<PlanarPoseExt> poseList = new List<PlanarPoseExt>();
            Node nodeInfo = info as Node;
            if (nodeInfo != null)
            {
                var port = ParameterUtil.Get(nodeInfo.param, "tdm_server_port", 0);
                if (port != 0)
                {
                    using (var context = NetMQContext.Create())
                    {
                        Console.WriteLine("Creating socket");
                        using (var socket = context.CreateRequestSocket())
                        {
                            var addr = string.Format("tcp://localhost:{0}", port);
                            Console.WriteLine("Connecting to {0}", addr);
                            socket.Connect(addr);
                            //uint id = 1;
                            while (!_stopTask)
                            {
                                socket.Send("pose");
                                var pose = socket.ReceiveString();
                                var jObj = JObject.Parse(pose);
                                var jPos = jObj.SelectToken("$.pos");
                                var jOrient = jObj.SelectToken("$.orient");
                                var jError = jObj.SelectToken("$.error");
                                var jEuler = jObj.SelectToken("$.euler");
                                var planarPose = new PlanarPoseExt()
                                {
                                    TimeStamp = DateTime.Now.Ticks,
                                    X = jPos.Value<double>("x"),
                                    Y = jPos.Value<double>("y"),
                                    Theta = jOrient.Value<double>("z")
                                };
                                if (jError != null) 
                                {

                                    planarPose.TransError = jError.Value<double>("trans");
                                    planarPose.RotError = jError.Value<double>("rot");
                                }
                                if (jEuler != null)
                                {
                                    planarPose.Rx = jEuler.Value<double>("Rx");
                                    planarPose.Ry = jEuler.Value<double>("Ry");
                                    planarPose.Rz = jEuler.Value<double>("Rz");
                                }

                                poseList.Add(planarPose);
                                //Console.WriteLine("x: {0}, y: {1}, theta: {2}, pose:{3}", planarPose.X, planarPose.Y,
                                //    planarPose.Theta, pose);
                                Console.Write(".");
                                
                                //System.Threading.Thread.Sleep(50);
                            }
                        }
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

        public static void LogKinectSkeleton(object info)
        {
            Console.Write("Sleep for 5 seconds");
            System.Threading.Thread.Sleep(5000);
            Console.Write("Start processing...");
            Node nodeInfo = info as Node;
            if (nodeInfo != null)
            {
                Subscribe subscriber =
                    nodeInfo.subscriber.FirstOrDefault(subscribe => subscribe.msg_type == "KinectBodies");
                if (subscriber != null)
                {
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
                                            var bodies = Serializer.Deserialize<KinectBodies>(memStream);
                                            using (var file = File.Create("skeleton.bin"))
                                            {
                                                Serializer.Serialize(file, bodies);
                                            }
                                            Console.Write("Written to file");
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
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
    }
}
