using System;

namespace Indriya.Application.Data
{
    /// <summary>
    /// Represents gesture confidence data
    /// </summary>
    public class GestureConfidenceData
    {
        /// <summary>
        /// Number of times the gesture is active (Time = CurrentActiveLapse*Period)
        /// </summary>
        public int CurrentActiveLapse { get; set; }
        /// <summary>
        /// Gesture count
        /// </summary>
        public int Count { get; set; }
        /// <summary>
        /// Gesture confidence level
        /// </summary>
        public int Level
        {
            get { return (int) _level; }
        }

        private readonly GestureConfidenceLevels _level;
        private bool _lastActive;
        private bool _active;
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="level">Gesture confidence level</param>
        public GestureConfidenceData(GestureConfidenceLevels level)
        {
            _level = level;
            Reset();
        }

        /// <summary>
        /// Reset the gesture confidence data. Clears count and active lapse
        /// </summary>
        public void Reset()
        {
            CurrentActiveLapse = 0;
            Count = 0;
            _lastActive = false;
            _active = false;
        }

        /// <summary>
        /// Update the gesture confidence data. Updates the activelapse and count
        /// </summary>
        /// <param name="active">Flag to tell if gesture is active</param>
        /// <param name="gesturePeriod">Gesture period</param>
        public void Update(bool active, int gesturePeriod)
        {
            _lastActive = _active;
            _active = active;
            if (active)
            {
                CurrentActiveLapse++;
            }
            if (_lastActive && !_active)
            {
                if (CurrentActiveLapse >= gesturePeriod)
                {
                    Count++;
                }
                CurrentActiveLapse = 0;
                Console.WriteLine(@"Statistics for level {0}: {1}", _level, Count);
            }
        }
    }
}