using System;

namespace Experimot.Scheduler.Data
{
    public class VoiceCommand
    {
        public string Command { get; set; }
        public bool Active { get; set; }
        public int Confidence { get; set; }
        public string Language { get; set; }
        public DateTime TriggerAt { get; set; }
    }

    public class VoiceCommandManager
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
            set { _previous = value; }
        }

        public VoiceCommand Current
        {
            get { return _current; }
            set { _current = value; }
        }

        public void Update(VoiceCommand command)
        {
            if (command != null)
            {
                if (_current != null)
                {
                    _previous = _current;
                }
                _current = command;
                _current.TriggerAt = DateTime.Now;
                if (_previous == null)
                {
                    _previous = command;
                }
            }
        }
    }
}