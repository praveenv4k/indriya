using System;
using System.IO;
using NetMQ;
using ProtoBuf;

namespace Experimot.Core
{
    public class MessagePublisher<T> where T : class, IExtensible
    {
        private NetMQContext _ctx;
        private NetMQSocket _socket;
        private readonly uint _port;
        private readonly string _topic;

        /// <summary>
        /// Initializes a new instance of the MainWindow class.
        /// </summary>
        public MessagePublisher(string host, uint port, string topic)
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

        /// <summary>
        /// Handles the body frame data arriving from the sensor
        /// </summary>
        /// <param name="msg"></param>
        public virtual void Update(T msg)
        {
            if (!CanSend) return;
            Publish(msg);
        }

        protected virtual bool IsValid(T msg)
        {
            if (msg != null)
            {
                return true;
            }
            return false;
        }

        protected int SendFrequency = 2;
        private int _sendCount;
        private readonly string _host;

        protected virtual bool CanSend
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

        protected virtual void Publish(T msg, bool force = false)
        {
            if (msg != null && _socket != null)
            {
                //Console.WriteLine("Will publish msg type : {0}", typeof(T).Name);
                if (force || IsValid(msg))
                {
                    _socket.SendMore(_topic);

                    using (var ms = new MemoryStream())
                    {
                        Serializer.Serialize(ms, msg);
                        _socket.Send(ms.GetBuffer(), (int) ms.Length);
                        //Console.WriteLine("Published msg type : {0}", typeof (T).Name);
                    }
                }
            }
        }
    }
}
