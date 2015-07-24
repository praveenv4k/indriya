using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using Indriya.Core.Msgs;
using Indriya.Core.Properties;
using Newtonsoft.Json;
using ILog = Common.Logging.ILog;
using LogManager = Common.Logging.LogManager;

namespace Indriya.Core.Data
{
    /// <summary>
    /// Represents the application context
    /// </summary>
    public class Context : INotifyPropertyChanged
    {
        private Robot _robot;

        private readonly Pose _worldFrame = new Pose()
        {
            id = 0,
            name = "WorldFrame",
            position = new Vector3d() {x = 0, y = 0, z = 0},
            orientation = new Quaternion() {w = 1, x = 0, y = 0, z = 0}
        };

        private ObservableCollection<Human> _humans;
        private IDictionary<string, ManipulatableObject> _objects;
        private readonly object _object = new object();
        private ObservableCollection<GestureModule> _motionModules;
        private ObservableCollection<VoiceRecognitionModule> _voiceModules;
        private ObservableCollection<RobotBehaviorModule> _behaviorModules;
        private static readonly ILog Log = LogManager.GetLogger<Context>();
        private readonly VoiceCommandManager _voiceCommandManager;
        private bool _serializeHuman;

        /// <summary>
        /// Constructor
        /// </summary>
        public Context()
        {
            Humans = new ObservableCollection<Human>();
            Robot = new Robot();
            _voiceCommandManager = new VoiceCommandManager();
            Objects = new ConcurrentDictionary<string, ManipulatableObject>();
            MotionModules = new ObservableCollection<GestureModule>();
            BehaviorModules = new ObservableCollection<RobotBehaviorModule>();
            VoiceRecognitionModules = new ObservableCollection<VoiceRecognitionModule>();
        }

        /// <summary>
        /// Description of robot
        /// </summary>
        public Robot Robot
        {
            get { return _robot; }
            private set
            {
                if (Equals(value, _robot)) return;
                _robot = value;
                OnPropertyChanged();
            }
        }

        /// <summary>
        /// Collection of human in the environment
        /// </summary>
        public ObservableCollection<Human> Humans
        {
            get { return _humans; }
            set { _humans = value; }
        }

        /// <summary>
        /// Collection of objects in the environment
        /// </summary>
        public IDictionary<string, ManipulatableObject> Objects
        {
            get { return _objects; }
            set { _objects = value; }
        }

        /// <summary>
        /// List of registered Motion recognition modules
        /// </summary>
        public ObservableCollection<GestureModule> MotionModules
        {
            get { return _motionModules; }
            set { _motionModules = value; }
        }

        /// <summary>
        /// List of registered Robot behavior modules
        /// </summary>
        public ObservableCollection<RobotBehaviorModule> BehaviorModules
        {
            get { return _behaviorModules; }
            set { _behaviorModules = value; }
        }

        /// <summary>
        /// List of registered speech recognition modules
        /// </summary>
        public ObservableCollection<VoiceRecognitionModule> VoiceRecognitionModules
        {
            get { return _voiceModules; }
            set { _voiceModules = value; }
        }

        /// <summary>
        /// Transformation of world reference frame
        /// </summary>
        public Pose WorldFrame
        {
            get { return _worldFrame; }
        }

        /// <summary>
        /// Manages the speech commands from the user
        /// </summary>
        public VoiceCommandManager VoiceCommandManager
        {
            get { return _voiceCommandManager; }
        }

        /// <summary>
        /// Property changed event handler
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }

        /// <summary>
        /// Prepared the context for new program
        /// </summary>
        public void PrepareForNewProgram()
        {
            lock (_object)
            {
                foreach (var human in Humans)
                {
                    foreach (var gesture in human.Gestures)
                    {
                        gesture.Reset();
                    }
                }
            }
        }

        /// <summary>
        /// Set the world reference frame transformation
        /// </summary>
        /// <param name="pose">World frame transformation</param>
        public void SetWorldFrame(Pose pose)
        {
            if (pose != null)
            {
                _worldFrame.position = pose.position;
                _worldFrame.orientation = pose.orientation;
            }
        }

        /// <summary>
        /// Update a message of type Pose_V
        /// </summary>
        /// <param name="pose">List of pose message</param>
        public void Update(Pose_V pose)
        {
            lock (_object)
            {
                Robot.Localization.SetPose(pose.pose.FirstOrDefault(s => s.name == "torso_frame_kinect"));
                SetWorldFrame(pose.pose.FirstOrDefault(s => s.name == "world_frame_kinect"));
            }
        }

        /// <summary>
        /// Update the joint values of the robot
        /// </summary>
        /// <param name="jointValue">List of joint values</param>
        public void Update(JointValueVector jointValue)
        {
            lock (_object)
            {
                Robot.SensorData.JointValues = jointValue;
            }
        }

        /// <summary>
        /// Update the sensor data of the robot
        /// </summary>
        /// <param name="sensorData">Sensor data</param>
        public void Update(SensorData sensorData)
        {
            lock (_object)
            {
                Robot.SensorData = sensorData;
            }
        }

        /// <summary>
        /// Update the voice command from the human
        /// </summary>
        /// <param name="command">Voice command</param>
        public void Update(VoiceCommandDescription command)
        {
            lock (_object)
            {
                if (VoiceCommandManager != null)
                {
                    //Log.InfoFormat("Updating the voice commands");
                    VoiceCommandManager.Update(command);
                }
            }
        }

        /// <summary>
        /// Update the skeleton information of the humans
        /// </summary>
        /// <param name="kinectBodies">Skeleton list</param>
        public void Update(KinectBodies kinectBodies)
        {
            lock (_object)
            {
                if (kinectBodies.Body.Count <= 0)
                {
                    Humans.Clear();
                    return;
                }
                var keys = Humans.Select(s => s.Body.TrackingId).ToList();
                var bodyIds = kinectBodies.Body.Select(s => s.TrackingId).ToList();

                // Remove those humans that dont exist in the list of kinect bodies anymore
                foreach (var key in keys)
                {
                    if (!bodyIds.Contains(key))
                    {
                        var item = Humans.FirstOrDefault(s => s.Body.TrackingId == key);
                        if (item != null)
                        {
                            Humans.Remove(item);
                            Log.InfoFormat("Removed human: {0}", item.Id);
                        }
                    }
                }

                foreach (var kinectBody in kinectBodies.Body)
                {
                    var item = Humans.FirstOrDefault(s => s.Body.TrackingId == kinectBody.TrackingId);
                    if (item == null)
                    {
                        var human = new Human(kinectBody.TrackingId, _motionModules)
                        {
                            Body = kinectBody
                        };
                        Humans.Add(human);
                        Log.InfoFormat("Added new human: {0}", human.Id);
                    }
                    else
                    {
                        item.Body = kinectBody;
                    }
                }
                if (Humans.Count > 0 && !_serializeHuman)
                {
                    var humansStr = JsonConvert.SerializeObject(Humans);
                    var humansObj = JsonConvert.DeserializeObject<ObservableCollection<Human>>(humansStr);
                    if (humansObj != null)
                    {
                        Console.WriteLine(humansStr);
                    }
                    _serializeHuman = true;
                }
            }
        }

        /// <summary>
        /// Update the gesture triggers from the gesture recognition module
        /// </summary>
        /// <param name="triggers">Gesture trigger list</param>
        public void Update(GestureTriggers triggers)
        {
            if (triggers != null)
            {
                lock (_object)
                {
                    if (_humans.Count > 0)
                    {
                        var item = _humans.FirstOrDefault(s => s.Body.TrackingId == triggers.id);
                        if (item != null)
                        {
                            foreach (var trigger in triggers.motion)
                            {
                                var gest = item.Gestures.FirstOrDefault(g => g.Name == trigger.name);

                                if (gest != null && !string.IsNullOrEmpty(trigger.name))
                                {
                                    gest.Refresh(trigger);
                                }
                                else
                                {
                                    if (!string.IsNullOrEmpty(trigger.name))
                                    {
                                        var newGest = new Gesture(trigger.name, (GestureMode) trigger.type);
                                        newGest.Refresh(trigger);
                                        item.Gestures.Add(newGest);
                                    }
                                }

                            }
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Update the gesture trigger from gesture recognition module
        /// </summary>
        /// <param name="trigger">Gesture trigger</param>
        public void Update(GestureTrigger trigger)
        {
            if (trigger != null)
            {
                Console.WriteLine(trigger.motion.name);
                lock (_object)
                {
                    if (_humans.Count > 0)
                    {
                        var item = _humans[0];
                        if (item != null)
                        {
                            var gest = item.Gestures.FirstOrDefault(g => g.Name == trigger.motion.name);

                            if (gest != null && !string.IsNullOrEmpty(trigger.motion.name))
                            {
                                gest.Refresh(trigger.motion);
                            }
                            else
                            {
                                if (!string.IsNullOrEmpty(trigger.motion.name))
                                {
                                    var newGest = new Gesture(trigger.motion.name, (GestureMode) trigger.motion.type);
                                    newGest.Refresh(trigger.motion);
                                    item.Gestures.Add(newGest);
                                }
                            }
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Update humans information
        /// </summary>
        /// <param name="humans">List of human</param>
        public void Update(Humans humans)
        {
            if (humans != null)
            {
                lock (_object)
                {
                    foreach (var human in humans.human)
                    {
                        //TODO Need to unify the usage of tracking id across the application
                        var item = _humans.FirstOrDefault(s => s.Body.TrackingId == human.id);
                        if (item != null)
                        {
                            item.HeadPosition = human.head_position;
                            item.TorsoPosition = human.torso_position;
                            item.TorsoOrientation = human.orientation;
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Register the gesture recognition module to the context
        /// </summary>
        /// <param name="module">Module information</param>
        public void RegisterMotionRecognitionModule(GestureRecognitionModule module)
        {
            if (module != null && !string.IsNullOrEmpty(module.name))
            {
                lock (_object)
                {
                    var regMod = _motionModules.FirstOrDefault(s => s.Name == module.name);
                    if (regMod == null)
                    {
                        _motionModules.Add(new GestureModule(module));
                    }
                    else
                    {
                        regMod = new GestureModule(module);
                    }
                }
            }
        }

        /// <summary>
        /// Register the voice recognition module to the context
        /// </summary>
        /// <param name="module">Module information</param>
        public void RegisterVoiceRecognitionModule(VoiceRecognitionModule module)
        {
            if (module != null && !string.IsNullOrEmpty(module.name))
            {
                lock (_object)
                {
                    var regMod = _voiceModules.FirstOrDefault(s => s.name == module.name);
                    if (regMod == null)
                    {
                        _voiceModules.Add(module);
                    }
                    else
                    {
                        regMod = module;
                    }
                }
            }
        }

        /// <summary>
        /// Register the robot behavior module information to the context
        /// </summary>
        /// <param name="module">Module information</param>
        public void RegisterRobotBehaviorModule(RobotBehaviorModule module)
        {
            if (module != null && !string.IsNullOrEmpty(module.name))
            {
                lock (_object)
                {
                    var regMod = _behaviorModules.FirstOrDefault(s => s.name == module.name);
                    if (regMod == null)
                    {
                        _behaviorModules.Add(module);
                    }
                    else
                    {
                        regMod = module;
                    }
                }
            }
        }

    }
}
