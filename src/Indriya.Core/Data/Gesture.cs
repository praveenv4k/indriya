using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using Indriya.Core.Properties;
using Indriya.Core.Msgs;

namespace Indriya.Core.Data
{
    /// <summary>
    /// Represents a gesture
    /// </summary>
    public class Gesture : INotifyPropertyChanged
    {
        private string _name;
        private GestureMode _gestureMode;
        private bool _active;
        private readonly Dictionary<GestureConfidenceLevels, GestureConfidenceData> _confidenceDict;
        protected const int GesturePeriod = 2;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="name">Name of the gesture</param>
        /// <param name="mode">Mode of the gesture</param>
        public Gesture(string name, GestureMode mode)
        {
            //_currentLapse = 0;
            Name = name;
            Mode = mode;
            Active = false;
            Confidence = 0;
            Count = 0;
            Progress = 0;
            _confidenceDict = new Dictionary<GestureConfidenceLevels, GestureConfidenceData>
            {
                {GestureConfidenceLevels.Low, new GestureConfidenceData(GestureConfidenceLevels.Low)},
                {GestureConfidenceLevels.Average, new GestureConfidenceData(GestureConfidenceLevels.Average)},
                {GestureConfidenceLevels.Good, new GestureConfidenceData(GestureConfidenceLevels.Good)},
                {GestureConfidenceLevels.Better, new GestureConfidenceData(GestureConfidenceLevels.Better)},
                {GestureConfidenceLevels.Best, new GestureConfidenceData(GestureConfidenceLevels.Best)},
            };
        }

        /// <summary>
        /// To check if the gesture confidence is above a certain level
        /// </summary>
        /// <param name="confidence">Confidence value</param>
        /// <param name="level">Confidence level</param>
        /// <returns>True if confidence is above the level</returns>
        private bool IsActive(int confidence, GestureConfidenceLevels level)
        {
            return confidence >= (int) level;
        }

        /// <summary>
        /// Update the count of the confidence levels above the given confidence value
        /// </summary>
        /// <param name="confidence"></param>
        private void UpdateConfidenceLevels(int confidence)
        {
            var enumArray = Enum.GetValues(typeof (GestureConfidenceLevels));
            foreach (var item in enumArray)
            {
                var val = (GestureConfidenceLevels) item;
                _confidenceDict[val].Update(IsActive(confidence, val),
                    GesturePeriod);
            }
        }

        /// <summary>
        /// Refreshed the gesture with the gesture trigger
        /// </summary>
        /// <param name="trigger">Gesture Trigger</param>
        public void Refresh(GestureDescription trigger)
        {
            if (trigger != null)
            {
                Name = trigger.name;
                Mode = (GestureMode) trigger.type;
                Active = trigger.active;
                Confidence = trigger.confidence;
                Progress = trigger.progress;

                UpdateConfidenceLevels(Confidence);
            }
        }

        /// <summary>
        /// Reset the confidence level count
        /// </summary>
        public void Reset()
        {
            var enumArray = Enum.GetValues(typeof(GestureConfidenceLevels));
            foreach (var item in enumArray)
            {
                var val = (GestureConfidenceLevels)item;
                _confidenceDict[val].Reset();
            }
        }

        /// <summary>
        /// Name of the gesture
        /// </summary>
        public string Name
        {
            get { return _name; }
            set
            {
                if (value == _name) return;
                _name = value;
                OnPropertyChanged();
            }
        }

        /// <summary>
        /// Mode of the gesture
        /// </summary>
        public GestureMode Mode
        {
            get { return _gestureMode; }
            set
            {
                if (value == _gestureMode) return;
                _gestureMode = value;
                OnPropertyChanged();
            }
        }

        /// <summary>
        /// Gesture active flag
        /// </summary>
        public bool Active
        {
            get { return _active; }
            set
            {
                if (value == _active) return;
                _active = value;
                OnPropertyChanged();
            }
        }

        private int _progress;

        /// <summary>
        /// Gesture progress flag - For continuous gestures
        /// </summary>
        public int Progress
        {
            get { return _progress; }
            set
            {
                if (value == _progress) return;
                _progress = value;
                OnPropertyChanged();
            }
        }

        private int _confidence;

        /// <summary>
        /// Gesture confidence values
        /// </summary>
        public int Confidence
        {
            get { return _confidence; }
            set
            {
                if (value == _confidence) return;
                _confidence = value;
                OnPropertyChanged();
            }
        }

        private int _count;

        /// <summary>
        /// Gesture count
        /// </summary>
        public int Count
        {
            get { return _count; }
            set
            {
                if (_count != value)
                {
                    _count = value;
                    var handler = GestureTriggered;
                    if (handler != null)
                    {
                        handler(this, new GestureArgs(this));
                    }
                }
            }
        }

        /// <summary>
        /// Dictionary containing the number of times this gesture is performed corresponding to each confidence level
        /// </summary>
        public Dictionary<GestureConfidenceLevels, GestureConfidenceData> ConfidenceDict
        {
            get { return _confidenceDict; }
        }

        /// <summary>
        /// Gesture triggered event
        /// </summary>
        public event EventHandler<GestureArgs> GestureTriggered;

        /// <summary>
        /// Property changed event
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