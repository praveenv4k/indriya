using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Web.Configuration;
using experimot.msgs;
using Experimot.Core.Annotations;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace Experimot.Scheduler.Data
{
    public enum GestureMode
    {
        None = 0,
        Discrete = 1,
        Continuous = 2
    }

    [ExpandableObject]
    public class GestureModule : INotifyPropertyChanged
    {
        private string _name;
        public event PropertyChangedEventHandler PropertyChanged;

        [Annotations.NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }

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

        [ExpandableObject]
        public ObservableCollection<Gesture> Gestures
        {
            get { return _gestures; }
        }

        private readonly ObservableCollection<Gesture> _gestures;

        public GestureModule(experimot.msgs.GestureRecognitionModule module)
        {
            _gestures = new ObservableCollection<Gesture>();
            if (module != null)
            {
                Name = module.name;
                foreach (var gestureDescription in module.motions)
                {
                    _gestures.Add(new Gesture()
                    {
                        Name = gestureDescription.name,
                        Mode = (GestureMode) gestureDescription.type
                    });
                }
            }
        }
    }

    public enum GestureConfidenceLevels
    {
        Low = 75,
        Average = 80,
        Good = 85,
        Better = 90,
        Best = 95
    }

    public struct GestureConfidenceData
    {
        public int CurrentActiveLapse;
        public int Count;

        public void Update(bool active, int gesturePeriod)
        {
            if (active)
            {
                CurrentActiveLapse++;
                if (CurrentActiveLapse >= gesturePeriod)
                {
                    Count++;
                }
            }
            else
            {

            }
        }
    }

    public class Gesture : INotifyPropertyChanged
    {
        private string _name;
        private GestureMode _gestureMode;
        private bool _active;
        private Dictionary<GestureConfidenceLevels, GestureConfidenceData> _confidenceDict;
        protected const int GesturePeriod = 10;
        private int _currentLapse;


        public static Gesture Default(string name, GestureMode mode)
        {
            return new Gesture()
            {
                _currentLapse = 0,
                Name = name,
                Mode = mode,
                Active = false,
                Confidence = 0,
                Count = 0,
                Progress = 0,
                _confidenceDict = new Dictionary<GestureConfidenceLevels, GestureConfidenceData>()
                {
                    {GestureConfidenceLevels.Low, new GestureConfidenceData()},
                    {GestureConfidenceLevels.Average, new GestureConfidenceData()},
                    {GestureConfidenceLevels.Good, new GestureConfidenceData()},
                    {GestureConfidenceLevels.Better, new GestureConfidenceData()},
                    {GestureConfidenceLevels.Best, new GestureConfidenceData()},
                }
            };
        }

        private bool IsActive(int confidence, GestureConfidenceLevels level)
        {
            return confidence >= (int) level;
        }

        private void UpdateConfidenceLevels(int confidence, int currentLapse)
        {
            if (currentLapse > GesturePeriod)
            {
                foreach (var gestureConfidenceData in _confidenceDict)
                {
                    
                }
            }
            else
            {
                
            }
        }

        public void Refresh(GestureDescription trigger)
        {
            if (trigger != null)
            {
                Name = trigger.name;
                Mode = (GestureMode) trigger.type;
                Active = trigger.active;
                Confidence = trigger.confidence;
                Progress = trigger.progress;
                _currentLapse++;

                UpdateConfidenceLevels(Confidence,_currentLapse);
            }
        }

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

        public event EventHandler<GestureArgs> GestureTriggered;

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }
    }



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