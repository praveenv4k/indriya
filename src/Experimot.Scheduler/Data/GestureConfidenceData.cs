using System;

namespace Experimot.Scheduler.Data
{
    public class GestureConfidenceData
    {
        public int CurrentActiveLapse { get; set; }
        public int Count { get; set; }

        public int Level
        {
            get { return (int) _level; }
        }

        private readonly GestureConfidenceLevels _level;
        private bool _lastActive;
        private bool _active;

        public GestureConfidenceData(GestureConfidenceLevels level)
        {
            _level = level;
            CurrentActiveLapse = 0;
            Count = 0;
            _lastActive = false;
            _active = false;
        }

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