using experimot.msgs;

namespace Scheduler.Core
{
    public class Gesture
    {
        private string _name;

        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }
    }

    public class Human
    {
        private string _id;
        private KinectBody _body;
        private Gesture _gesture;

        public string Id
        {
            get { return _id; }
            set { _id = value; }
        }

        public KinectBody Body
        {
            get { return _body; }
            set { _body = value; }
        }

        public Gesture Gesture
        {
            get { return _gesture; }
            set { _gesture = value; }
        }
    }
}