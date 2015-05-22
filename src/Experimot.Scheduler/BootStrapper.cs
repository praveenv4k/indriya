using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Common.Logging;
using Experimot.Core;
using Experimot.Core.Util;
using Experimot.Scheduler.Data;
using Experimot.Scheduler.Scriptcs;
using Experimot.Scheduler.Tasks;
using Experimot.Scheduler.Web;
using Nancy.TinyIoc;
using Quartz;
using Quartz.Impl;
using Quartz.Impl.Matchers;

namespace Experimot.Scheduler
{
    internal class BootStrapper
    {
        private bool _startup;
        private bool _shutdown;
        private static readonly ILog Log = LogManager.GetLogger(typeof (BootStrapper));
        private readonly IList<Process> _processes;
        private readonly IList<Task> _tasks;
        private volatile bool _shouldStop;

        public BootStrapper(string configFile)
        {
            RegisterTypes();

            TinyIoCContainer.Current.Register(this);

            var config = experimot_config.LoadFromFile(configFile);
            TinyIoCContainer.Current.Register(config);

            var context = new Context();
            TinyIoCContainer.Current.Register(context);

            var contextSync = new ContextSync();
            TinyIoCContainer.Current.Register(contextSync);

            var parameterServer = new ParameterServer();
            TinyIoCContainer.Current.Register(parameterServer);

            var contextServer = new ContextServer();
            TinyIoCContainer.Current.Register(contextServer);

            _processes = new List<Process>();

            _tasks = new List<Task>
            {
                Task.Factory.StartNew(() => RunParameterServer(parameterServer)),
                Task.Factory.StartNew(() => RunContextSync(contextSync)),
                Task.Factory.StartNew(() => RunContextServer(contextServer))
            };

            bool enableWebServer = ParameterUtil.Get(config.parameters, "WebServerEnabled", false);
            if (enableWebServer)
            {
                var server = new ExperimotWeb(config);
                TinyIoCContainer.Current.Register(server);
                _tasks.Add(Task.Factory.StartNew(() => RunExperimotServer(server)));
            }

            InitializeScheduler();
        }

        private void RunParameterServer(object arg)
        {
            try
            {
                var server = arg as ParameterServer;
                if (server != null)
                {
                    server.Start();
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
            catch (Exception ex)
            {
                Log.ErrorFormat("Exception in parameter server: {0}", ex.StackTrace);
            }
        }

        private void RunContextServer(object arg)
        {
            try
            {
                var server = arg as ContextServer;
                if (server != null)
                {
                    server.Start();
                    Log.Info("Context server Started");
                    while (!_shouldStop)
                    {
                        server.Run();
                        Thread.Sleep(40);
                    }
                    server.Shutdown();
                }
                Log.Info("Context server Completed");
            }
            catch (Exception ex)
            {
                Log.ErrorFormat("Exception in context server: {0}", ex.StackTrace);
            }
        }

        private void RunExperimotServer(object arg)
        {
            try
            {
                var server = arg as ExperimotWeb;
                if (server != null)
                {
                    server.Start();
                    Log.Info("Experimot server Started");
                }
                else
                {
                    Log.Info("server instance null. looks like it is disabled");
                }
                Log.Info("Experimot server Completed");
            }
            catch (Exception ex)
            {
                Log.ErrorFormat("Exception in experimot web server: {0}", ex.StackTrace);
            }
        }

        private void RunContextSync(object arg)
        {
            try
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
            catch (Exception ex)
            {
                Log.ErrorFormat("Exception in Context Sync Task: {0}", ex.StackTrace);
            }
        }

        private void RegisterTypes()
        {
            TinyIoCContainer.Current.Register<BootStrapper>().AsSingleton();
            TinyIoCContainer.Current.Register<Context>().AsSingleton();
            TinyIoCContainer.Current.Register<ParameterServer>().AsSingleton();
            TinyIoCContainer.Current.Register<ContextServer>().AsSingleton();
            TinyIoCContainer.Current.Register<ContextSync>().AsSingleton();
            TinyIoCContainer.Current.Register<StdSchedulerFactory>().AsSingleton();
            TinyIoCContainer.Current.Register<ExperimotWeb>().AsSingleton();
        }

        private void InitializeScheduler()
        {
            // our properties that enable XML configuration plugin
            // and makes it watch for changes every two minutes (120 seconds)
            var properties = new NameValueCollection();
            properties["quartz.plugin.triggHistory.type"] = "Quartz.Plugin.History.LoggingJobHistoryPlugin";

            properties["quartz.plugin.jobInitializer.type"] = "Quartz.Plugin.Xml.XMLSchedulingDataProcessorPlugin";
            properties["quartz.plugin.jobInitializer.fileNames"] = "quartz_config.xml";
            properties["quartz.plugin.jobInitializer.failOnFileNotFound"] = "true";
            //properties["quartz.plugin.jobInitializer.scanInterval"] = "120";

            var factory = new StdSchedulerFactory(properties);
            TinyIoCContainer.Current.Register(factory);
            var scheduler = factory.GetScheduler();

            scheduler.ListenerManager.AddJobListener(new JobListenerImpl(), GroupMatcher<JobKey>.AnyGroup());
        }

        public void StartUp()
        {
            var config = TinyIoCContainer.Current.Resolve<experimot_config>();
            if (!_startup && config != null)
            {
                string paramServer = ParameterUtil.Get(config.parameters, "ParameterClientHost",
                    "tcp://localhost");
                int paramPort = ParameterUtil.Get(config.parameters, "ParameterServerPort",
                    5560);

                string contextServer = ParameterUtil.Get(config.parameters, "ContextClientHost",
                    "tcp://localhost");
                int contextPort = ParameterUtil.Get(config.parameters, "ContextServerPort",
                    5800);

                foreach (var node in config.nodes)
                {
                    if (node != null && node.enabled && node.process != null)
                    {
                        var exeFile = Environment.ExpandEnvironmentVariables(node.process.path);
                        if (!string.IsNullOrEmpty(exeFile))
                        {
                            try
                            {


                                var args = string.Format("{3} --name={0} --param={1}:{2}", node.name, paramServer,
                                    paramPort,
                                    Environment.ExpandEnvironmentVariables(node.process.args));

                                if (node.process.type == "scriptcs")
                                {
                                    //args = string.Format("{3} -- --name={0} --param={1}:{2}", node.name, paramServer, port,
                                    //Environment.ExpandEnvironmentVariables(node.process.args));
                                    args = string.Format("{3} -- {0} {1}:{2}", node.name, contextServer, contextPort,
                                        Environment.ExpandEnvironmentVariables(node.process.args));
                                }

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

                var factory = TinyIoCContainer.Current.Resolve<StdSchedulerFactory>();
                if (factory != null)
                {
                    factory.GetScheduler().Start();
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
            try
            {
                if (!_shutdown)
                {
                    _shouldStop = true;
                    // Stop main program is it being executed
                    MainProgramExecutionRequest(ExecutionRequest.Stop);
                    foreach (var process in _processes)
                    {
                        if (!process.HasExited)
                        {
                            //process.CloseMainWindow();
                            //process.Close();
                            process.Kill();
                        }
                    }
                    try
                    {
                        var factory = TinyIoCContainer.Current.Resolve<StdSchedulerFactory>();
                        var scheduler = factory.GetScheduler();
                        if (scheduler != null)
                        {
                            var keys = scheduler.GetJobKeys(GroupMatcher<JobKey>.GroupEquals("MainGroup"));
                            if (keys != null && keys.Count > 0)
                            {
                                scheduler.DeleteJobs(keys.ToList());
                            }
                            scheduler.Shutdown();
                            Log.Info("Quartz Scheduler Shutdown");
                        }

                        var server = TinyIoCContainer.Current.Resolve<ExperimotWeb>(ResolveOptions.FailUnregisteredOnly);
                        if (server != null)
                        {
                            server.Stop();
                        }
                    }
                    catch (Exception ex)
                    {
                        Log.ErrorFormat("Web shutdown exception: {0}", ex.Message);
                    }
                    Task.WaitAll(_tasks.ToArray(), new TimeSpan(0, 0, 0, 5));
                    _shutdown = true;
                }
            }
            catch (Exception ex)
            {
                Log.ErrorFormat("Exception occured while shutdown: {0}", ex.Message);
            }
        }

        public void RequestMainProgramGeneration(string jsonString)
        {
            var config = TinyIoCContainer.Current.Resolve<experimot_config>();
            var outputPath = ParameterUtil.Get(config.parameters, "MainProgramFilePath", "");
            if (!string.IsNullOrEmpty(outputPath))
            {
                outputPath = Environment.ExpandEnvironmentVariables(outputPath);
                ProgramGenerator.GeneratePrograms(jsonString, outputPath);
            }
        }

        public void RequestMainProgramGeneration(IDictionary<string, string> map)
        {
            var config = TinyIoCContainer.Current.Resolve<experimot_config>();
            var outputPath = ParameterUtil.Get(config.parameters, "MainProgramFilePath", "");
            if (!string.IsNullOrEmpty(outputPath))
            {
                outputPath = Environment.ExpandEnvironmentVariables(outputPath);
                var dict = new Dictionary<string, string>();
                dict.Add("Greet_Left", "wave");
                ProgramGenerator.GeneratePrograms(dict, outputPath);
            }
        }

        private Process _mainProgramProcess;

        public void MainProgramExecutionRequest(ExecutionRequest request)
        {
            var config = TinyIoCContainer.Current.Resolve<experimot_config>();
            string contextServer = ParameterUtil.Get(config.parameters, "ContextClientHost",
                "tcp://localhost");
            int contextPort = ParameterUtil.Get(config.parameters, "ContextServerPort",
                5800);
            var mainProgram = config.nodes.FirstOrDefault(s => s.name == "scriptcs_program");
            if (mainProgram != null)
            {
                switch (request)
                {
                    case ExecutionRequest.Start:
                        if (_mainProgramProcess == null)
                        {
                            var exeFile = Environment.ExpandEnvironmentVariables(mainProgram.process.path);
                            var args = string.Format("{3} -- {0} {1}:{2}", mainProgram.name, contextServer, contextPort,
                                Environment.ExpandEnvironmentVariables(mainProgram.process.args));
                            var workingDir = Path.GetDirectoryName(exeFile);
                            _mainProgramProcess = new Process
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
                            _mainProgramProcess.Start();
                            Log.InfoFormat("Started Process : {0} {1}", exeFile, args);
                        }
                        break;
                    case ExecutionRequest.Pause:
                        break;
                    case ExecutionRequest.Stop:
                        if (_mainProgramProcess != null && _mainProgramProcess.HasExited)
                        {
                            _mainProgramProcess.Dispose();
                            _mainProgramProcess = null;
                        }
                        if (_mainProgramProcess != null && !_mainProgramProcess.HasExited)
                        {
                            _mainProgramProcess.Kill();
                            _mainProgramProcess.Dispose();
                            _mainProgramProcess = null;
                        }
                        Log.Info("Stopped Main Program");
                        break;
                    default:
                        throw new ArgumentOutOfRangeException("request");
                }
            }

        }
    }
}
