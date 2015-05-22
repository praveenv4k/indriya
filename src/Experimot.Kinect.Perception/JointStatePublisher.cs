using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Windows.Threading;
using CsvHelper;
using experimot.msgs;
using NetMQ;
using ProtoBuf;

namespace Experimot.Kinect.Perception
{
    public class JointStatePublisher
    {
        private NetMQContext _ctx;
        private NetMQSocket _socket;
        private int _port = 5563;
        private DispatcherTimer _timer;
        private Queue<JointValueVector> _jvList;
        private string _topic;
        private UTF8Encoding _encoding;
        private Dictionary<int, int> _jointMap;

        public JointStatePublisher()
        {
            _topic = "RSP";
            _encoding = new UTF8Encoding();
            _jvList = new Queue<JointValueVector>();

            _jointMap = new Dictionary<int,int>();
			_jointMap.Add(0, 1);
			_jointMap.Add(1, 0);
			_jointMap.Add(2, 9);
			_jointMap.Add(3, 8);
			_jointMap.Add(4, 7);
			_jointMap.Add(5, 10);
			_jointMap.Add(6, 2);
			_jointMap.Add(7, 3);
			_jointMap.Add(8, 11);
			_jointMap.Add(9, 12);
			_jointMap.Add(10, 5);
			_jointMap.Add(11, 4);
			_jointMap.Add(12, 13);
			_jointMap.Add(13, 6);
			_jointMap.Add(14, 20);
			_jointMap.Add(15, 19);
			_jointMap.Add(16, 21);
			_jointMap.Add(17, 14);
			_jointMap.Add(18, 15);
			_jointMap.Add(19, 22);
			_jointMap.Add(20, 23);
			_jointMap.Add(21, 17);
			_jointMap.Add(22, 16);
			_jointMap.Add(23, 24);
			_jointMap.Add(24, 18);

        }

        public void Terminate()
        {
            TerminateZmq();
        }

        public void Initialize()
        {
            InitZmq();
            LoadCsv(@"datalog.csv");

            _timer = new DispatcherTimer();
            _timer.Interval = new TimeSpan(0, 0, 0, 0, 100);
            _timer.Tick += _timer_Tick;
            _timer.IsEnabled = true;
        }

        void _timer_Tick(object sender, EventArgs e)
        {
            if (_jvList != null && _socket != null)
            {
                bool noData = false;
                try
                {
                    var item = _jvList.Dequeue();
                    if (item == null)
                    {
                        noData = true;
                    }
                    else
                    {
                        //_socket.SendMore(new ZFrame(_topic));
                        _socket.SendMore(_topic);
                        using (var ms = new MemoryStream())
                        {
                            Serializer.Serialize(ms, item);
                            //_socket.Send(new ZFrame(ms.GetBuffer()));
                            _socket.Send(ms.GetBuffer(),(int)ms.Length);
                        }
                    }
                }
                catch (Exception ex)
                {
                    Debug.WriteLine(ex.Message);
                    noData = true;
                }
                finally
                {
                    if (noData)
                    {
                        _timer.IsEnabled = false;
                    }
                }
            }
        }

        private bool LoadCsv(string path)
        {
            using (var reader = new StreamReader(path))
            {
                var factory = new CsvFactory();
                var csvParser = factory.CreateParser(reader);
                var strArray = csvParser.Read();
                bool first = true;
                int numJoints = 25;
                int startIndex = 4;
                while (strArray != null)
                {
                    if (!first)
                    {
                        var jv = new JointValueVector();
                        for (int i = startIndex; i < numJoints + startIndex; i++)
                        {
                            jv.JointValues.Add(new JointValue { id = i - startIndex, value = double.Parse(strArray[_jointMap[i-startIndex]+startIndex]) });
                        }
                        _jvList.Enqueue(jv);
                    }
                    strArray = csvParser.Read();
                    if (first) first = false;
                }
            }
            return false;
        }

        private void InitZmq()
        {
            if (_ctx == null)
            {
                _ctx = NetMQContext.Create();
                _socket = _ctx.CreatePublisherSocket();
                var address = string.Format("tcp://*:{0}", _port);
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
    }
}
