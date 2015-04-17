using System;
using System.IO;
using System.Linq;
using Common.Logging;
using Experimot.Core;
using Experimot.Core.Util;
using NetMQ;
using NetMQ.zmq;
using ProtoBuf;

namespace Experimot.Scheduler
{
    public class ParameterServer : IDisposable
    {
        private readonly experimot_config _config;
        private NetMQContext _ctx;
        private NetMQSocket _socket;
        private bool _disposed;
        private readonly ILog _log = LogManager.GetLogger(typeof (ParameterServer));

        private const int RecvTimeout = 50;

        private bool _startup;

        public ParameterServer(experimot_config config)
        {
            _config = config;
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
                        if (!req.Contains("register"))
                        {
                            Console.WriteLine(@"Received request from {0}", req);
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
                                using (var ms = new MemoryStream())
                                {
                                    Serializer.Serialize(ms, nodeInfo);
                                    _socket.Send(ms.GetBuffer());
                                }
                            }
                        }
                        else // register either motions or behaviors
                        {
                            var name = _socket.ReceiveString(new TimeSpan(0, 0, 0, 0, RecvTimeout));
                            if (req.Contains("motion"))
                            {
                                var motionModule =
                                    ReceiveAndParseGestureDescription<experimot.msgs.GestureRecognitionModule>(_socket,
                                        RecvTimeout);
                                if (motionModule != null)
                                {
                                    Console.WriteLine(@"Module name: {0}", motionModule.name);
                                }
                            }
                            else if (req.Contains("behavior"))
                            {
                                var behaviorModule =
                                    ReceiveAndParseGestureDescription<experimot.msgs.RobotBehaviorModule>(_socket,
                                        RecvTimeout);
                                if (behaviorModule != null)
                                {
                                    Console.WriteLine(@"Module name: {0}", behaviorModule.name);
                                }
                            }
                            else
                            {

                            }
                        }
                    }
                }
                catch (NetMQException zex)
                {
                    // If not timeout
                    if (zex.ErrorCode != ErrorCode.EAGAIN)
                    {
                        _log.ErrorFormat(@"ZMQ Exception: {0}", zex.Message);
                    }
                }
                catch (Exception ex)
                {
                    _log.Error(ex.Message);
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
                    using (var memStream = new MemoryStream(msg.First.Buffer))
                    {
                        var nodeInfo = Serializer.Deserialize<T>(memStream);
                        return nodeInfo;
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
                Console.WriteLine(@"Parameter server running at: {0}", address);
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