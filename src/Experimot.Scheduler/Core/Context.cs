using System.Collections;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using experimot.msgs;
using Experimot.Scheduler.Annotations;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace Experimot.Scheduler.Core
{
    public class Context : INotifyPropertyChanged
    {
        private Robot _robot;
        private readonly IDictionary<int, Human> _humans;
        private readonly IDictionary<string, ManipulatableObject> _objects;
        private readonly object _object = new object();

        public Context()
        {
            _humans = new ConcurrentDictionary<int, Human>();
            _robot = new Robot();
            _objects = new ConcurrentDictionary<string, ManipulatableObject>();
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
        //public IDictionary<int, Human> Humans
        //{
        //    get { return _humans; }
        //}

        [ExpandableObject]
        //[Xceed.Wpf.Toolkit.PropertyGrid.Attributes.ItemsSource(typeof(Human))]
        public IEnumerable Humans
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
                Robot.Localization.CurrentPose = pose;
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
                _humans.Clear();
                foreach (var kinectBody in kinectBodies.Body)
                {
                    _humans.Add(kinectBody.TrackingId, new Human());
                    _humans[kinectBody.TrackingId].Body = kinectBody;
                }
            }
        }
    }
}
