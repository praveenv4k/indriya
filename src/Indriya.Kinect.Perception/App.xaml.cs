using System;
using System.IO;
using System.Windows;
using CommandLine;
using Common.Logging;
using Indriya.Core.Msgs;
using Indriya.Core.Util;
using Microsoft.Kinect.VisualGestureBuilder;
using NetMQ;
using ProtoBuf;

namespace Indriya.Kinect.Perception
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private static readonly ILog Log = LogManager.GetLogger<App>();
        public static CommandLineOptions Options;
        public static Node NodeInfo;
        public App()
        {
            Startup += AppStartup;
        }

        private void AppStartup(object sender, StartupEventArgs e)
        {
            NodeInfo = null;
            try
            {
                var args = e.Args;
                //if (args.Length > 0)
                {
                    Options = new CommandLineOptions();
                    Parser.Default.ParseArguments(args, Options);
                    NodeInfo = MessageUtil.RequestProtoMessage<Node>(Options.ParameterServer, Options.Name);

                    if (NodeInfo != null)
                    {
                        SendMotionRecognitionModuleInfo(NodeInfo, Options.ParameterServer);
                    }
                }
            }
            catch (Exception ex)
            {
                Log.Info("Retrieving the parameter from server failed");
            }
            if (NodeInfo == null)
            {
                MessageBox.Show("Info null");
                MainWindow = new MainWindow();
            }
            else
            {
                MainWindow = new MainWindow(NodeInfo);
            }
            MainWindow.Show();
        }

        public static string GetFileString(string fileName, string server, int timeout = 1000)
        {
            try
            {
                using (var context = NetMQContext.Create())
                {
                    using (var socket = context.CreateRequestSocket())
                    {
                        socket.Connect(server);
                        socket.SendMore("file_request");
                        socket.Send(fileName);
                        var msg = socket.ReceiveString(new TimeSpan(0, 0, 0, 0, timeout));
                        if (msg != null)
                        {
                            Log.InfoFormat("File request response: {0}", msg);
                            return msg;
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
            return string.Empty;
        }

        private static void SendMotionRecognitionModuleInfo(Node node, string server, int timeout = 1000)
        {
            try
            {
                if (node == null)
                {
                    return;
                }

                const string defaultValue = @"Database\experimot.gbd";
                var dbList = ParameterUtil.GetCsvList(node.param, "database", defaultValue);
                if (dbList.Count == 0)
                {
                    dbList.Add(defaultValue);
                }
                var module = new GestureRecognitionModule {name = node.name};
                foreach (var db in dbList)
                {
                    using (var database = new VisualGestureBuilderDatabase(db))
                    {
                        foreach (var gesture in database.AvailableGestures)
                        {
                            var desc = new GestureDescription
                            {
                                name = gesture.Name,
                                type = (GestureDescription.GestureType) gesture.GestureType
                            };

                            module.motions.Add(desc);
                        }
                    }
                }

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
                        
                        //var msg = socket.ReceiveString(new TimeSpan(0, 0, 0, 0, timeout));
                        var msg = socket.ReceiveString();
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
