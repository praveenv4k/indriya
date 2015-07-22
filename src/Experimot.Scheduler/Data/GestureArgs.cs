using System;

namespace Experimot.Scheduler.Data
{
    /// <summary>
    /// Gesture event arguments class
    /// </summary>
    public class GestureArgs : EventArgs
    {
        private readonly Gesture _gesture;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="gesture">Gesture object</param>
        public GestureArgs(Gesture gesture)
        {
            _gesture = gesture;
        }

        /// <summary>
        /// Associated gesture object
        /// </summary>
        public Gesture Gesture
        {
            get { return _gesture; }
        }
    }
}