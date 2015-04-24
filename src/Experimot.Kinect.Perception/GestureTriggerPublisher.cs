using System.Collections.Generic;
using System.IO;
using System.Windows;
using experimot.msgs;
using Microsoft.Kinect;
using Microsoft.Kinect.VisualGestureBuilder;
using ProtoBuf;
using NetMQ;
using Joint = Microsoft.Kinect.Joint;

namespace Experimot.Kinect.Perception
{
    /// <summary>
    /// Interaction logic for MainWindow
    /// </summary>
    public class GestureTriggerPublisher
    {
        private NetMQContext _ctx;
        private NetMQSocket _socket;
        private readonly uint _port;
        private readonly string _topic;
        private bool _noBodyTracked;
        private bool _emptyMsgSent;

        private static GestureTriggerPublisher _publisher;

        public static GestureTriggerPublisher Create(string host, uint port, string topic)
        {
            if (_publisher == null)
            {
                _publisher = new GestureTriggerPublisher(host, port, topic);
            }
            return _publisher;
        }

        public static GestureTriggerPublisher Instance
        {
            get { return _publisher; }
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
            _noBodyTracked = false;
            _emptyMsgSent = false;
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
        //public void UpdateBodyFrame(Body[] bodies)
        //{
        //    if (!CanSend) return;

        //    KinectBodies kbodies = new KinectBodies();
        //    _noBodyTracked = true;
        //    int penIndex = 0;
        //    foreach (var body in bodies)
        //    {
        //        penIndex++;
        //        if (body.IsTracked)
        //        {
        //            _noBodyTracked = false;
        //            _emptyMsgSent = false;

        //            var kbody = new KinectBody
        //            {
        //                IsTracked = true,
        //                TrackingId = penIndex - 1,
        //                JointCount = body.Joints.Count
        //            };

        //            IReadOnlyDictionary<JointType, Joint> joints = body.Joints;

        //            foreach (JointType jointType in joints.Keys)
        //            {
        //                // sometimes the depth(Z) of an inferred joint may show as negative
        //                // clamp down to 0.1f to prevent coordinatemapper from returning (-Infinity, -Infinity)
        //                CameraSpacePoint position = joints[jointType].Position;
        //                if (position.Z < 0)
        //                {
        //                    position.Z = KinectBodyHelper.InferredZPositionClamp;
        //                }

        //                KinectJoint kjoint = new KinectJoint
        //                {
        //                    Type = (KinectJoint.JointType) jointType,
        //                    State = (KinectJoint.TrackingState) joints[jointType].TrackingState,
        //                    Position = new Vector3d {x = position.X, y = position.Y, z = position.Z}
        //                };
        //                var orient = body.JointOrientations[jointType].Orientation;
        //                kjoint.Orientation = new Quaternion
        //                {
        //                    w = orient.W,
        //                    x = orient.X,
        //                    y = orient.Y,
        //                    z = orient.Z
        //                };
        //                kbody.Joints.Add(kjoint);
        //            }
        //            kbodies.Body.Add(kbody);
        //        }
        //        PublishGestureTrigger(kbodies);
        //    }
        //    if (_noBodyTracked && !_emptyMsgSent)
        //    {
        //        PublishGestureTrigger(kbodies, true);
        //        _emptyMsgSent = true;
        //    }
        //}
        private const int SendFrequency = 10;
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

        private bool once = true;
        public void PublishGestureTrigger(GestureTriggers gesture, bool force = false)
        {
            if (gesture != null && gesture.motion.Count > 0 && _socket != null)
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
