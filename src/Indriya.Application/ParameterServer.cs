using System;
using System.IO;
using System.Linq;
using Common.Logging;
using Indriya.Application.Data;
using Indriya.Core;
using Indriya.Core.Util;
using Nancy.TinyIoc;
using NetMQ;
using ProtoBuf;

namespace Indriya.Application
{
    public class ParameterServer : IDisposable
    {
        private readonly AppConfig _config;
        private NetMQContext _ctx;
        private NetMQSocket _socket;
        private bool _disposed;
        private static readonly ILog Log = LogManager.GetLogger(typeof (ParameterServer));

        private const int RecvTimeout = 50;
        private readonly int _interval = 40;
        private bool _startup;
        private readonly Context _worldCtx;

        public ParameterServer()
        {
            _worldCtx = TinyIoCContainer.Current.Resolve<Context>();
            _config = TinyIoCContainer.Current.Resolve<AppConfig>();
            _interval = ParameterUtil.Get(_config.parameters, "ParameterServerInterval", _interval);
        }

        public int Interval
        {
            get { return _interval; }
        }

        public void Start()
        {
            if (!_startup && _config != null)
            {
                InitZmq(ParameterUtil.Get(_config.parameters, "ParameterServerHost", "tcp://*"),
                    ParameterUtil.Get(_config.parameters, "ParameterServerPort", 5560));
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
                        if (req.Contains("register"))
                        {
                            Log.InfoFormat(@"Registration request {0}", req);
                            var name = _socket.ReceiveString(new TimeSpan(0, 0, 0, 0, RecvTimeout));
                            Log.InfoFormat(@"Registration request from {0}", name);
                            if (req.Contains("motion"))
                            {
                                var motionModule =
                                    ReceiveAndParseGestureDescription<Indriya.Core.Msgs.GestureRecognitionModule>(_socket,
                                        RecvTimeout);
                                if (motionModule != null)
                                {
                                    if (_worldCtx != null)
                                    {
                                        App.Current.Dispatcher.Invoke(delegate // <--- HERE
                                        {
                                            _worldCtx.RegisterMotionRecognitionModule(motionModule);
                                        });
                                    }
                                    Log.InfoFormat(@"Module name: {0}", motionModule.name);
                                    _socket.Send("Registration successful!");
                                }
                            }
                            else if (req.Contains("behavior"))
                            {
                                var behaviorModule =
                                    ReceiveAndParseGestureDescription<Indriya.Core.Msgs.RobotBehaviorModule>(_socket,
                                        RecvTimeout);
                                if (behaviorModule != null)
                                {
                                    if (_worldCtx != null)
                                    {
                                        App.Current.Dispatcher.Invoke(delegate // <--- HERE
                                        {
                                            _worldCtx.RegisterRobotBehaviorModule(behaviorModule);
                                        });
                                    }
                                    Log.InfoFormat(@"Module name: {0}", behaviorModule.name);
                                    _socket.Send("Registration successful!");
                                }
                            }
                            else if (req.Contains("speech"))
                            {
                                var behaviorModule =
                                    ReceiveAndParseGestureDescription<Indriya.Core.Msgs.VoiceRecognitionModule>(_socket,
                                        RecvTimeout);
                                if (behaviorModule != null)
                                {
                                    if (_worldCtx != null)
                                    {
                                        App.Current.Dispatcher.Invoke(delegate // <--- HERE
                                        {
                                            _worldCtx.RegisterVoiceRecognitionModule(behaviorModule);
                                        });
                                    }
                                    Log.InfoFormat(@"Module name: {0}", behaviorModule.name);
                                    _socket.Send("Registration successful!");
                                }
                            }
                        }
                        else if (req.Contains("file_request"))
                        {
                            Log.InfoFormat(@"File request {0}", req);
                            var fileName = _socket.ReceiveString(new TimeSpan(0, 0, 0, 0, RecvTimeout));
                            Log.InfoFormat(@"Request for file {0}", fileName);
                            _socket.Send(File.Exists(fileName)
                                ? File.ReadAllText(fileName)
                                : "File not found!");
                        }
                        else // Node parameter request
                        {
                            Log.InfoFormat(@"Received request from {0}", req);
                            var nodeExist = _config.nodes.FirstOrDefault(s => s.name == req);
                            if (nodeExist != null)
                            {
                                var nodeInfo = MessageUtil.XmlToMessageNode(nodeExist);
                                var globalParams = MessageUtil.XmlToMessageParam(_config.parameters);
                                foreach (var item in globalParams)
                                {
                                    var existParam = nodeInfo.param.FirstOrDefault(s => s.key == item.key);
                                    if (existParam == null)
                                    {
                                        nodeInfo.param.Add(item);
                                    }
                                }
                                var globalRefs = nodeInfo.param.Where(s => s.value.StartsWith("$", StringComparison.OrdinalIgnoreCase)).ToList();
                                for (int i = 0; i < globalRefs.Count; i++)
                                {
                                    var param = globalRefs[i];
                                    var paramName = param.value.TrimStart('$');
                                    var gParamExist = nodeInfo.param.FirstOrDefault(s => s.key == paramName);
                                    if (gParamExist != null)
                                    {
                                        param.value = gParamExist.value;
                                        param.dataType = gParamExist.dataType;
                                    }
                                }
                                using (var ms = new MemoryStream())
                                {
                                    Serializer.Serialize(ms, nodeInfo);
                                    _socket.Send(ms.GetBuffer(), (int) ms.Length);
                                }
                            }
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

        private static T ReceiveAndParseGestureDescription<T>(NetMQSocket socket, int timeout) where T : class
        {
            var msg = socket.ReceiveMessage(new TimeSpan(0, 0, 0, 0, timeout));
            if (msg != null)
            {
                if (msg.FrameCount > 0)
                {
                    try
                    {
                        using (var memStream = new MemoryStream(msg.First.Buffer))
                        {
                            var nodeInfo = Serializer.Deserialize<T>(memStream);
                            return nodeInfo;
                        }
                    }
                    catch (ProtoException ex)
                    {
                        Log.ErrorFormat("Exception while deserializing registration message: {0} ", ex.Message);
                    }
                }
            }
            else
            {
                Console.WriteLine(@"Message buffer empty!");
            }
            return default(T);
        }

        private void InitZmq(string host, int port)
        {
            if (_ctx == null)
            {
                _ctx = NetMQContext.Create();
                _socket = _ctx.CreateResponseSocket();
                var address = string.Format("{0}:{1}", host, port);
                _socket.Bind(address);
                Log.InfoFormat(@"Parameter server running at: {0}", address);
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
                Log.Info(@"Parameter server disposed");
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