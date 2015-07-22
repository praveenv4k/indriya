using KinectJoint = experimot.msgs.KinectJoint;
using KinectBody = experimot.msgs.KinectBody;
using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Media.Media3D;
using experimot.msgs;
using Microsoft.Kinect;
using NetMQ;
using ProtoBuf;
using Quaternion = experimot.msgs.Quaternion;
#if USE_KINECT_BODIES
#else
using KinectEx;
using KinectEx.Smoothing;
#endif

namespace Experimot.Kinect.Perception
{
    /// <summary>
    /// Interaction logic for MainWindow
    /// </summary>
    public class KinectBodyPublisher
    {
        private NetMQContext _ctx;
        private NetMQSocket _socket;
        private readonly uint _port;
        private readonly string _topic;
        //private bool _noBodyTracked;
        //private int _emptyMsgSent;

        /// <summary>
        /// Initializes a new instance of the MainWindow class.
        /// </summary>
        public KinectBodyPublisher()
            : this("tcp://*", 5570, "KSP")
        {
        }

        /// <summary>
        /// Initializes a new instance of the MainWindow class.
        /// </summary>
        public KinectBodyPublisher(string host, uint port, string topic)
        {
            _host = host;
            _port = port;
            _topic = topic;
            //_noBodyTracked = false;
            //_emptyMsgSent = 0;
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
        /// <param name="bodies"></param>
        /// <param name="humanPose"></param>
        /// <param name="naoJoints"></param>
#if USE_KINECT_BODIES
        public void UpdateBodyFrame(Body[] bodies, HumanPosePublisher humanPose)
#else
        public void UpdateBodyFrame(SmoothedBodyList<ExponentialSmoother> bodies, HumanPosePublisher humanPose, NaoJointPublisher naoJoints)
#endif
        {
            if (!CanSend) return;

            KinectBodies kbodies = new KinectBodies();
            ParamList list = null;
            var humans = new Humans();
            //_noBodyTracked = true;
            int penIndex = 0;
            foreach (var body in bodies)
            {
                penIndex++;

                var human = new Human {tracked = body.IsTracked};
                var jointPosDict = new Dictionary<JointType, Vector3D>();
                human.id = penIndex-1;

                if (body.IsTracked)
                {
                    //_noBodyTracked = false;
                    //_emptyMsgSent = 0;

                    if (naoJoints != null)
                    {
                        list = naoJoints.GetJointValues(body);
                        if (list.param.Count > 0)
                        {
                            naoJoints.Update(list);
                        }
                    }

                    var kbody = new KinectBody
                    {
                        IsTracked = true,
                        TrackingId = penIndex - 1,
                        JointCount = body.Joints.Count
                    };

                    var joints = body.Joints;

                    foreach (JointType jointType in joints.Keys)
                    {
                        // sometimes the depth(Z) of an inferred joint may show as negative
                        // clamp down to 0.1f to prevent coordinatemapper from returning (-Infinity, -Infinity)
                        CameraSpacePoint position = joints[jointType].Position;
                        if (position.Z < 0)
                        {
                            position.Z = KinectBodyHelper.InferredZPositionClamp;
                        }

                        var vector3 = new Vector3d {x = position.X, y = position.Y, z = position.Z};
                        KinectJoint kjoint = new KinectJoint
                        {
                            Type = (KinectJoint.JointType) jointType,
                            State = (KinectJoint.TrackingState) joints[jointType].TrackingState,
                            Position = vector3
                        };
                        var orient = body.JointOrientations[jointType].Orientation;
                        kjoint.Orientation = new Quaternion
                        {
                            w = orient.W,
                            x = orient.X,
                            y = orient.Y,
                            z = orient.Z
                        };
#if USE_KINECT_BODIES
#else
                        kjoint.Angle = (float) body.GetAngleAt(jointType);
#endif
                        kbody.Joints.Add(kjoint);

                        if (jointType == JointType.SpineBase || jointType == JointType.ShoulderLeft ||
                            jointType == JointType.ShoulderRight || jointType == JointType.Head ||
                            jointType == JointType.SpineShoulder)
                        {
                            if (jointType == JointType.Head)
                            {
                                human.head_position = vector3;
                            }
                            if (jointType == JointType.SpineBase)
                            {
                                human.torso_position = vector3;
                            }
                            jointPosDict.Add(jointType, new Vector3D(position.X, position.Y, position.Z));
                        }
                    }

                    if (jointPosDict.ContainsKey(JointType.SpineBase) &&
                        jointPosDict.ContainsKey(JointType.ShoulderLeft) &&
                        jointPosDict.ContainsKey(JointType.ShoulderRight) && jointPosDict.ContainsKey(JointType.Head) &&
                        jointPosDict.ContainsKey(JointType.SpineShoulder))
                    {
#if USE_Z_FRONT
                        var tri = new Triangle(jointPosDict[JointType.SpineBase], jointPosDict[JointType.ShoulderLeft],
                            jointPosDict[JointType.ShoulderRight]);
                        var zAxis = tri.Normal(); // Z Axis
                        var midPt = jointPosDict[JointType.SpineShoulder];
                        var yAxis = (midPt - jointPosDict[JointType.SpineBase]);
                        yAxis.Normalize();
                        var xAxis = Vector3D.CrossProduct(yAxis, zAxis);
                        xAxis.Normalize();

                        human.orientation = ToQuaternion(xAxis, yAxis, zAxis);
#else
                        var tri = new Triangle(jointPosDict[JointType.SpineBase], jointPosDict[JointType.ShoulderLeft],
                            jointPosDict[JointType.ShoulderRight]);
                        var xAxis = tri.Normal(); // Z Axis
                        var midPt = jointPosDict[JointType.SpineShoulder];
                        var zAxis = (midPt - jointPosDict[JointType.SpineBase]);
                        zAxis.Normalize();
                        var yAxis = Vector3D.CrossProduct(zAxis, xAxis);
                        yAxis.Normalize();

                        //human.orientation = ToQuaternion(xAxis, yAxis, zAxis);
                        //var spineBase = jointPosDict[JointType.SpineBase];
                        //var tri = new Triangle(spineBase, jointPosDict[JointType.ShoulderLeft],
                        //    jointPosDict[JointType.ShoulderRight]);
                        //var xAxis = tri.Normal(); // Z Axis
                        //var zAxis = spineBase + new Vector3D(spineBase.X, spineBase.Y, spineBase.Z + 0.5);
                        //zAxis.Normalize();
                        
                        //var yAxis = Vector3D.CrossProduct(zAxis, xAxis);
                        //yAxis.Normalize();

                        human.orientation = ToQuaternion(xAxis, yAxis, zAxis);
#endif
                    }
                    else
                    {
                        human.orientation = new Quaternion {w = 1, x = 0, y = 0, z = 0};
                    }
                    kbodies.Body.Add(kbody);
                    humans.human.Add(human);
                }
                if (humanPose != null)
                {
                    humanPose.Update(humans);
                }
                //PublishKinectBodies(kbodies);
            }
            PublishKinectBodies(kbodies);
            //if (_noBodyTracked && _emptyMsgSent < 5)
            //{
            //    PublishKinectBodies(kbodies, true);
            //    _emptyMsgSent++;
            //}
        }

        private Quaternion ToQuaternion(Vector3D xAxis, Vector3D yAxis, Vector3D zAxis)
        {
            double m00 = xAxis.X;
            double m01 = yAxis.X;
            double m02 = zAxis.X;

            double m10 = xAxis.Y;
            double m11 = yAxis.Y;
            double m12 = zAxis.Y;

            double m20 = xAxis.Z;
            double m21 = yAxis.Z;
            double m22 = zAxis.Z;

            //double m00 = xAxis.X;
            //double m01 = xAxis.Y;
            //double m02 = xAxis.Z;

            //double m10 = yAxis.X;
            //double m11 = yAxis.Y;
            //double m12 = yAxis.Z;

            //double m20 = zAxis.X;
            //double m21 = zAxis.Y;
            //double m22 = zAxis.Z;


            double qw = Math.Sqrt(0.5*(1 + m00 + m11 + m22));
            double qx = (m21 - m12)/(4*qw);
            double qy = (m02 - m20)/(4*qw);
            double qz = (m10 - m01)/(4*qw);

            System.Windows.Media.Media3D.Quaternion quat = new System.Windows.Media.Media3D.Quaternion(qx, qy, qz, qw);
            quat.Normalize();
            return new Quaternion {w = quat.W, x = quat.X, y = quat.Y, z = quat.Z};
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

        private void PublishKinectBodies(KinectBodies kbodies, bool force = true)
        {
            if (kbodies != null && _socket != null)
            //if (kbodies != null && _socket != null)
            {
                if (force || kbodies.Body.Count > 0)
                {
                    _socket.SendMore(_topic);

                    using (var ms = new MemoryStream())
                    {
                        Serializer.Serialize(ms, kbodies);
                        _socket.Send(ms.GetBuffer(), (int)ms.Length);
                    }
                }
            }

        }
    }
}
