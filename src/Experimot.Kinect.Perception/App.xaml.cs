using System.IO;
using System.Text;
using System.Windows;
using CommandLine;
using Common.Logging;
using experimot.msgs;
using ProtoBuf;
using ZMQ;
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
                //MainWindow = new MainWindow(info);
                MainWindow = new MainWindow();
            }
            MainWindow.Show();
        }

        private Node GetNodeInfo(string name, string server, int timeout = 1000)
        {
            try
            {
                using (var context = new Context(1))
                {
                    using (var socket = context.Socket(SocketType.REQ))
                    {
                        socket.Connect(server);
                        if (socket.Send(name, Encoding.ASCII) == SendStatus.Sent)
                        {
                            byte[] msg = socket.Recv(timeout);
                            if (msg != null)
                            {
                                using (var memStream = new MemoryStream(msg))
                                {
                                    var nodeInfo = Serializer.Deserialize<Node>(memStream);
                                    return nodeInfo;
                                }
                            }
                            else
                            {
                                MessageBox.Show(string.Format("Message buffer empty!"));
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            return null;
        }

    }
}
