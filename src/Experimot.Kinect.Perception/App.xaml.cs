using System.IO;
using System.Text;
using System.Windows;
using CommandLine;
using experimot.msgs;
using ProtoBuf;
using ZMQ;
using Exception = System.Exception;

namespace Experimot.Kinect.Perception
{
    class Options
    {
        [Option('n', "name", DefaultValue = "gesture_recognition", HelpText = "This is the name of the node!")]
        public string Name { get; set; }
        [Option('p', "param", DefaultValue = "tcp://localhost:5560", HelpText = "This is the address of parameter server!")]
        public string ParameterServer { get; set; }
    }
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            var args = e.Args;
            var options = new Options();
            Parser.Default.ParseArguments(args, options);
            var info = GetNodeInfo(options.Name, options.ParameterServer);
            if (info != null)
            {
            }
            base.OnStartup(e);
        }

        private Node GetNodeInfo(string name, string server, int timeout=1000)
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
