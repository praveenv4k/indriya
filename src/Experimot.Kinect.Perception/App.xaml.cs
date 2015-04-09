using System;
using System.IO;
using System.Text;
using System.Windows;
using CommandLine;
using Common.Logging;
using experimot.msgs;
using ProtoBuf;
using NetMQ;
using NetMQ.zmq;
using Exception = System.Exception;

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
                var options = new CommandLineOptions();
                Parser.Default.ParseArguments(args, options);
                info = GetNodeInfo(options.Name, options.ParameterServer);
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
                        //socket.ReceiveTimeout = new TimeSpan(0, 0, 0, 0, timeout);
                        //socket.Send(new ZFrame(name));
                        socket.Send(name);
                        //socket.Receive
                        //using (var msg = socket.ReceiveFrame())
                        //{
                        //    var nodeInfo = Serializer.Deserialize<Node>(msg);
                        //    MessageBox.Show(string.Format("Received node info!"));
                        //    return nodeInfo;
                        //}
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
                            //MessageBox.Show(string.Format("Message buffer empty!"));
                            //Console.WriteLine("Message buffer empty!");
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

    }
}
