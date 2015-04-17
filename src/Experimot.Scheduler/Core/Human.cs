using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using experimot.msgs;
using Experimot.Scheduler.Annotations;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace Experimot.Scheduler.Core
{
    public class Human : INotifyPropertyChanged
    {
        private string _id;

        private KinectBody _body;

        private readonly ObservableCollection<Gesture> _gestures;

        public Human()
        {
            _gestures = new ObservableCollection<Gesture>();
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

        [ExpandableObject]
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

        //[ExpandableObject]
        //public Gesture Gesture
        //{
        //    get { return _gesture; }
        //    set
        //    {
        //        if (Equals(value, _gesture)) return;
        //        _gesture = value;
        //        OnPropertyChanged();
        //    }
        //}

        [ExpandableObject]
        public ObservableCollection<Gesture> Gestures
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