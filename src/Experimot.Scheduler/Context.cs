using System.Collections.Concurrent;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using experimot.msgs;
using Experimot.Core.Data;
using Experimot.Scheduler.Annotations;
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
        private readonly IDictionary<string, GestureRecognitionModule> _motionModules;
        private readonly IDictionary<string, RobotBehaviorModule> _behaviorModules;

        public Context()
        {
            //_humans = new ConcurrentDictionary<int, Human>();
            _humans = new List<Human>();
            _robot = new Robot();
            _objects = new ConcurrentDictionary<string, ManipulatableObject>();
            _motionModules = new ConcurrentDictionary<string, GestureRecognitionModule>();
            _behaviorModules = new ConcurrentDictionary<string, RobotBehaviorModule>();
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

        public void RegisterMotionRecognitionModule(experimot.msgs.GestureRecognitionModule module)
        {
            if (module != null && !string.IsNullOrEmpty(module.name))
            {
                lock (_object)
                {
                    if (_motionModules.ContainsKey(module.name))
                    {
                        _motionModules.Add(module.name, module);
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
                    if (_behaviorModules.ContainsKey(module.name))
                    {
                        _behaviorModules.Add(module.name, module);
                    }
                }
            }
        }
    }
}
