using System.Collections.Generic;
using System.IO;
using experimot.msgs;
using Microsoft.Kinect;
using ProtoBuf;
using NetMQ;
using Joint = Microsoft.Kinect.Joint;

namespace Experimot.Kinect.Perception
{
    /// <summary>
    /// Interaction logic for MainWindow
    /// </summary>
    public class HumanPosePublisher
    {
        private NetMQContext _ctx;
        private NetMQSocket _socket;
        private readonly uint _port;
        private readonly string _topic;
        private bool _noBodyTracked;
        private int _emptyMsgSent;

        /// <summary>
        /// Initializes a new instance of the MainWindow class.
        /// </summary>
        public HumanPosePublisher()
            : this("tcp://*", 5571, "HPP")
        {
        }

        /// <summary>
        /// Initializes a new instance of the MainWindow class.
        /// </summary>
        public HumanPosePublisher(string host, uint port, string topic)
        {
            _host = host;
            _port = port;
            _topic = topic;
            _noBodyTracked = false;
            _emptyMsgSent = 0;
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

        /// <summary>
        /// Handles the body frame data arriving from the sensor
        /// </summary>
        /// <param name="humans"></param>
        public void UpdateHumans(Humans humans)
        {
            if (!CanSend) return;
            PublishHumans(humans);
        }

        private const int SendFrequency = 2;
        private int _sendCount;
        private readonly string _host;

        private bool CanSend
        {
            get
            {
                if (_sendCount < SendFrequency)
                {
                    _sendCount++;
                }
                else
                {
                    _sendCount = 0;
                }
                return _sendCount == 0;
            }
        }

        private void PublishHumans(Humans humans, bool force = false)
        {
            if (humans != null && _socket != null)
            {
                if (force || humans.human.Count > 0)
                {
                    _socket.SendMore(_topic);

                    using (var ms = new MemoryStream())
                    {
                        Serializer.Serialize(ms, humans);
                        _socket.Send(ms.GetBuffer(), (int) ms.Length);
                    }
                }
            }

        }
    }
}
