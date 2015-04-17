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

namespace Experimot.Scheduler
{
    internal class BootStrapper
    {
        private readonly experimot_config _config;
        private bool _startup;
        private bool _shutdown;
        private ILog Log = LogManager.GetLogger(typeof (BootStrapper));
        private const string PYTHONPATH = @"C:\Python27";
        private readonly IList<Process> _processes;
        private readonly ParameterServer _parameterServer;
        private ContextSync _contextSync;
        private IList<Task> _tasks;
        private volatile bool _shouldStop;
        private IList<Thread> _threads;

        public BootStrapper(experimot_config config, Context context)
        {
            _config = config;
            _processes = new List<Process>();
            _contextSync = new ContextSync(config, context);
            _parameterServer = new ParameterServer(_config);
            _parameterServer.Start();

            _tasks = new List<Task>
            {
                Task.Factory.StartNew(() => RunServer(_parameterServer)),
                Task.Factory.StartNew(() => RunContextSync(_contextSync))
            };

            _threads = new List<Thread>();
            //_threads.Add(new Thread(RunServer));
            //_threads.Add(new Thread(RunContextSync));

            //_threads[0].Start(_parameterServer);
            //_threads[1].Start(_contextSync);
        }

        private void RunServer(object arg)
        {
            var server = arg as ParameterServer;
            if (server != null)
            {
                Console.WriteLine("Parameter server Started");
                while (!_shouldStop)
                {
                    server.Run();
                    Thread.Sleep(40);
                }
                server.Shutdown();
            }
            Console.WriteLine("Parameter server Completed");
        }

        private void RunContextSync(object arg)
        {
            var sync = arg as ContextSync;
            if (sync != null)
            {
                Console.WriteLine("Context sync Started");
                while (!_shouldStop)
                {
                    sync.Update(100);
                    Thread.Sleep(200);
                }
            }
            Console.WriteLine("Context sync Completed");
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
                                string args = string.Empty;

                                string paramServer = ParameterUtil.Get(_config.parameters, "ParameterClientHost",
                                    "tcp://*");
                                int port = ParameterUtil.Get(_config.parameters, "ParameterServerPort",
                                    5560);

                                args = string.Format("{3} --name={0} --param={1}:{2}", node.name, paramServer, port,
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
                Console.WriteLine("Process exited: {0}", process.Id);
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
                foreach (var thread in _threads)
                {
                    thread.Join(1000);
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
