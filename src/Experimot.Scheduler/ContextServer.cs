using System;
using System.Linq;
using Common.Logging;
using Experimot.Core;
using Experimot.Core.Util;
using Experimot.Scheduler.Data;
using Nancy.TinyIoc;
using NetMQ;
using Newtonsoft.Json;

namespace Experimot.Scheduler
{
    public class ContextServer : IDisposable
    {
        private readonly experimot_config _config;
        private NetMQContext _ctx;
        private NetMQSocket _socket;
        private bool _disposed;
        private static readonly ILog Log = LogManager.GetLogger(typeof (ContextServer));

        private const int RecvTimeout = 50;

        private static readonly string[] SupportedRequests = {
            "human/{0}",
            "behavior_modules",
            "behavior_module/{0}",
            "motion_modules",
            "robot",
            "humans",
            "body/{0}",
            "voice_command"
        };

        private const string UnknownRequest = @"Unknown request. Support request : ";

        private bool _startup;

        public ContextServer()
        {
            _config = TinyIoCContainer.Current.Resolve<experimot_config>();
        }

        public void Start()
        {
            if (!_startup && _config != null)
            {
                InitZmq(ParameterUtil.Get(_config.parameters, "ContextServerHost", "tcp://*"),
                    ParameterUtil.Get(_config.parameters, "ContextServerPort", 5800));
                _startup = true;
            }
        }

        public void Shutdown()
        {
            if (_startup)
            {
                TerminateZmq();
            }
        }

        public void Run()
        {
            if (_socket != null && _config != null)
            {
                try
                {
                    var req = _socket.ReceiveString(new TimeSpan(0, 0, 0, 0, RecvTimeout));
                    if (!string.IsNullOrEmpty(req))
                    {
                        if (req.Contains("node"))
                        {
                            var name = req.Replace("node_", "");
                            if (_config != null)
                            {
                                var node = _config.nodes.FirstOrDefault(s => s.name == name);
                                if (node != null)
                                {
                                    var ret = node.Clone();
                                    foreach (var p in _config.parameters)
                                    {
                                        if (ret.parameters.FirstOrDefault(s => s.key == p.key) == null)
                                        {
                                            ret.parameters.Add(p);
                                        }
                                    }
                                    string json = JsonConvert.SerializeObject(ret);
                                    _socket.Send(json);
                                }
                            }
                        }
                        else if (req.Contains("humans"))
                        {
                            var context = TinyIoCContainer.Current.Resolve<Context>();
                            if (context != null)
                            {
                                string json = JsonConvert.SerializeObject(context.Humans);
                                _socket.Send(json);
                            }
                        }
                        else if (req.Contains("body/"))
                        {
                            string json = string.Empty;
                            string[] strArray = req.Split('/');
                            int id = -1;
                            if (strArray.Length == 2)
                            {
                                int.TryParse(strArray[1], out id);
                            }
                            if (id != -1)
                            {
                                var context = TinyIoCContainer.Current.Resolve<Context>();
                                if (context != null)
                                {
                                    var human = context.Humans.FirstOrDefault(s => s.Id == id);
                                    if (human != null)
                                    {
                                        json = JsonConvert.SerializeObject(human.Body);
                                    }
                                }
                            }
                            _socket.Send(json);
                        }
                        else if (req.Contains("human/"))
                        {
                            string json = string.Empty;
                            string[] strArray = req.Split('/');
                            int id = -1;
                            if (strArray.Length == 2)
                            {
                                int.TryParse(strArray[1], out id);
                            }
                            if (id != -1)
                            {
                                var context = TinyIoCContainer.Current.Resolve<Context>();
                                if (context != null)
                                {
                                    var human = context.Humans.FirstOrDefault(s => s.Id == id);
                                    json = JsonConvert.SerializeObject(human);
                                    //_socket.Send(json);
                                }
                            }
                            _socket.Send(json);
                        }
                        else if (req.Contains("behavior_modules"))
                        {
                            var context = TinyIoCContainer.Current.Resolve<Context>();
                            if (context != null)
                            {
                                string json = JsonConvert.SerializeObject(context.BehaviorModules);
                                _socket.Send(json);
                            }
                        }
                        else if (req.Contains("behavior_module/"))
                        {
                            string json = string.Empty;
                            string[] strArray = req.Split('/');
                            string id = string.Empty;
                            if (strArray.Length == 2)
                            {
                                id = strArray[1];
                            }
                            if (!string.IsNullOrEmpty(id))
                            {
                                var context = TinyIoCContainer.Current.Resolve<Context>();
                                if (context != null)
                                {
                                    var human = context.BehaviorModules.FirstOrDefault(s => s.name == id);
                                    json = JsonConvert.SerializeObject(human);
                                }
                            }
                            _socket.Send(json);
                        }
                        else if (req.Contains("motion_modules"))
                        {
                            var context = TinyIoCContainer.Current.Resolve<Context>();
                            if (context != null)
                            {
                                string json = JsonConvert.SerializeObject(context.MotionModules);
                                _socket.Send(json);
                            }
                        }
                        else if (req.Contains("robot"))
                        {
                            var context = TinyIoCContainer.Current.Resolve<Context>();
                            if (context != null)
                            {
                                string json = JsonConvert.SerializeObject(context.Robot);
                                _socket.Send(json);
                            }
                        }
                        else if (req.Contains("world_frame"))
                        {
                            var context = TinyIoCContainer.Current.Resolve<Context>();
                            if (context != null)
                            {
                                string json = JsonConvert.SerializeObject(context.WorldFrame);
                                _socket.Send(json);
                            }
                        }
                        else if (req.Contains("voice_command"))
                        {
                            var context = TinyIoCContainer.Current.Resolve<Context>();
                            if (context != null)
                            {
                                string json = JsonConvert.SerializeObject(context.VoiceCommandManager);
                                _socket.Send(json);
                            }
                        }
                        else
                        {
                            _socket.Send(UnknownRequest + string.Join(", ", SupportedRequests));
                        }
                    }
                }
                catch (NetMQException zex)
                {
                    // If not timeout
                    if (zex.ErrorCode != ErrorCode.TryAgain)
                    {
                        Log.ErrorFormat(@"ZMQ Exception: {0}", zex.Message);
                    }
                }
                catch (Exception ex)
                {
                    Log.Error(ex.Message);
                }
            }
        }

        private void InitZmq(string host, int port)
        {
            if (_ctx == null)
            {
                _ctx = NetMQContext.Create();
                _socket = _ctx.CreateResponseSocket();
                var address = string.Format("{0}:{1}", host, port);
                _socket.Bind(address);
                Log.InfoFormat(@"Context server running at: {0}", address);
            }
        }

        private void TerminateZmq()
        {
            if (_socket != null)
            {
                _socket.Dispose();
                if (_ctx != null)
                {
                    _ctx.Dispose();
                    _ctx = null;
                }
                Log.Info(@"Context server disposed");
            }

        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        // Protected implementation of Dispose pattern. 
        protected virtual void Dispose(bool disposing)
        {
            if (_disposed)
                return;

            if (disposing)
            {
            }

            TerminateZmq();

            _disposed = true;
        }
    }
}