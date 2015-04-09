using System;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Windows.Threading;
using Common.Logging;
using ProtoBuf;
using Scheduler;
using NetMQ;
using NetMQ.zmq;

namespace Experimot.Scheduler
{
    public class ParameterServer : IDisposable
    {
        private readonly experimot_config _config;
        private NetMQContext _ctx;
        private NetMQSocket _socket;
        private bool _disposed;
        private readonly ILog Log = LogManager.GetLogger(typeof (ParameterServer));

        private DispatcherTimer _timer;
        private const int RecvTimeout = 100;

        public ParameterServer(experimot_config config)
        {
            _config = config;

            InitZmq(ParameterUtil.Get(config.parameters, "ParameterServerHost", "tcp://*"),
                ParameterUtil.Get(config.parameters, "ParameterServerPort", 5560));

            InitTimer(ParameterUtil.Get(config.parameters, "ParameterServerInterval", 50));
        }

        private void InitTimer(int milliSecInterval)
        {
            if (_timer == null)
            {
                _timer = new DispatcherTimer {Interval = new TimeSpan(0, 0, 0, 0, milliSecInterval)};
                _timer.Tick += TimerTick;
                _timer.IsEnabled = true;
            }
        }

        private void DestroyTimer()
        {
            if (_timer != null)
            {
                _timer.IsEnabled = false;
                _timer.Tick -= TimerTick;
            }
        }

        private void TimerTick(object sender, EventArgs e)
        {
            if (_socket != null && _config != null)
            {
                try
                {
                    //var req = _socket.Recv(Encoding.ASCII, RecvTimeout);
                    var req = _socket.ReceiveString(new TimeSpan(0,0,0,0,RecvTimeout));
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
                                //{
                                //    Log.ErrorFormat("Parameter Send Failed: {0}", req);
                                //}
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
                catch (System.Exception ex)
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

            DestroyTimer();
            TerminateZmq();

            _disposed = true;
        }
    }
}