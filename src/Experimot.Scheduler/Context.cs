using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using Common.Logging;
using experimot.msgs;
using Experimot.Scheduler.Annotations;
using Experimot.Scheduler.Data;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using Xceed.Wpf.Toolkit.PropertyGrid.Editors;

namespace Experimot.Scheduler
{
    public class Context : INotifyPropertyChanged
    {
        private Robot _robot;
        //private readonly IDictionary<int, Human> _humans;
        private readonly IList<Human> _humans;
        private readonly IDictionary<string, ManipulatableObject> _objects;
        private readonly object _object = new object();
        private readonly ObservableCollection<GestureModule> _motionModules;
        private readonly ObservableCollection<RobotBehaviorModule> _behaviorModules;
        private static readonly ILog Log = LogManager.GetLogger<Context>();

        public Context()
        {
            //_humans = new ConcurrentDictionary<int, Human>();
            _humans = new List<Human>();
            _robot = new Robot();
            _objects = new ConcurrentDictionary<string, ManipulatableObject>();
            _motionModules = new ObservableCollection<GestureModule>();
            _behaviorModules = new ObservableCollection<RobotBehaviorModule>();
        }

        [ExpandableObject]
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

        //[ExpandableObject]
        [Editor(typeof (CollectionEditor), typeof (CollectionEditor))]
        public IList<Human> Humans
        {
            get { return _humans; }
        }

        [ExpandableObject]
        public IDictionary<string, ManipulatableObject> Objects
        {
            get { return _objects; }
        }

        [ExpandableObject]
        public ObservableCollection<GestureModule> MotionModules
        {
            get { return _motionModules; }
        }

        [ExpandableObject]
        public ObservableCollection<RobotBehaviorModule> BehaviorModules
        {
            get { return _behaviorModules; }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }

        public void Update(Pose pose)
        {
            lock (_object)
            {
                Robot.Localization.SetPose(pose);
            }
        }

        public void Update(SensorData sensorData)
        {
            lock (_object)
            {
                Robot.SensorData = sensorData;
            }
        }

        public void Update(KinectBodies kinectBodies)
        {
            lock (_object)
            {
                var keys = _humans.Select(s => s.Body.TrackingId).ToList();
                var bodyIds = kinectBodies.Body.Select(s => s.TrackingId).ToList();

                // Remove those humans that dont exist in the list of kinect bodies anymore
                foreach (var key in keys)
                {
                    if (!bodyIds.Contains(key))
                    {
                        var item = _humans.FirstOrDefault(s => s.Body.TrackingId == key);
                        if (item != null)
                        {
                            _humans.Remove(item);
                        }
                    }
                }

                foreach (var kinectBody in kinectBodies.Body)
                {
                    var item = _humans.FirstOrDefault(s => s.Body.TrackingId == kinectBody.TrackingId);
                    if (item == null)
                    {
                        _humans.Add(new Human()
                        {
                            Body = kinectBody,
                            Id = kinectBody.TrackingId.ToString()
                        });
                    }
                    else
                    {
                        item.Body = kinectBody;
                    }
                }
            }
        }

        public void Update(GestureTrigger trigger)
        {
            Log.Info("Gesture Update");
            if (trigger != null)
            {
                lock (_object)
                {
                    //if
                    var item = _humans.FirstOrDefault(s => s.Body.TrackingId == trigger.id);
                    if (item != null)
                    {
                        var gest = item.Gestures.FirstOrDefault(g => g.Name == trigger.motion.name);
                        if (gest != null)
                        {
                            if (trigger.motion.confidence < 85 || !trigger.motion.active)
                            {
                                item.Gestures.Remove(gest);
                                Log.InfoFormat("Gesture Removed: {0}",trigger.motion.name);
                            }
                            else
                            {
                                //gest = new Gesture
                                //{
                                //    Name = trigger.motion.name,
                                //    Mode = (GestureMode) trigger.motion.type
                                //};
                            }
                        }
                        else
                        {
                            if (trigger.motion.confidence > 85 || trigger.motion.active)
                            {
                                item.Gestures.Add(new Gesture
                                {
                                    Name = trigger.motion.name,
                                    Mode = (GestureMode) trigger.motion.type
                                });
                                Log.InfoFormat("Gesture Added: {0}", trigger.motion.name);
                            }
                        }
                    }
                }
            }
        }

        public void RegisterMotionRecognitionModule(experimot.msgs.GestureRecognitionModule module)
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

        public void RegisterRobotBehaviorModule(experimot.msgs.RobotBehaviorModule module)
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
