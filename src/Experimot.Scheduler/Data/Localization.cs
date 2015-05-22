using System.Collections.Concurrent;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using experimot.msgs;
using Experimot.Core.Annotations;

namespace Experimot.Scheduler.Data
{
    public class Localization: INotifyPropertyChanged
    {
        private Vector3d _currentPosition;
        private Quaternion _currentOrientation;
        private readonly ConcurrentQueue<Pose> _recentPoses;
        public const int RecentPosesCount = 100;

        public Localization()
        {
            SetPose(new Pose()
            {
                position = new Vector3d() {x = 0, y = 0, z = 0},
                orientation = new Quaternion() {w = 1, x = 0, y = 0, z = 0}
            });
            _recentPoses = new ConcurrentQueue<Pose>();
        }

        public void SetPose(Pose pose)
        {
            if (pose != null)
            {
                Position = pose.position;
                Orientation = pose.orientation;
            }
        }

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

        //[ExpandableObject]
        [Browsable(false)]
        public ConcurrentQueue<Pose> RecentPose
        {
            get { return _recentPoses; }
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