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

            var config = experimot_config.LoadFromFile(configFile);
            TinyIoCContainer.Current.Register(config);
            
            var context = new Context();
            TinyIoCContainer.Current.Register(context);

            var contextSync = new ContextSync();
            TinyIoCContainer.Current.Register(contextSync);

            var parameterServer = new ParameterServer();
            TinyIoCContainer.Current.Register(parameterServer);

            _processes = new List<Process>();

            _tasks = new List<Task>
            {
                Task.Factory.StartNew(() => RunParameterServer(parameterServer)),
                Task.Factory.StartNew(() => RunContextSync(contextSync)),
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
                Log.ErrorFormat("Exception in Context Sync Task: {0}",ex.StackTrace);
            }
        }

        private void RegisterTypes()
        {
            TinyIoCContainer.Current.Register<Context>().AsSingleton();
            TinyIoCContainer.Current.Register<ParameterServer>().AsSingleton();
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
                foreach (var node in config.nodes)
                {
                    if (node != null && node.enabled && node.process != null)
                    {
                        var exeFile = Environment.ExpandEnvironmentVariables(node.process.path);
                        if (!string.IsNullOrEmpty(exeFile))
                        {
                            try
                            {
                                string paramServer = ParameterUtil.Get(config.parameters, "ParameterClientHost",
                                    "tcp://*");
                                int port = ParameterUtil.Get(config.parameters, "ParameterServerPort",
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
    }
}
