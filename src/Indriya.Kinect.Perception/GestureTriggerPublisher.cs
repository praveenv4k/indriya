using System.IO;
using Indriya.Core.Msgs;
using NetMQ;
using ProtoBuf;

namespace Indriya.Kinect.Perception
{
    /// <summary>
    /// Interaction logic for MainWindow
    /// </summary>
    public class GestureTriggerPublisher
    {
        private NetMQContext _ctx;
        private NetMQSocket _socket;
        private readonly string _host;
        private readonly uint _port;
        private readonly string _topic;
        private readonly object _sync = new object();

        private static GestureTriggerPublisher _publisher;

        public static GestureTriggerPublisher Create(string host, uint port, string topic)
        {
            return _publisher ?? (_publisher = new GestureTriggerPublisher(host, port, topic));
        }

        public static GestureTriggerPublisher Instance
        {
            get { return _publisher ?? (_publisher = new GestureTriggerPublisher()); }
        }

        /// <summary>
        /// Initializes a new instance of the MainWindow class.
        /// </summary>
        private GestureTriggerPublisher() : this("tcp://*", 5580, "GTP")
        {
        }

        /// <summary>
        /// Initializes a new instance of the MainWindow class.
        /// </summary>
        private GestureTriggerPublisher(string host, uint port, string topic)
        {
            _host = host;
            _port = port;
            _topic = topic;
        }

        private void InitZmq()
        {
            if (_ctx == null)
            {
                _ctx = NetMQContext.Create();
                _socket = _ctx.CreatePublisherSocket();
                var address = string.Format("{0}:{1}", _host, _port);
                _socket.Bind(address);
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

        /// <summary>
        /// Execute start up tasks
        /// </summary>
        public void Initialize()
        {
            InitZmq();
        }

        /// <summary>
        /// Execute shutdown tasks
        /// </summary>
        public void Terminate()
        {
            TerminateZmq();
        }

        public void PublishGestureTrigger(GestureTriggers gesture, bool force = false)
        {
            if (gesture != null && gesture.motion.Count > 0 && _socket != null)
            {
                lock (_sync)
                {
                    _socket.SendMore(_topic);

                    using (var ms = new MemoryStream())
                    {
                        Serializer.Serialize(ms, gesture);
                        _socket.Send(ms.GetBuffer(), (int) ms.Length);
                    }
                }
            }
        }
    }
}
