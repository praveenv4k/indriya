using System.Collections.Concurrent;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using experimot.msgs;
using Experimot.Scheduler.Annotations;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace Experimot.Scheduler.Core
{
    public class Localization: INotifyPropertyChanged
    {
        private Pose _currentPose;
        private readonly ConcurrentQueue<Pose> _recentPoses;
        public const int RecentPosesCount = 100;

        public Localization()
        {
            _currentPose = new Pose();
            _recentPoses = new ConcurrentQueue<Pose>();
        }

        [ExpandableObject]
        public Pose CurrentPose
        {
            get { return _currentPose; }
            set
            {
                if (_currentPose != value)
                {
                    if (Equals(value, _currentPose)) return;
                    _currentPose = value;
                    OnPropertyChanged();
                }
            }
        }

        [ExpandableObject]
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