using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using Indriya.Core.Properties;
using Indriya.Core.Msgs;
using Newtonsoft.Json;

namespace Indriya.Core.Data
{
    /// <summary>
    /// Represents information about a human
    /// </summary>
    public class Human : INotifyPropertyChanged
    {
        private int _id;

        private KinectBody _body;

        private readonly ObservableCollection<Gesture> _gestures;
        private Vector3d _headPosition;
        private Vector3d _torsoPosition;
        private Quaternion _torsoOrientation;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="id">Identifier of the human</param>
        public Human(int id)
        {
            _id = id;
            _gestures = new ObservableCollection<Gesture>();
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="id">Identifier of the human</param>
        /// <param name="modules">List of gesture modules</param>
        public Human(int id, IList<GestureModule> modules) : this(id)
        {
            if (modules != null)
            {
                foreach (var module in modules)
                {
                    if (module.Gestures != null && module.Gestures.Count > 0)
                    {
                        foreach (var gestureDescription in module.Gestures)
                        {
                            _gestures.Add(new Gesture(gestureDescription.Name, gestureDescription.Mode));
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Identifier of the human
        /// </summary>
        public int Id
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
        /// Skeleton information of the human
        /// </summary>
        [JsonIgnore]
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

        /// <summary>
        /// Human head position
        /// </summary>
        public Vector3d HeadPosition
        {
            get { return _headPosition; }
            set
            {
                if (Equals(value, _headPosition)) return;
                _headPosition = value;
                OnPropertyChanged();
            }
        }

        /// <summary>
        /// Human Torso position
        /// </summary>
        public Vector3d TorsoPosition
        {
            get { return _torsoPosition; }
            set
            {
                if (Equals(value, _torsoPosition)) return;
                _torsoPosition = value;
                OnPropertyChanged();
            }
        }

        /// <summary>
        /// Human torso orientation. Computed from Shoulder points and spine base
        /// </summary>
        public Quaternion TorsoOrientation
        {
            get { return _torsoOrientation; }
            set
            {
                if (Equals(value, _torsoOrientation)) return;
                _torsoOrientation = value;
                OnPropertyChanged();
            }
        }

        /// <summary>
        /// List of gestures
        /// </summary>
        public ObservableCollection<Gesture> Gestures
        {
            get { return _gestures; }
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