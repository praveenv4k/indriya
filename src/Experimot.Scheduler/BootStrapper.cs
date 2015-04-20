using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Common.Logging;
using Experimot.Core;
using Experimot.Core.Util;
using Experimot.Scheduler.Tasks;
using Experimot.Scheduler.Web;

namespace Experimot.Scheduler
{
    internal class BootStrapper
    {
        private readonly experimot_config _config;
        private bool _startup;
        private bool _shutdown;
        private static readonly ILog Log = LogManager.GetLogger(typeof (BootStrapper));
        private readonly IList<Process> _processes;
        private readonly ParameterServer _parameterServer;
        private readonly ContextSync _contextSync;
        private readonly IList<Task> _tasks;
        private volatile bool _shouldStop;
        private ExperimotServer _server;

        public BootStrapper(experimot_config config, Context context)
        {
            _config = config;
            _processes = new List<Process>();
            _contextSync = new ContextSync(config, context);
            _parameterServer = new ParameterServer(_config);
            _server = new ExperimotServer(_config);

            _tasks = new List<Task>
            {
                Task.Factory.StartNew(() => RunParameterServer(_parameterServer)),
                Task.Factory.StartNew(() => RunContextSync(_contextSync)),
                Task.Factory.StartNew(() => RunExperimotServer(_server))
            };
        }

        private void RunParameterServer(object arg)
        {
            var server = arg as ParameterServer;
            if (server != null)
            {
                _parameterServer.Start();
                Log.Info("Parameter server Started");
                while (!_shouldStop)
                {
                    server.Run();
                    Thread.Sleep(40);
                }
                server.Shutdown();
            }
            Log.Info("Parameter server Completed");
        }

        private void RunExperimotServer(object arg)
        {
            var server = arg as ExperimotServer;
            if (server != null)
            {
                _server.Start();
                Log.Info("Experimot server Started");
            }
            Log.Info("Experimot server Completed");
        }

        private void RunContextSync(object arg)
        {
            var sync = arg as ContextSync;
            if (sync != null)
            {
                Log.Info("Context sync Started");
                while (!_shouldStop)
                {
                    sync.Update(100);
                    Thread.Sleep(200);
                }
            }
            Log.Info("Context sync Completed");
        }

        public void StartUp()
        {
            if (!_startup && _config != null)
            {
                foreach (var node in _config.nodes)
                {
                    if (node != null && node.enabled && node.process != null)
                    {
                        var exeFile = Environment.ExpandEnvironmentVariables(node.process.path);
                        if (!string.IsNullOrEmpty(exeFile))
                        {
                            try
                            {
                                string paramServer = ParameterUtil.Get(_config.parameters, "ParameterClientHost",
                                    "tcp://*");
                                int port = ParameterUtil.Get(_config.parameters, "ParameterServerPort",
                                    5560);

                                var args = string.Format("{3} --name={0} --param={1}:{2}", node.name, paramServer, port,
                                    Environment.ExpandEnvironmentVariables(node.process.args));

                                var workingDir = Path.GetDirectoryName(exeFile);
                                var myProcess = new Process
                                {
                                    StartInfo =
                                    {
                                        UseShellExecute = true,
                                        FileName = exeFile,
                                        CreateNoWindow = true,
                                        Arguments = args,
                                        WorkingDirectory = workingDir ?? string.Empty
                                    }
                                };
                                myProcess.Start();
                                Log.InfoFormat("Started Process : {0} {1}", exeFile, args);
                                _processes.Add(myProcess);
                                myProcess.Exited += myProcess_Exited;
                                Thread.Sleep(200);
                                //break;
                            }
                            catch (Exception ex)
                            {
                                Log.ErrorFormat("Process: {0}, Message: {1}", exeFile, ex.Message);
                            }

                        }
                    }
                }
                _startup = true;
            }
        }

        private void myProcess_Exited(object sender, EventArgs e)
        {
            var process = sender as Process;
            if (process != null)
            {
                Log.InfoFormat("Process exited: {0}", process.Id);
            }
        }

        public void Shutdown()
        {
            if (!_shutdown)
            {
                _shouldStop = true;
                foreach (var process in _processes)
                {
                    if (!process.HasExited)
                    {
                        //process.CloseMainWindow();
                        //process.Close();
                        process.Kill();
                    }
                }
                if (_server != null)
                {
                    _server.Stop();
                    _server = null;
                }
                Task.WaitAll(_tasks.ToArray(), new TimeSpan(0, 0, 0, 1));
                _shutdown = true;
            }
        }

        public experimot_config Config
        {
            get { return _config; }
        }
    }
}
