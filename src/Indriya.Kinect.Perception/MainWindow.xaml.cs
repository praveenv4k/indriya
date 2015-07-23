//---------------------------------------------------------------------------------------------------
// <copyright file="MainWindow.xaml.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//
// <Description>
// This program tracks up to 6 people simultaneously.
// If a person is tracked, the associated gesture detector will determine if that person is seated or not.
// If any of the 6 positions are not in use, the corresponding gesture detector(s) will be paused
// and the 'Not Tracked' image will be displayed in the UI.
// </Description>
//----------------------------------------------------------------------------------------------------

using System.Collections.Generic;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using Common.Logging;
using Microsoft.Kinect;
using Indriya.Core.Util;
using System;
#if USE_KINECT_BODIES
#else
using KinectEx;
using KinectEx.Smoothing;
#endif

namespace Indriya.Kinect.Perception
{
    /// <summary>
    /// Interaction logic for the MainWindow
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        /// <summary> Active Kinect sensor </summary>
        private KinectSensor _kinectSensor;
        
        /// <summary> Array for the bodies (Kinect will track up to 6 people simultaneously) </summary>
#if USE_KINECT_BODIES
        private Body[] _bodies;
#else
        private SmoothedBodyList<ExponentialSmoother> _bodies; 
#endif
        /// <summary> Reader for body frames </summary>
        private BodyFrameReader _bodyFrameReader;

        /// <summary> Current status text to display </summary>
        private string _statusText;

        /// <summary> KinectBodyView object which handles drawing the Kinect bodies to a View box in the UI </summary>
        private readonly KinectBodyView _kinectBodyView;
        
        /// <summary> List of gesture detectors, there will be one detector created for each potential body (max of 6) </summary>
        private List<GestureDetector> _gestureDetectorList;

        //private readonly Node _node;
        private KinectBodyPublisher _kBodyPub;
        private readonly ILog _log = LogManager.GetLogger<MainWindow>();
        private GestureTriggerPublisher _gestPub;
        private HumanPosePublisher _humanPub;
        private readonly NaoJointPublisher _naoJoints;
        private readonly GestureDatabase _database;
        /// <summary>
        /// Initializes a new instance of the MainWindow class
        /// </summary>
        public MainWindow()
        {
            // only one sensor is currently supported
            _kinectSensor = KinectSensor.GetDefault();

            // set IsAvailableChanged event notifier
            _kinectSensor.IsAvailableChanged += Sensor_IsAvailableChanged;

            // open the sensor
            _kinectSensor.Open();

            // set the status text
            StatusText = _kinectSensor.IsAvailable
                ? Indriya.Kinect.Perception.Properties.Resources.RunningStatusText
                : Indriya.Kinect.Perception.Properties.Resources.NoSensorStatusText;

            // open the reader for the body frames
            _bodyFrameReader = _kinectSensor.BodyFrameSource.OpenReader();

            // set the BodyFramedArrived event notifier
            _bodyFrameReader.FrameArrived += Reader_BodyFrameArrived;

            // initialize the BodyViewer object for displaying tracked bodies in the UI
            _kinectBodyView = new KinectBodyView(_kinectSensor);

            // initialize the gesture detection objects for our gestures
            _gestureDetectorList = new List<GestureDetector>();

            // initialize the MainWindow
            InitializeComponent();

            // set our data context objects for display in UI
            DataContext = this;
            kinectBodyViewbox.DataContext = _kinectBodyView;

            // create a gesture detector for each body (6 bodies => 6 detectors) and create content controls to display results in the UI
            int col0Row = 0;
            int col1Row = 0;
            int maxBodies = _kinectSensor.BodyFrameSource.BodyCount;

            IList<string> dbList = new List<string>();
            const string defaultValue = @"Database\experimot.gbd";
            var node = App.NodeInfo;
            if (node != null)
            {
                dbList = ParameterUtil.GetCsvList(node.param, "database", defaultValue);
            }
            else
            {
                dbList.Add(defaultValue);
            }
            //MessageBox.Show(string.Join("\n", _node.param.Select(s=>s.value)));
            _database = new GestureDatabase(dbList);

            for (int i = 0; i < maxBodies; ++i)
            {
                var imageDict = _database.GestureImageSource;
                GestureResultView result = new GestureResultView(i, false, false, 0.0f, imageDict);
                GestureDetector detector = new GestureDetector(_kinectSensor, result, _database);
                _gestureDetectorList.Add(detector);

                // split gesture results across the first two columns of the content grid
                ContentControl contentControl = new ContentControl()
                {
                    Content = _gestureDetectorList[i].GestureResultView
                };

                if (i%2 == 0)
                {
                    // Gesture results for bodies: 0, 2, 4
                    Grid.SetColumn(contentControl, 0);
                    Grid.SetRow(contentControl, col0Row);
                    ++col0Row;
                }
                else
                {
                    // Gesture results for bodies: 1, 3, 5
                    Grid.SetColumn(contentControl, 1);
                    Grid.SetRow(contentControl, col1Row);
                    ++col1Row;
                }

                contentGrid.Children.Add(contentControl);
            }

            if (_kBodyPub == null)
            {
                _kBodyPub = new KinectBodyPublisher();
            }
            if (_humanPub == null)
            {
                _humanPub = new HumanPosePublisher();
            }
            if (_naoJoints == null)
            {
                _naoJoints = new NaoJointPublisher();
            }
        }

        public MainWindow(Indriya.Core.Msgs.Node node2) : this()
        {
            var node = App.NodeInfo;
            if (node != null)
            {
                if (node.publisher != null)
                {
                    foreach (var item in node.publisher)
                    {
                        if (item.msg_type == "KinectBodies")
                        {
                            _kBodyPub = new KinectBodyPublisher(item.host, item.port, item.topic);
                            Loaded += MainWindow_Loaded;
                        }
                        if (item.msg_type == "GestureTriggers")
                        {
                            _gestPub = GestureTriggerPublisher.Create(item.host, item.port, item.topic);
                        }
                        if (item.msg_type == "Humans")
                        {
                            _humanPub = new HumanPosePublisher(item.host, item.port, item.topic);
                        }
                        if (item.msg_type == "ParamList")
                        {
                            try
                            {
                                string defaultValue = @"nao_joints_h25v50.json";
                                var fileName = ParameterUtil.Get(node.param, "nao_joints", defaultValue);

                                var json = App.GetFileString(fileName, App.Options.ParameterServer);

                                defaultValue = @"kinect_nao_map.json";
                                fileName = ParameterUtil.Get(node.param, "nao_kinect", defaultValue);
                                var kinectJson = App.GetFileString(fileName, App.Options.ParameterServer);
                                _naoJoints = new NaoJointPublisher(item.host, item.port, item.topic, json, kinectJson);
                            }
                            catch (Exception ex)
                            {
                                MessageBox.Show(ex.StackTrace,ex.Message);
                            }
                        }
                        _log.Info("Gesture recognition node initialized from the config file");
                    }
                }
            }
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            if (_kBodyPub != null)
            {
                _kBodyPub.Initialize();
            }
            if (_gestPub != null)
            {
                _gestPub.Initialize();
            }
            if (_humanPub != null)
            {
                _humanPub.Initialize();
            }
            if (_naoJoints != null)
            {
                _naoJoints.Initialize();
            }
        }

        /// <summary>
        /// INotifyPropertyChangedPropertyChanged event to allow window controls to bind to changeable data
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// Gets or sets the current status text to display
        /// </summary>
        public string StatusText
        {
            get
            {
                return _statusText;
            }

            set
            {
                if (_statusText != value)
                {
                    _statusText = value;

                    // notify any bound elements that the text has changed
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("StatusText"));
                    }
                }
            }
        }

        /// <summary>
        /// Execute shutdown tasks
        /// </summary>
        /// <param name="sender">object sending the event</param>
        /// <param name="e">event arguments</param>
        private void MainWindow_Closing(object sender, CancelEventArgs e)
        {
            if (_kBodyPub != null)
            {
                _kBodyPub.Terminate();
                _kBodyPub = null;
            }
            if (_gestPub != null)
            {
                _gestPub.Terminate();
                _gestPub = null;
            }
            if (_humanPub != null)
            {
                _humanPub.Terminate();
                _humanPub = null;
            }
            if (_bodyFrameReader != null)
            {
                // BodyFrameReader is IDisposable
                _bodyFrameReader.FrameArrived -= Reader_BodyFrameArrived;
                _bodyFrameReader.Dispose();
                _bodyFrameReader = null;
            }

            if (_gestureDetectorList != null)
            {
                // The GestureDetector contains disposable members (VisualGestureBuilderFrameSource and VisualGestureBuilderFrameReader)
                foreach (GestureDetector detector in _gestureDetectorList)
                {
                    detector.Dispose();
                }

                _gestureDetectorList.Clear();
                _gestureDetectorList = null;
            }

            if (_kinectSensor != null)
            {
                _kinectSensor.IsAvailableChanged -= Sensor_IsAvailableChanged;
                _kinectSensor.Close();
                _kinectSensor = null;
            }
        }

        /// <summary>
        /// Handles the event when the sensor becomes unavailable (e.g. paused, closed, unplugged).
        /// </summary>
        /// <param name="sender">object sending the event</param>
        /// <param name="e">event arguments</param>
        private void Sensor_IsAvailableChanged(object sender, IsAvailableChangedEventArgs e)
        {
            // on failure, set the status text
            StatusText = _kinectSensor.IsAvailable ? Indriya.Kinect.Perception.Properties.Resources.RunningStatusText
                                                            : Indriya.Kinect.Perception.Properties.Resources.SensorNotAvailableStatusText;
        }

        /// <summary>
        /// Handles the body frame data arriving from the sensor and updates the associated gesture detector object for each body
        /// </summary>
        /// <param name="sender">object sending the event</param>
        /// <param name="e">event arguments</param>
        private void Reader_BodyFrameArrived(object sender, BodyFrameArrivedEventArgs e)
        {
            bool dataReceived = false;

            using (BodyFrame bodyFrame = e.FrameReference.AcquireFrame())
            {
                if (bodyFrame != null)
                {
                    if (_bodies == null)
                    {
                        // creates an array of 6 bodies, which is the max number of bodies that Kinect can track simultaneously
#if USE_KINECT_BODIES
                        _bodies = new Body[bodyFrame.BodyCount];
#else
                        _bodies = new SmoothedBodyList<ExponentialSmoother>();
#endif
                    }

                    // The first time GetAndRefreshBodyData is called, Kinect will allocate each Body in the array.
                    // As long as those body objects are not disposed and not set to null in the array,
                    // those body objects will be re-used.
                    bodyFrame.GetAndRefreshBodyData(_bodies);
#if USE_KINECT_BODIES
#else
                    _bodies.MapDepthPositions();
#endif
                    dataReceived = true;
                }
            }


            if (dataReceived)
            {
                // visualize the new body data
                _kinectBodyView.UpdateBodyFrame(_bodies);
                if(_kBodyPub!=null) _kBodyPub.UpdateBodyFrame(_bodies,_humanPub,_naoJoints);
                // we may have lost/acquired bodies, so update the corresponding gesture detectors
                if (_bodies != null)
                {
                    // loop through all bodies to see if any of the gesture detectors need to be updated
                    int maxBodies = _kinectSensor.BodyFrameSource.BodyCount;
                    for (int i = 0; i < maxBodies; ++i)
                    {
                        var body = _bodies[i];
                        ulong trackingId = body.TrackingId;
                        var torso = body.Joints[JointType.SpineBase];
                        var torsoOrient = body.JointOrientations[JointType.SpineBase];

                        _gestureDetectorList[i].GestureResultView.Position = (torso.TrackingState == TrackingState.Tracked) ? torso.Position : new CameraSpacePoint();
                        _gestureDetectorList[i].GestureResultView.Orientation = (torso.TrackingState == TrackingState.Tracked) ? torsoOrient.Orientation : new Vector4();                            

                        // if the current body TrackingId changed, update the corresponding gesture detector with the new value
                        if (trackingId != _gestureDetectorList[i].TrackingId)
                        {
                            //Joint torso = body.Joints[JointType.SpineBase];
                            //JointOrientation torsoOrient = body.JointOrientations[JointType.SpineBase];

                            //this.gestureDetectorList[i].GestureResultView.Position = (torso != null && torso.TrackingState == TrackingState.Tracked) ? torso.Position : new CameraSpacePoint();
                            //this.gestureDetectorList[i].GestureResultView.Orientation = (torso != null && torso.TrackingState == TrackingState.Tracked) ? torsoOrient.Orientation : new Vector4();                            
                            _gestureDetectorList[i].TrackingId = trackingId;
                            //this
                            // if the current body is tracked, unpause its detector to get VisualGestureBuilderFrameArrived events
                            // if the current body is not tracked, pause its detector so we don't waste resources trying to get invalid gesture results
                            _gestureDetectorList[i].IsPaused = trackingId == 0;
                        }
                    }
                }
            }
        }

        
    }
}
