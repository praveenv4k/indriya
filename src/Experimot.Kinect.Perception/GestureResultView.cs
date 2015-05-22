//------------------------------------------------------------------------------
// <copyright file="GestureResultView.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Microsoft.Kinect;

namespace Experimot.Kinect.Perception
{
    /// <summary>
    /// Stores discrete gesture results for the GestureDetector.
    /// Properties are stored/updated for display in the UI.
    /// </summary>
    public sealed class GestureResultView : INotifyPropertyChanged
    {
        /// <summary> Image to show when the 'detected' property is true for a tracked body </summary>
        //private readonly ImageSource seatedImage = new BitmapImage(new Uri(@"Images\Seated.png", UriKind.Relative));
        private readonly ImageSource _handwaveLeft = new BitmapImage(new Uri(@"Images\Handwave_Left.png", UriKind.Relative));
        private readonly ImageSource _handwaveRight = new BitmapImage(new Uri(@"Images\Handwave_Right.png", UriKind.Relative));

        private readonly Dictionary<string, ImageSource> _gestureImageDict = new Dictionary<string, ImageSource>();

        /// <summary> Image to show when the 'detected' property is false for a tracked body </summary>
        //private readonly ImageSource notSeatedImage = new BitmapImage(new Uri(@"Images\NotSeated.png", UriKind.Relative));
        private readonly ImageSource _handwaveNone = new BitmapImage(new Uri(@"Images\Handwave_None.png", UriKind.Relative));

        /// <summary> Image to show when the body associated with the GestureResultView object is not being tracked </summary>
        private readonly ImageSource _notTrackedImage = new BitmapImage(new Uri(@"Images\NotTracked.png", UriKind.Relative));

        /// <summary> Array of brush colors to use for a tracked body; array position corresponds to the body colors used in the KinectBodyView class </summary>
        private readonly Brush[] _trackedColors = { Brushes.Red, Brushes.Orange, Brushes.Green, Brushes.Blue, Brushes.Indigo, Brushes.Violet };

        /// <summary> Brush color to use as background in the UI </summary>
        private Brush _bodyColor = Brushes.Gray;

        /// <summary> The body index (0-5) associated with the current gesture detector </summary>
        private int _bodyIndex;

        /// <summary> Current confidence value reported by the discrete gesture </summary>
        private float _confidence;

        /// <summary> True, if the discrete gesture is currently being detected </summary>
        private string _detected = GestureNames.None;

        /// <summary> Image to display in UI which corresponds to tracking/detection state </summary>
        private ImageSource _imageSource;
        
        /// <summary> True, if the body is currently being tracked </summary>
        private bool _isTracked;

        /// <summary>
        /// Initializes a new instance of the GestureResultView class and sets initial property values
        /// </summary>
        /// <param name="bodyIndex">Body Index associated with the current gesture detector</param>
        /// <param name="isTracked">True, if the body is currently tracked</param>
        /// <param name="detected">True, if the gesture is currently detected for the associated body</param>
        /// <param name="confidence">Confidence value for detection of the 'Seated' gesture</param>
        public GestureResultView(int bodyIndex, bool isTracked, bool detected, float confidence)
        {
            BodyIndex = bodyIndex;
            IsTracked = isTracked;
            Detected = detected ? string.Empty : GestureNames.None;
            Confidence = confidence;
            ImageSource = _notTrackedImage;

            _gestureImageDict.Add(GestureNames.None, _handwaveNone);
            _gestureImageDict.Add(GestureNames.HandwaveLeft, _handwaveLeft);
            _gestureImageDict.Add(GestureNames.HandwaveRight, _handwaveRight);
        }

        /// <summary>
        /// INotifyPropertyChangedPropertyChanged event to allow window controls to bind to changeable data
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary> 
        /// Gets the body index associated with the current gesture detector result 
        /// </summary>
        public int BodyIndex
        {
            get
            {
                return _bodyIndex;
            }

            private set
            {
                if (_bodyIndex != value)
                {
                    _bodyIndex = value;
                    NotifyPropertyChanged();
                }
            }
        }

        /// <summary> 
        /// Gets the body color corresponding to the body index for the result
        /// </summary>
        public Brush BodyColor
        {
            get
            {
                return _bodyColor;
            }

            private set
            {
                if (!Equals(_bodyColor, value))
                {
                    _bodyColor = value;
                    NotifyPropertyChanged();
                }
            }
        }

        /// <summary> 
        /// Gets a value indicating whether or not the body associated with the gesture detector is currently being tracked 
        /// </summary>
        public bool IsTracked 
        {
            get
            {
                return _isTracked;
            }

            private set
            {
                if (IsTracked != value)
                {
                    _isTracked = value;
                    NotifyPropertyChanged();
                }
            }
        }

        /// <summary> 
        /// Gets a value indicating whether or not the discrete gesture has been detected
        /// </summary>
        public string Detected 
        {
            get
            {
                return _detected;
            }

            private set
            {
                if (_detected != value)
                {
                    _detected = value;
                    NotifyPropertyChanged();
                }
            }
        }

        /// <summary> 
        /// Gets a float value which indicates the detector's confidence that the gesture is occurring for the associated body 
        /// </summary>
        public float Confidence
        {
            get
            {
                return _confidence;
            }

            private set
            {
                if (Math.Abs(_confidence - value) > 1e-6)
                {
                    _confidence = value;
                    NotifyPropertyChanged();
                }
            }
        }

        /// <summary> 
        /// Gets an image for display in the UI which represents the current gesture result for the associated body 
        /// </summary>
        public ImageSource ImageSource
        {
            get
            {
                return _imageSource;
            }

            private set
            {
                if (!Equals(ImageSource, value))
                {
                    _imageSource = value;
                    NotifyPropertyChanged();
                }
            }
        }

        private CameraSpacePoint _position;
        public CameraSpacePoint Position
        {
            get
            {
                return _position;
            }
            set
            {
                if (_position != value)
                {
                    _position = value;
                    NotifyPropertyChanged();
                }
            }
        }

        private Vector4 _orientation;
        public Vector4 Orientation
        {
            get
            {
                return _orientation;
            }
            set
            {
                if (_orientation != value)
                {
                    _orientation = value;
                    NotifyPropertyChanged();
                }
            }
        }

        /// <summary>
        /// Updates the values associated with the discrete gesture detection result
        /// </summary>
        /// <param name="isBodyTrackingIdValid">True, if the body associated with the GestureResultView object is still being tracked</param>
        /// <param name="isGestureDetected">True, if the discrete gesture is currently detected for the associated body</param>
        /// <param name="detectionConfidence">Confidence value for detection of the discrete gesture</param>
        /// <param name="gestureKey">Gesture unique identifier</param>
        public void UpdateGestureResult(bool isBodyTrackingIdValid, bool isGestureDetected, float detectionConfidence,
            string gestureKey)
        {
            try
            {
                IsTracked = isBodyTrackingIdValid;
                Confidence = 0.0f;

                if (!IsTracked)
                {
                    ImageSource = _notTrackedImage;
                    Detected = GestureNames.None;
                    BodyColor = Brushes.Gray;
                }
                else
                {
                    BodyColor = _trackedColors[BodyIndex];

                    if (isGestureDetected)
                    {
                        Detected = gestureKey;
                        Confidence = detectionConfidence;
                        ImageSource = _gestureImageDict[gestureKey];
                    }
                    else
                    {
                        Detected = GestureNames.None;
                        ImageSource = _gestureImageDict[GestureNames.None];
                    }
                }
                //var gestMsg = new experimot.msgs.GestureTrigger()
                //{
                //    id = BodyIndex,
                //    motion = new GestureDescription()
                //    {
                //        active = isGestureDetected,
                //        confidence = (int) detectionConfidence*100,
                //        name = gestureKey,
                //        progress = 0,
                //        type = GestureDescription.GestureType.Discrete
                //    }
                //};
                //GestureTriggerPublisher.Instance.PublishGestureTrigger(gestMsg);
            }
            catch (Exception ex)
            {
                MessageBox.Show(string.Format("{0}: {1}", ex.Message, ex.StackTrace));
            }
        }

        /// <summary>
        /// Notifies UI that a property has changed
        /// </summary>
        /// <param name="propertyName">Name of property that has changed</param> 
        private void NotifyPropertyChanged([CallerMemberName] string propertyName = "")
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }
    }
}
