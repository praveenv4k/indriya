using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Threading;
using Common.Logging;
using IronPython.Hosting;
using Scheduler;

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

        public BootStrapper(experimot_config config)
        {
            _config = config;
            _processes = new List<Process>();

            _parameterServer = new ParameterServer(_config);
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

                                args = string.Format("--name={0} --param={1}:{2}", node.name, paramServer, port);

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
                                Log.InfoFormat("Started Process : {0}", exeFile);
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
                foreach (var process in _processes)
                {
                    if (!process.HasExited)
                    {
                        //process.CloseMainWindow();
                        //process.Close();
                        process.Kill();
                    }
                }
                _shutdown = true;
            }
        }

        public experimot_config Config
        {
            get { return _config; }
        }
    }
}
