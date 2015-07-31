//------------------------------------------------------------------------------
// <copyright file="GestureDetector.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using Common.Logging;
using Indriya.Core.Msgs;
using Microsoft.Kinect;
using Microsoft.Kinect.VisualGestureBuilder;

namespace Indriya.Kinect.Perception
{
    /// <summary>
    /// Gesture Detector class which listens for VisualGestureBuilderFrame events from the service
    /// and updates the associated GestureResultView object with the latest results for the 'Seated' gesture
    /// </summary>
    public class GestureDetector : IDisposable
    {
        /// <summary> Name of the discrete gesture in the database that we want to track </summary>
        //private readonly string seatedGestureName = "Seated";
        private readonly List<string> _gestures = new List<string>();

        /// <summary> Gesture frame source which should be tied to a body tracking ID </summary>
        private VisualGestureBuilderFrameSource _vgbFrameSource;

        /// <summary> Gesture frame reader which will handle gesture events coming from the sensor </summary>
        private VisualGestureBuilderFrameReader _vgbFrameReader;

        private static readonly ILog Log = LogManager.GetLogger(typeof (GestureDetector)); 

        /// <summary>
        /// Initializes a new instance of the GestureDetector class along with the gesture frame source and reader
        /// </summary>
        /// <param name="kinectSensor">Active sensor to initialize the VisualGestureBuilderFrameSource object with</param>
        /// <param name="gestureResultView">GestureResultView object to store gesture results of a single body to</param>
        /// <param name="database"></param>
        public GestureDetector(KinectSensor kinectSensor, GestureResultView gestureResultView, GestureDatabase database)
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

                if (database != null)
                {
                    _gestures.AddRange(database.GestureNames);
                    foreach (var gesture in database.Gestures)
                    {
                        _vgbFrameSource.AddGesture(gesture);
                        //_vgbFrameSource.SetIsEnabled(gesture, true);
                    }
                }
            }
            catch (Exception ex)
            {
                Log.Warn(ex.Message);
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
                        // Publish the discrete results
                        PublishDiscreteGestureResult(discreteResults);

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

        private void PublishDiscreteGestureResult(IReadOnlyDictionary<Gesture, DiscreteGestureResult> discreteResults)
        {
            try
            {
                if (discreteResults != null && _vgbFrameSource != null && _vgbFrameSource.Gestures != null &&
                    _vgbFrameSource.Gestures.Count > 0 && GestureResultView != null)
                {
                    GestureTriggers triggers = new GestureTriggers {id = GestureResultView.BodyIndex};
                    //GestureTriggers triggers = new GestureTriggers { id = (int)TrackingId };
                    Log.InfoFormat("Publishing gesture results for body: {0}", GestureResultView.BodyIndex);
                    // For publishing

#if ORIGINAL
                    foreach (Gesture gesture in _vgbFrameSource.Gestures)
                    {
                        //System.Diagnostics.Debug.WriteLine(gesture.Name);
                        if (gesture.GestureType == GestureType.Discrete && _gestures.Contains(gesture.Name))
                            //if (gesture.GestureType == GestureType.Discrete)
                            //if (gesture.Name.Equals(this.seatedGestureName) && gesture.GestureType == GestureType.Discrete)
                        {
                            //if (gesture.Name != GestureNames.HandwaveRight)
                            //{
                            //    continue;
                            //}
                            DiscreteGestureResult result;
                            discreteResults.TryGetValue(gesture, out result);
                            var trigger = new GestureDescription
                            {
                                name = gesture.Name,
                                progress = 0,
                                type = (GestureDescription.GestureType) gesture.GestureType,
                                active = result != null && result.Detected,
                                confidence = result != null ? (int) (result.Confidence*100.00) : 0
                            };
                            triggers.motion.Add(trigger);
                        }
                    }
#else
                    foreach (var discreteResult in discreteResults)
                    {
                        var gesture = discreteResult.Key;
                        var result = discreteResult.Value;
                        var trigger = new GestureDescription
                        {
                            name = gesture.Name,
                            progress = 0,
                            type = (GestureDescription.GestureType)gesture.GestureType,
                            active = result != null && result.Detected,
                            confidence = result != null ? (int)(result.Confidence * 100.00) : 0
                        };
                        triggers.motion.Add(trigger);
                    }
#endif

                    GestureTriggerPublisher.Instance.PublishGestureTrigger(triggers);

                }
            }
            catch (Exception ex)
            {
                Log.ErrorFormat("Exception occured while publishing gesture data: {0}", ex.Message);
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
