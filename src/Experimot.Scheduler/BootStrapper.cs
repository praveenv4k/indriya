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
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Serialization;
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

        private void TestJson(string str)
        {
            var humanStr =
                "[{\"Id\":2,\"HeadPosition\":null,\"TorsoPosition\":null,\"TorsoOrientation\":null,\"Gestures\":[{\"Name\":\"Greet_Left\",\"Mode\":1,\"Active\":false,\"Progress\":0,\"Confidence\":0,\"Count\":0},{\"Name\":\"Greet_Right\",\"Mode\":1,\"Active\":false,\"Progress\":0,\"Confidence\":0,\"Count\":0}]}]";
            JArray humanArray = JArray.Parse(humanStr);
            if (humanArray != null && humanArray.Count > 0)
            {
                foreach (var human in humanArray)
                {
                    var gestures = human.SelectToken("$.Gestures");
                    foreach (var gesture in gestures)
                    {
                        string name = gesture.Value<string>("Name");
                        bool active = gesture.Value<bool>("Active");
                        int confidence = gesture.Value<int>("Confidence");
                        Log.InfoFormat(@"Name : {0}, Active : {1}, Confidence: {2}", name, active, confidence);
                    }
                }
            }
            var behaviorStr =
                "[{\"name\":\"nao_behavior_manager\",\"param\":[],\"behaviors\":[{\"name\":\"crouch\",\"type\":0,\"state\":0},{\"name\":\"stand\",\"type\":0,\"state\":0},{\"name\":\"wave\",\"type\":0,\"state\":0},{\"name\":\"greet\",\"type\":0,\"state\":0}],\"responder\":{\"Host\":\"tcp://localhost\",\"Port\":5590}}]";
            JArray behaviorArray = JArray.Parse(behaviorStr);
            if (behaviorArray != null && behaviorArray.Count > 0)
            {
                foreach (var module in behaviorArray)
                {
                    var moduleName = module.Value<string>("name");
                    var behaviors = module.SelectToken("$.behaviors");
                    foreach (var behavior in behaviors)
                    {
                        string name = behavior.Value<string>("name");
                        int type = behavior.Value<int>("type");
                        int state = behavior.Value<int>("state");
                        Log.InfoFormat(@"Name : {0}, Active : {1}, Confidence: {2}", name, type, state);
                    }
                    var responder = module.SelectToken("$.responder");
                    if (responder != null)
                    {
                        string host = responder.Value<string>("Host");
                        int port = responder.Value<int>("Port");
                        Log.InfoFormat(@"Host : {0}, Port : {1}", host, port);
                    }
                }
            }
            if (!string.IsNullOrEmpty(str))
            {
                var obj = JObject.Parse(str);
                if (obj != null)
                {
                    Log.InfoFormat("Json object count : {0}", obj.Count);
                    var token2 = obj.SelectToken("$.parameters"); //$.Manufacturers[?(@.Name == 'Acme Co')]
                    if (token2 != null)
                    {
                        
                    }
                    var token = obj.SelectToken("$.parameters[?(@.key == 'ApplicationName')]"); //$.Manufacturers[?(@.Name == 'Acme Co')]
                    if (token != null)
                    {
                        Log.InfoFormat("Value : {0}", token.Value<string>("value"));
                        
                    }
                }
            }   
        }

        public BootStrapper(string configFile)
        {
            RegisterTypes();

            var config = experimot_config.LoadFromFile(configFile);
            TinyIoCContainer.Current.Register(config);

            TestJson(JsonConvert.SerializeObject(config));

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
                Log.ErrorFormat("Exception in Context Sync Task: {0}",ex.StackTrace);
            }
        }

        private void RegisterTypes()
        {
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

                                if (node.process.type == "scriptcs")
                                {
                                    args = string.Format("{3} -- --name={0} --param={1}:{2}", node.name, paramServer, port,
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
