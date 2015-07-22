using System;
using System.ComponentModel;
using System.Globalization;
using System.Runtime.CompilerServices;
using experimot.msgs;
using Experimot.Scheduler.Annotations;

namespace Experimot.Scheduler.Data
{
    /// <summary>
    /// Voice command manager
    /// </summary>
    public class VoiceCommandManager: INotifyPropertyChanged
    {
        private VoiceCommand _previous;
        private VoiceCommand _current;

        /// <summary>
        /// Constructor
        /// </summary>
        public VoiceCommandManager()
        {
            _previous = new VoiceCommand()
            {
                TriggerAt = DateTime.Now
            };
            _current = new VoiceCommand()
            {
                TriggerAt = DateTime.Now
            };
        }

        /// <summary>
        /// Previous voice command
        /// </summary>
        public VoiceCommand Previous
        {
            get { return _previous; }
            set
            {
                if (Equals(value, _previous)) return;
                _previous = value;
                OnPropertyChanged();
            }
        }

        /// <summary>
        /// Current voice command
        /// </summary>
        public VoiceCommand Current
        {
            get { return _current; }
            set
            {
                if (Equals(value, _current)) return;
                _current = value;
                OnPropertyChanged();
            }
        }

        /// <summary>
        /// Update the voice commands with the voice command description message sent by speech recognition modules
        /// </summary>
        /// <param name="command">Command description</param>
        public void Update(VoiceCommandDescription command)
        {
            if (command != null)
            {
                if (_current != null)
                {
                    _previous = _current;
                }
                else
                {
                    _current = new VoiceCommand();
                }

                if (_previous == null)
                {
                    _previous = new VoiceCommand
                    {
                        Active = command.active,
                        Command = command.command,
                        Confidence = command.confidence,
                        Language = command.language,
                        TriggerAt = FromString(command.triggeredAt)
                    };
                }

                _current.Active = command.active;
                _current.Command = command.command;
                _current.Confidence = command.confidence;
                _current.Language = command.language;
                _current.TriggerAt = FromString(command.triggeredAt);
            }
        }

        /// <summary>
        /// Convert string (yyyy/MM/dd HH:mm:ss.fff) to DataTime
        /// </summary>
        /// <param name="dateTimeStr"></param>
        /// <returns></returns>
        public static DateTime FromString(string dateTimeStr)
        {
            try
            {
                if (!string.IsNullOrEmpty(dateTimeStr))
                {
                    return DateTime.ParseExact(dateTimeStr, "yyyy/MM/dd HH:mm:ss.fff", CultureInfo.InvariantCulture);
                }
            }
            catch (Exception ex)
            {
                // ignored
            }
            return DateTime.Now;
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