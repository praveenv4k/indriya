using System.ComponentModel;
using System.Runtime.CompilerServices;
using experimot.msgs;
using Experimot.Core.Annotations;

namespace Experimot.Core.Data
{
    public class ManipulatableObject: INotifyPropertyChanged
    {
        private string _id;
        private Pose _pose;
        private Color _color;

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

        public Pose Pose
        {
            get { return _pose; }
            set
            {
                if (Equals(value, _pose)) return;
                _pose = value;
                OnPropertyChanged();
            }
        }

        public Color Color
        {
            get { return _color; }
            set
            {
                if (Equals(value, _color)) return;
                _color = value;
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
}