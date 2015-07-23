using System.ComponentModel;
using System.Runtime.CompilerServices;
using Experimot.Core.Annotations;
using Indriya.Core.Msgs;

namespace Indriya.Application.Data
{
    /// <summary>
    /// Represents a manipulatable object
    /// </summary>
    public class ManipulatableObject: INotifyPropertyChanged
    {
        private string _id;
        private Pose _pose;
        private Color _color;

        /// <summary>
        /// Id of the object
        /// </summary>
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

        /// <summary>
        /// Pose of the object
        /// </summary>
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

        /// <summary>
        /// Color of the object
        /// </summary>
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
    }
}