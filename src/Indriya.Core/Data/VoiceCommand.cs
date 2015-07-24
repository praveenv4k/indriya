using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using Indriya.Core.Properties;

namespace Indriya.Core.Data
{
    /// <summary>
    /// Represents a voice command
    /// </summary>
    public class VoiceCommand: INotifyPropertyChanged
    {
        private string _command;
        private bool _active;
        private int _confidence;
        private string _language;
        private DateTime _triggerAt;

        /// <summary>
        /// Command information
        /// </summary>
        public string Command
        {
            get { return _command; }
            set
            {
                if (value == _command) return;
                _command = value;
                OnPropertyChanged();
            }
        }

        /// <summary>
        /// Flag to tell if the voice command is active
        /// </summary>
        public bool Active
        {
            get { return _active; }
            set
            {
                if (value.Equals(_active)) return;
                _active = value;
                OnPropertyChanged();
            }
        }

        /// <summary>
        /// Voice command confidence value
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

        /// <summary>
        /// Language
        /// </summary>
        public string Language
        {
            get { return _language; }
            set
            {
                if (value == _language) return;
                _language = value;
                OnPropertyChanged();
            }
        }

        /// <summary>
        /// Time at which the command is triggered
        /// </summary>
        public DateTime TriggerAt
        {
            get { return _triggerAt; }
            set
            {
                if (value.Equals(_triggerAt)) return;
                _triggerAt = value;
                OnPropertyChanged();
            }
        }

        /// <summary>
        /// Property changed event handler
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