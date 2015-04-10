using System;
using System.IO;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using CommandLine;
using Common.Logging;
using experimot.msgs;
using ProtoBuf;
using NetMQ;
using NetMQ.zmq;
using Exception = System.Exception;
using Poller = NetMQ.Poller;

namespace Experimot.Kinect.Perception
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private readonly ILog Log = LogManager.GetLogger<App>();

        public App()
        {
            Startup += AppStartup;
        }

        private void AppStartup(object sender, StartupEventArgs e)
        {
            Node info = null;
            try
            {
                var args = e.Args;
                if (args.Length > 0)
                {
                    var options = new CommandLineOptions();
                    Parser.Default.ParseArguments(args, options);
                    info = GetNodeInfo(options.Name, options.ParameterServer);
                }
            }
            catch (Exception ex)
            {
                Log.Info("Retrieving the parameter from server failed");
            }
            if (info == null)
            {
                MainWindow = new MainWindow();
            }
            else
            {
                MainWindow = new MainWindow(info);
            }
            MainWindow.Show();
        }

        private Node GetNodeInfo(string name, string server, int timeout = 1000)
        {
            try
            {
                using (var context = NetMQ.NetMQContext.Create())
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
                MessageBox.Show(string.Format("{1} : {0}", ex.StackTrace, ex.Message));
                //MessageBox.Show(ex.StackTrace,"Parameter retrieve");
            }
            return null;
        }

        private Node GetNodeInfo2(string name, string server, int timeout = 1000)
        {
            Node nodeInfo = null;
            try
            {
                using (var context = NetMQ.NetMQContext.Create())
                {
                    using (var socket = context.CreateRequestSocket())
                    using (var poller = new Poller())
                    {
                        socket.Connect(server);

                        socket.ReceiveReady += (s, a) =>
                        {
                            var msg = a.Socket.ReceiveMessage();
                            if (msg != null)
                            {
                                if (msg.FrameCount > 0)
                                {
                                    using (var memStream = new MemoryStream(msg.First.Buffer))
                                    {
                                        nodeInfo = Serializer.Deserialize<Node>(memStream);
                                    }
                                }
                            }
                            if (poller != null)
                            {
                                poller.RemoveSocket(a.Socket);
                            }
                        };
                        //poller.PollTimeout = (int) timeout/1000;
                        poller.AddSocket(socket);
                        socket.Send(name);
                        Task task = Task.Factory.StartNew(poller.Start);
                        Thread.Sleep(timeout);
                        poller.RemoveSocket(socket);
                        poller.Stop();
                        task.Wait();
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(string.Format("{1} : {0}", ex.StackTrace, ex.Message));
                //MessageBox.Show(ex.StackTrace,"Parameter retrieve");
            }
            return nodeInfo;
        }

    }
}
