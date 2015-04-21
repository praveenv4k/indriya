using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using experimot.msgs;
using Experimot.Core.Annotations;

namespace Experimot.Scheduler.Data
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