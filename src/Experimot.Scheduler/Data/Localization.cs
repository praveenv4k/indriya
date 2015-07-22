using System.Collections.Concurrent;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using experimot.msgs;
using Experimot.Core.Annotations;

namespace Experimot.Scheduler.Data
{
    /// <summary>
    /// Represents the localization information
    /// </summary>
    public class Localization : INotifyPropertyChanged
    {
        private Vector3d _currentPosition;
        private Quaternion _currentOrientation;
        private readonly ConcurrentQueue<Pose> _recentPoses;

        /// <summary>
        /// Cache size of recent poses
        /// </summary>
        public const int RecentPosesCount = 100;

        /// <summary>
        /// Constructor
        /// </summary>
        public Localization()
        {
            SetPose(new Pose()
            {
                position = new Vector3d() {x = 0, y = 0, z = 0},
                orientation = new Quaternion() {w = 1, x = 0, y = 0, z = 0}
            });
            _recentPoses = new ConcurrentQueue<Pose>();
        }

        /// <summary>
        /// Update the pose information from incoming message
        /// </summary>
        /// <param name="pose"></param>
        public void SetPose(Pose pose)
        {
            if (pose != null)
            {
                Position = pose.position;
                Orientation = pose.orientation;
            }
        }

        /// <summary>
        /// Position in 3D
        /// </summary>
        public Vector3d Position
        {
            get { return _currentPosition; }
            set
            {
                if (_currentPosition != value)
                {
                    if (Equals(value, _currentPosition)) return;
                    _currentPosition = value;
                    OnPropertyChanged();
                }
            }
        }

        /// <summary>
        /// Orientation in 3D
        /// </summary>
        public Quaternion Orientation
        {
            get { return _currentOrientation; }
            set
            {
                if (_currentOrientation != value)
                {
                    if (Equals(value, _currentOrientation)) return;
                    _currentOrientation = value;
                    OnPropertyChanged();
                }
            }
        }

        /// <summary>
        /// Recent poses
        /// </summary>
        [Browsable(false)]
        public ConcurrentQueue<Pose> RecentPose
        {
            get { return _recentPoses; }
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