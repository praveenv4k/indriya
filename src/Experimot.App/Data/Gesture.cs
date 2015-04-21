using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using Experimot.Core.Annotations;

namespace Experimot.Scheduler.Data
{
    public enum GestureMode
    {
        Discrete,
        Continuous
    }

    public class GestureModule : INotifyPropertyChanged
    {
        private string _name;
        public event PropertyChangedEventHandler PropertyChanged;

        [Annotations.NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }

        public string Name
        {
            get { return _name; }
            set
            {
                if (value == _name) return;
                _name = value;
                OnPropertyChanged();
            }
        }

        public ObservableCollection<Gesture> Gestures
        {
            get { return _gestures; }
        }

        private readonly ObservableCollection<Gesture> _gestures;

        public GestureModule(experimot.msgs.GestureRecognitionModule module)
        {
            _gestures = new ObservableCollection<Gesture>();
            if (module != null)
            {
                Name = module.name;
                foreach (var gestureDescription in module.motions)
                {
                    _gestures.Add(new Gesture()
                    {
                        Name = gestureDescription.name,
                        Mode = (GestureMode) gestureDescription.type
                    });
                }
            }
        }
    }

    public class Gesture : INotifyPropertyChanged
    {
        protected string _name;
        protected GestureMode _gestureMode;

        public string Name
        {
            get { return _name; }
            set
            {
                if (value == _name) return;
                _name = value;
                OnPropertyChanged();
            }
        }

        public GestureMode Mode
        {
            get { return _gestureMode; }
            set
            {
                if (value == _gestureMode) return;
                _gestureMode = value;
                OnPropertyChanged();
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }
    }

    public class ContinuousGesture : Gesture
    {
        protected int _progress;

        public int Progress
        {
            get { return _progress; }
            set
            {
                if (value == _progress) return;
                _progress = value;
                OnPropertyChanged();
            }
        }
    }

    public class DiscreteGesture : Gesture
    {
        private int _count;
        private bool _active;
        public EventHandler<DiscreteGestureArgs> GestureTriggered;

        public DiscreteGesture()
        {
            _count = 0;
        }

        public int Count
        {
            get { return _count; }
            private set
            {
                if (_count != value)
                {
                    _count = value;
                    var handler = GestureTriggered;
                    if (handler != null)
                    {
                        handler(this, new DiscreteGestureArgs(this));
                    }
                }
            }
        }

        public bool Active
        {
            get { return _active; }
            set
            {
                if (value.Equals(_active)) return;
                if (!_active && value)
                {
                    Count = Count + 1;
                }
                _active = value;
                OnPropertyChanged();
            }
        }
    }

    public class DiscreteGestureArgs : EventArgs
    {
        private readonly DiscreteGesture _gesture;

        public DiscreteGestureArgs(DiscreteGesture gesture)
        {
            _gesture = gesture;
        }

        public DiscreteGesture Gesture
        {
            get { return _gesture; }
        }
    }
}