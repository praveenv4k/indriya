//------------------------------------------------------------------------------
// <copyright file="GestureDetector.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Diagnostics;
using Experimot.Kinect.GestureRecognition;
using Microsoft.Kinect;
using Microsoft.Kinect.VisualGestureBuilder;

namespace Experimot.Kinect.Perception
{
    /// <summary>
    /// Gesture Detector class which listens for VisualGestureBuilderFrame events from the service
    /// and updates the associated GestureResultView object with the latest results for the 'Seated' gesture
    /// </summary>
    public class GestureDetector : IDisposable
    {
        /// <summary> Path to the gesture database that was trained with VGB </summary>
        //private readonly string gestureDatabase = @"Database\Seated.gbd";
        private readonly List<string> _gesturedbs = new List<string>();

        /// <summary> Name of the discrete gesture in the database that we want to track </summary>
        //private readonly string seatedGestureName = "Seated";
        private readonly List<string> _gestures = new List<string>();

        /// <summary> Gesture frame source which should be tied to a body tracking ID </summary>
        private VisualGestureBuilderFrameSource _vgbFrameSource;

        /// <summary> Gesture frame reader which will handle gesture events coming from the sensor </summary>
        private VisualGestureBuilderFrameReader _vgbFrameReader;

        /// <summary>
        /// Initializes a new instance of the GestureDetector class along with the gesture frame source and reader
        /// </summary>
        /// <param name="kinectSensor">Active sensor to initialize the VisualGestureBuilderFrameSource object with</param>
        /// <param name="gestureResultView">GestureResultView object to store gesture results of a single body to</param>
        public GestureDetector(KinectSensor kinectSensor, GestureResultView gestureResultView)
        {
            try
            {
                if (kinectSensor == null)
                {
                    throw new ArgumentNullException("kinectSensor");
                }

                if (gestureResultView == null)
                {
                    throw new ArgumentNullException("gestureResultView");
                }

                GestureResultView = gestureResultView;

                // create the vgb source. The associated body tracking ID will be set when a valid body frame arrives from the sensor.
                _vgbFrameSource = new VisualGestureBuilderFrameSource(kinectSensor, 0);
                _vgbFrameSource.TrackingIdLost += Source_TrackingIdLost;

                // open the reader for the vgb frames
                _vgbFrameReader = _vgbFrameSource.OpenReader();
                if (_vgbFrameReader != null)
                {
                    _vgbFrameReader.IsPaused = true;
                    _vgbFrameReader.FrameArrived += Reader_GestureFrameArrived;
                }

                _gesturedbs.Add(@"Database\experimot.gbd");

                _gestures.Add(GestureNames.HandwaveLeft);
                _gestures.Add(GestureNames.HandwaveRight);

                foreach (var db in _gesturedbs)
                {
                    using (var database = new VisualGestureBuilderDatabase(db))
                    {
                        foreach (var gesture in database.AvailableGestures)
                        {
                            _vgbFrameSource.AddGesture(gesture);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
            }
        }

        /// <summary> Gets the GestureResultView object which stores the detector results for display in the UI </summary>
        public GestureResultView GestureResultView { get; private set; }

        /// <summary>
        /// Gets or sets the body tracking ID associated with the current detector
        /// The tracking ID can change whenever a body comes in/out of scope
        /// </summary>
        public ulong TrackingId
        {
            get
            {
                return _vgbFrameSource.TrackingId;
            }

            set
            {
                if (_vgbFrameSource.TrackingId != value)
                {
                    _vgbFrameSource.TrackingId = value;
                }
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether or not the detector is currently paused
        /// If the body tracking ID associated with the detector is not valid, then the detector should be paused
        /// </summary>
        public bool IsPaused
        {
            get
            {
                return _vgbFrameReader.IsPaused;
            }

            set
            {
                if (_vgbFrameReader.IsPaused != value)
                {
                    _vgbFrameReader.IsPaused = value;
                }
            }
        }

        /// <summary>
        /// Disposes all unmanaged resources for the class
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Disposes the VisualGestureBuilderFrameSource and VisualGestureBuilderFrameReader objects
        /// </summary>
        /// <param name="disposing">True if Dispose was called directly, false if the GC handles the disposing</param>
        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (_vgbFrameReader != null)
                {
                    _vgbFrameReader.FrameArrived -= Reader_GestureFrameArrived;
                    _vgbFrameReader.Dispose();
                    _vgbFrameReader = null;
                }

                if (_vgbFrameSource != null)
                {
                    _vgbFrameSource.TrackingIdLost -= Source_TrackingIdLost;
                    _vgbFrameSource.Dispose();
                    _vgbFrameSource = null;
                }
            }
        }

        /// <summary>
        /// Handles gesture detection results arriving from the sensor for the associated body tracking Id
        /// </summary>
        /// <param name="sender">object sending the event</param>
        /// <param name="e">event arguments</param>
        private void Reader_GestureFrameArrived(object sender, VisualGestureBuilderFrameArrivedEventArgs e)
        {
            VisualGestureBuilderFrameReference frameReference = e.FrameReference;
            using (VisualGestureBuilderFrame frame = frameReference.AcquireFrame())
            {
                if (frame != null)
                {
                    // get the discrete gesture results which arrived with the latest frame
                    IReadOnlyDictionary<Gesture, DiscreteGestureResult> discreteResults = frame.DiscreteGestureResults;
                    Gesture detectedGesture = null;
                    DiscreteGestureResult detectedResult = null;
                    if (discreteResults != null)
                    {
                        // we only have one gesture in this source object, but you can get multiple gestures
                        foreach (Gesture gesture in _vgbFrameSource.Gestures)
                        {
                            //System.Diagnostics.Debug.WriteLine(gesture.Name);
                            if (gesture.GestureType == GestureType.Discrete && _gestures.Contains(gesture.Name))
                            //if (gesture.Name.Equals(this.seatedGestureName) && gesture.GestureType == GestureType.Discrete)
                            {

                                DiscreteGestureResult result;
                                discreteResults.TryGetValue(gesture, out result);

                                //if (result != null && result.Detected)
                                if (result != null)
                                {
                                    if (result.Detected)
                                    {
                                        detectedGesture = gesture;
                                        detectedResult = result;
                                        break;
                                    }
                                    // update the GestureResultView object with new gesture result values
                                    //this.GestureResultView.UpdateGestureResult(true, result.Detected, result.Confidence, gesture.Name);
                                }
                            }
                        }
                    }
                    if (detectedGesture != null)
                    {
                        GestureResultView.UpdateGestureResult(true, detectedResult.Detected, detectedResult.Confidence, detectedGesture.Name);
                    }
                    else
                    {
                        GestureResultView.UpdateGestureResult(true, false, 0.0f, string.Empty);
                    }
                }
            }
        }

        /// <summary>
        /// Handles the TrackingIdLost event for the VisualGestureBuilderSource object
        /// </summary>
        /// <param name="sender">object sending the event</param>
        /// <param name="e">event arguments</param>
        private void Source_TrackingIdLost(object sender, TrackingIdLostEventArgs e)
        {
            // update the GestureResultView object to show the 'Not Tracked' image in the UI
            GestureResultView.UpdateGestureResult(false, false, 0.0f, string.Empty);
        }
    }
}
