using System;
using System.IO;
using System.Linq;
using System.Windows.Threading;
using Common.Logging;
using NetMQ;
using NetMQ.zmq;
using ProtoBuf;
using Scheduler;

namespace Experimot.Scheduler
{
    public class ParameterServer : IDisposable
    {
        private readonly experimot_config _config;
        private NetMQContext _ctx;
        private NetMQSocket _socket;
        private bool _disposed;
        private readonly ILog Log = LogManager.GetLogger(typeof (ParameterServer));

        //private DispatcherTimer _timer;
        private const int RecvTimeout = 100;

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

                //InitTimer(ParameterUtil.Get(_config.parameters, "ParameterServerInterval", 50));

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
                        Console.WriteLine("Received request from {0}", req);
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
                }
                catch (NetMQException zex)
                {
                    // If not timeout
                    if (zex.ErrorCode != ErrorCode.EAGAIN)
                    {
                        Log.ErrorFormat("ZMQ Exception: {0}", zex.Message);
                    }
                }
                catch (Exception ex)
                {
                    Log.Error(ex.Message);
                }
            }
        }

        private void TimerTick(object sender, EventArgs e)
        {
            Run();
        }

        private void InitZmq(string host, int port)
        {
            if (_ctx == null)
            {
                _ctx = NetMQContext.Create();
                _socket = _ctx.CreateResponseSocket();
                var address = string.Format("{0}:{1}", host, port);
                _socket.Bind(address);
                Console.WriteLine("Parameter server running at: {0}", address);
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