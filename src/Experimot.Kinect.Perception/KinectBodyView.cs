//------------------------------------------------------------------------------
// <copyright file="KinectBodyView.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Windows;
using System.Windows.Media;
using Microsoft.Kinect;

namespace Experimot.Kinect.Perception
{
    /// <summary>
    /// Visualizes the Kinect Body stream for display in the UI
    /// </summary>
    public sealed class KinectBodyView
    {
        /// <summary>
        /// Drawing group for body rendering output
        /// </summary>
        private readonly DrawingGroup _drawingGroup;

        /// <summary>
        /// Drawing image that we will display
        /// </summary>
        private readonly DrawingImage _imageSource;

        /// <summary>
        /// Coordinate mapper to map one type of point to another
        /// </summary>
        private readonly CoordinateMapper _coordinateMapper;

        /// <summary>
        /// Width of display (depth space)
        /// </summary>
        private readonly int _displayWidth;

        /// <summary>
        /// Height of display (depth space)
        /// </summary>
        private readonly int _displayHeight;


        /// <summary>
        /// Initializes a new instance of the KinectBodyView class
        /// </summary>
        /// <param name="kinectSensor">Active instance of the KinectSensor</param>
        public KinectBodyView(KinectSensor kinectSensor)
        {
            if (kinectSensor == null)
            {
                throw new ArgumentNullException("kinectSensor");
            }

            // get the coordinate mapper
            _coordinateMapper = kinectSensor.CoordinateMapper;

            // get the depth (display) extents
            FrameDescription frameDescription = kinectSensor.DepthFrameSource.FrameDescription;

            // get size of joint space
            _displayWidth = frameDescription.Width;
            _displayHeight = frameDescription.Height;



            // Create the drawing group we'll use for drawing
            _drawingGroup = new DrawingGroup();

            // Create an image source that we can use in our image control
            _imageSource = new DrawingImage(_drawingGroup);
        }

        /// <summary>
        /// Gets the bitmap to display
        /// </summary>
        public ImageSource ImageSource
        {
            get { return _imageSource; }
        }

        //private bool serialize = false;


        //private void Serialize(Body[] bodies)
        //{
        //    try
        //    {
        //        if (bodies != null && bodies.Length > 0)
        //        {
        //            using (var memorystream = new MemoryStream())
        //            {
        //                BinaryFormatter bf = new BinaryFormatter();
        //                bf.Serialize(memorystream, bodies);

        //                Console.WriteLine("Number of Bytes: {0}", memorystream.GetBuffer().Length);
        //            }
        //        }
        //    }
        //    catch (Exception ex)
        //    {
        //        Console.WriteLine(ex.Message);
        //    }
        //}

        /// <summary>
        /// Updates the body array with new information from the sensor
        /// Should be called whenever a new BodyFrameArrivedEvent occurs
        /// </summary>
        /// <param name="bodies">Array of bodies to update</param>
        public void UpdateBodyFrame(Body[] bodies)
        {
            if (bodies != null)
            {
                //if (!serialize)
                //{
                //    Serialize(bodies);
                //    serialize = true;
                //}

                using (DrawingContext dc = _drawingGroup.Open())
                {
                    // Draw a transparent background to set the render size
                    dc.DrawRectangle(Brushes.Black, null, new Rect(0.0, 0.0, _displayWidth, _displayHeight));

                    int penIndex = 0;
                    foreach (Body body in bodies)
                    {
                        Pen drawPen = KinectBodyHelper.Instance.BodyColors[penIndex++];

                        if (body.IsTracked)
                        {
                            DrawClippedEdges(body, dc);

                            IReadOnlyDictionary<JointType, Joint> joints = body.Joints;

                            // convert the joint points to depth (display) space
                            Dictionary<JointType, Point> jointPoints = new Dictionary<JointType, Point>();

                            foreach (JointType jointType in joints.Keys)
                            {
                                // sometimes the depth(Z) of an inferred joint may show as negative
                                // clamp down to 0.1f to prevent coordinatemapper from returning (-Infinity, -Infinity)
                                CameraSpacePoint position = joints[jointType].Position;
                                if (position.Z < 0)
                                {
                                    position.Z = KinectBodyHelper.InferredZPositionClamp;
                                }

                                DepthSpacePoint depthSpacePoint = _coordinateMapper.MapCameraPointToDepthSpace(position);
                                jointPoints[jointType] = new Point(depthSpacePoint.X, depthSpacePoint.Y);
                            }

                            DrawBody(joints, jointPoints, dc, drawPen);

                            DrawHand(body.HandLeftState, jointPoints[JointType.HandLeft], dc);
                            DrawHand(body.HandRightState, jointPoints[JointType.HandRight], dc);
                        }
                    }

                    // prevent drawing outside of our render area
                    _drawingGroup.ClipGeometry = new RectangleGeometry(new Rect(0.0, 0.0, _displayWidth, _displayHeight));
                }
            }
        }

        /// <summary>
        /// Draws a body
        /// </summary>
        /// <param name="joints">joints to draw</param>
        /// <param name="jointPoints">translated positions of joints to draw</param>
        /// <param name="drawingContext">drawing context to draw to</param>
        /// <param name="drawingPen">specifies color to draw a specific body</param>
        private void DrawBody(IReadOnlyDictionary<JointType, Joint> joints, IDictionary<JointType, Point> jointPoints,
            DrawingContext drawingContext, Pen drawingPen)
        {
            // Draw the bones
            foreach (var bone in KinectBodyHelper.Instance.Bones)
            {
                DrawBone(joints, jointPoints, bone.Item1, bone.Item2, drawingContext, drawingPen);
            }

            // Draw the joints
            foreach (JointType jointType in joints.Keys)
            {
                Brush drawBrush = null;

                TrackingState trackingState = joints[jointType].TrackingState;

                if (trackingState == TrackingState.Tracked)
                {
                    drawBrush = KinectBodyHelper.Instance.TrackedJointBrush;
                }
                else if (trackingState == TrackingState.Inferred)
                {
                    drawBrush = KinectBodyHelper.Instance.InferredJointBrush;
                }

                if (drawBrush != null)
                {
                    drawingContext.DrawEllipse(drawBrush, null, jointPoints[jointType], KinectBodyHelper.JointThickness,
                        KinectBodyHelper.JointThickness);
                }
            }
        }

        /// <summary>
        /// Draws one bone of a body (joint to joint)
        /// </summary>
        /// <param name="joints">joints to draw</param>
        /// <param name="jointPoints">translated positions of joints to draw</param>
        /// <param name="jointType0">first joint of bone to draw</param>
        /// <param name="jointType1">second joint of bone to draw</param>
        /// <param name="drawingContext">drawing context to draw to</param>
        /// /// <param name="drawingPen">specifies color to draw a specific bone</param>
        private void DrawBone(IReadOnlyDictionary<JointType, Joint> joints, IDictionary<JointType, Point> jointPoints,
            JointType jointType0, JointType jointType1, DrawingContext drawingContext, Pen drawingPen)
        {
            Joint joint0 = joints[jointType0];
            Joint joint1 = joints[jointType1];

            // If we can't find either of these joints, exit
            if (joint0.TrackingState == TrackingState.NotTracked ||
                joint1.TrackingState == TrackingState.NotTracked)
            {
                return;
            }

            // We assume all drawn bones are inferred unless BOTH joints are tracked
            Pen drawPen = KinectBodyHelper.Instance.InferredBonePen;
            if ((joint0.TrackingState == TrackingState.Tracked) && (joint1.TrackingState == TrackingState.Tracked))
            {
                drawPen = drawingPen;
            }

            drawingContext.DrawLine(drawPen, jointPoints[jointType0], jointPoints[jointType1]);
        }

        /// <summary>
        /// Draws a hand symbol if the hand is tracked: red circle = closed, green circle = opened; blue circle = lasso
        /// </summary>
        /// <param name="handState">state of the hand</param>
        /// <param name="handPosition">position of the hand</param>
        /// <param name="drawingContext">drawing context to draw to</param>
        private void DrawHand(HandState handState, Point handPosition, DrawingContext drawingContext)
        {
            switch (handState)
            {
                case HandState.Closed:
                    drawingContext.DrawEllipse(KinectBodyHelper.Instance.HandClosedBrush, null, handPosition,
                        KinectBodyHelper.HandSize, KinectBodyHelper.HandSize);
                    break;

                case HandState.Open:
                    drawingContext.DrawEllipse(KinectBodyHelper.Instance.HandOpenBrush, null, handPosition,
                        KinectBodyHelper.HandSize, KinectBodyHelper.HandSize);
                    break;

                case HandState.Lasso:
                    drawingContext.DrawEllipse(KinectBodyHelper.Instance.HandLassoBrush, null, handPosition,
                        KinectBodyHelper.HandSize, KinectBodyHelper.HandSize);
                    break;
            }
        }

        /// <summary>
        /// Draws indicators to show which edges are clipping body data
        /// </summary>
        /// <param name="body">body to draw clipping information for</param>
        /// <param name="drawingContext">drawing context to draw to</param>
        private void DrawClippedEdges(Body body, DrawingContext drawingContext)
        {
            FrameEdges clippedEdges = body.ClippedEdges;

            if (clippedEdges.HasFlag(FrameEdges.Bottom))
            {
                drawingContext.DrawRectangle(
                    Brushes.Red,
                    null,
                    new Rect(0, _displayHeight - KinectBodyHelper.ClipBoundsThickness, _displayWidth,
                        KinectBodyHelper.ClipBoundsThickness));
            }

            if (clippedEdges.HasFlag(FrameEdges.Top))
            {
                drawingContext.DrawRectangle(
                    Brushes.Red,
                    null,
                    new Rect(0, 0, _displayWidth, KinectBodyHelper.ClipBoundsThickness));
            }

            if (clippedEdges.HasFlag(FrameEdges.Left))
            {
                drawingContext.DrawRectangle(
                    Brushes.Red,
                    null,
                    new Rect(0, 0, KinectBodyHelper.ClipBoundsThickness, _displayHeight));
            }

            if (clippedEdges.HasFlag(FrameEdges.Right))
            {
                drawingContext.DrawRectangle(
                    Brushes.Red,
                    null,
                    new Rect(_displayWidth - KinectBodyHelper.ClipBoundsThickness, 0,
                        KinectBodyHelper.ClipBoundsThickness, _displayHeight));
            }
        }
    }
}
