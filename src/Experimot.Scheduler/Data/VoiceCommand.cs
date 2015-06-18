using System;
using System.ComponentModel;
using System.Globalization;
using System.Runtime.CompilerServices;
using experimot.msgs;
using Experimot.Scheduler.Annotations;

namespace Experimot.Scheduler.Data
{
    public class VoiceCommand: INotifyPropertyChanged
    {
        private string _command;
        private bool _active;
        private int _confidence;
        private string _language;
        private DateTime _triggerAt;

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

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }
    }

    public class VoiceCommandManager: INotifyPropertyChanged
    {
        private VoiceCommand _previous;
        private VoiceCommand _current;

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

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}