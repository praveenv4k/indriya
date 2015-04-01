using System.Collections.Generic;
using experimot.msgs;

namespace Scheduler.Core
{
    public class Localization
    {
        private Pose _currentPose;
        private Queue<Pose> _recentPoses;
        public const int RecentPosesCount = 100;

        public Localization()
        {
            _currentPose = new Pose();
            _recentPoses = new Queue<Pose>(RecentPosesCount);
        }

        public Pose CurrentPose
        {
            get { return _currentPose; }
            set
            {
                if (_currentPose != value)
                {
                    _currentPose = value;
                }
            }
        }

        public Queue<Pose> RecentPose
        {
            get { return _recentPoses; }
        }
    }
}