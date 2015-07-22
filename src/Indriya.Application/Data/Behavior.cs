using System.ComponentModel;
using System.Runtime.CompilerServices;
using Experimot.Core.Annotations;

namespace Experimot.Scheduler.Data
{
    /// <summary>
    /// Represents a robot behavior
    /// </summary>
    public class Behavior : INotifyPropertyChanged
    {
        /// <summary>
        /// Property changed event handler
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// Name of the behavior
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
        /// Behavior Mode
        /// </summary>
        public BehaviorMode Mode
        {
            get { return _behaviorMode; }
            set
            {
                if (value == _behaviorMode) return;
                _behaviorMode = value;
                OnPropertyChanged();
            }
        }

        /// <summary>
        /// Current state of the behavior execution
        /// </summary>
        public BehaviorState State
        {
            get { return _state; }
            set
            {
                if (value == _state) return;
                _state = value;
                OnPropertyChanged();
            }
        }

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }

        private string _name;
        private BehaviorMode _behaviorMode;
        private BehaviorState _state;
    }
}