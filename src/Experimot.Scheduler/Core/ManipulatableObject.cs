using experimot.msgs;

namespace Scheduler.Core
{
    public class ManipulatableObject
    {
        private string _id;
        private Pose _pose;
        private Color _color;

        public string Id
        {
            get { return _id; }
            set { _id = value; }
        }

        public Pose Pose1
        {
            get { return _pose; }
            set { _pose = value; }
        }

        public Color Color
        {
            get { return _color; }
            set { _color = value; }
        }
    }
}