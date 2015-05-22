using System;

namespace Experimot.Scheduler.Data
{
    public class GestureArgs : EventArgs
    {
        private readonly Gesture _gesture;

        public GestureArgs(Gesture gesture)
        {
            _gesture = gesture;
        }

        public Gesture Gesture
        {
            get { return _gesture; }
        }
    }
}