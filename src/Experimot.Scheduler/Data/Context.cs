using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using Caliburn.Micro;
using experimot.msgs;
using Experimot.Scheduler.Annotations;
using ILog = Common.Logging.ILog;
using LogManager = Common.Logging.LogManager;

namespace Experimot.Scheduler.Data
{
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
        private BindableCollection<Human> _humans;
        private IDictionary<string, ManipulatableObject> _objects;
        private readonly object _object = new object();
        private BindableCollection<GestureModule> _motionModules;
        private BindableCollection<RobotBehaviorModule> _behaviorModules;
        private static readonly ILog Log = LogManager.GetLogger<Context>();
        private readonly VoiceCommandManager _voiceCommandManager;

        public Context()
        {
            Humans = new BindableCollection<Human>();
            Robot = new Robot();
            _voiceCommandManager = new VoiceCommandManager();
            Objects = new ConcurrentDictionary<string, ManipulatableObject>();
            MotionModules = new BindableCollection<GestureModule>();
            BehaviorModules = new BindableCollection<RobotBehaviorModule>();
        }

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

        public BindableCollection<Human> Humans
        {
            get { return _humans; }
            set { _humans = value; }
        }

        public IDictionary<string, ManipulatableObject> Objects
        {
            get { return _objects; }
            set { _objects = value; }
        }

        public BindableCollection<GestureModule> MotionModules
        {
            get { return _motionModules; }
            set { _motionModules = value; }
        }

        public BindableCollection<RobotBehaviorModule> BehaviorModules
        {
            get { return _behaviorModules; }
            set { _behaviorModules = value; }
        }

        public Pose WorldFrame
        {
            get { return _worldFrame; }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }

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

        public void SetWorldFrame(Pose pose)
        {
            if (pose != null)
            {
                _worldFrame.position = pose.position;
                _worldFrame.orientation = pose.orientation;
            }
        }

        public void Update(Pose_V pose)
        {
            lock (_object)
            {
                Robot.Localization.SetPose(pose.pose.FirstOrDefault(s => s.name == "torso_frame_kinect"));
                SetWorldFrame(pose.pose.FirstOrDefault(s => s.name == "world_frame_kinect"));
            }
        }

        public void Update(JointValueVector jointValue)
        {
            lock (_object)
            {
                Robot.SensorData.JointValues = jointValue;
            }
        }

        public void Update(SensorData sensorData)
        {
            lock (_object)
            {
                Robot.SensorData = sensorData;
            }
        }

        //public void Update(ParamList list)
        //{
        //    if (list != null)
        //    {
        //        Console.WriteLine(string.Join(",", list.param.Select(s => s.value).ToList()));
        //    }
        //}

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

                        // Check below is not needed since only tracked kinect bodies are published by the publisher

                        //if (!kinectBody.IsTracked)
                        //{
                        //    Humans.Remove(item);
                        //    Log.InfoFormat("Removed untracked human: {0}", item.Id);
                        //}
                        //else
                        //{
                        //    item.Body = kinectBody;
                        //}
                    }
                }
            }
        }

        public void Update(GestureTriggers triggers)
        {
            if (triggers != null)
            {
                lock (_object)
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
