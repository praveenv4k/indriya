using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using Caliburn.Micro;
using experimot.msgs;
using Experimot.Core.Annotations;

namespace Experimot.Scheduler.Data
{
    public class Human : INotifyPropertyChanged
    {
        private string _id;

        private KinectBody _body;

        private readonly BindableCollection<Gesture> _gestures;

        public Human()
        {
            _gestures = new BindableCollection<Gesture>();
        }

        public Human(IList<GestureModule> modules)
        {
            _gestures = new BindableCollection<Gesture>();
            if (modules != null)
            {
                foreach (var module in modules)
                {
                    if (module.Gestures != null && module.Gestures.Count > 0)
                    {
                        foreach (var gestureDescription in module.Gestures)
                        {
                            _gestures.Add(Gesture.Default(gestureDescription.Name, gestureDescription.Mode));
                        }
                    }
                }
            }
        }

        public string Id
        {
            get { return _id; }
            set
            {
                if (value == _id) return;
                _id = value;
                OnPropertyChanged();
            }
        }

        public KinectBody Body
        {
            get { return _body; }
            set
            {
                if (Equals(value, _body)) return;
                _body = value;
                OnPropertyChanged();
            }
        }

        public BindableCollection<Gesture> Gestures
        {
            get { return _gestures; }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}