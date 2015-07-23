using Indriya.Core.Msgs;

namespace Indriya.Kinect.Speech
{
    class SpeechCommand
    {
        private readonly VoiceCommandPublisher _vcp;
        private readonly object _object = new object();
        private readonly VoiceCommandDescription _command;
        public volatile bool Stop = false;

        public SpeechCommand(VoiceCommandPublisher vcp)
        {
            _vcp = vcp;
            _command = new VoiceCommandDescription();
        }

        public void Run(object interval)
        {
            int value = 100;
            int.TryParse(interval.ToString(), out value);
            if (_vcp != null)
            {
                while (!Stop)
                {
                    lock (_object)
                    {
                        if (IsValid(_command))
                        {
                            _vcp.Update(_command);
                        }
                    }
                    System.Threading.Thread.Sleep(value);
                }
            }
        }

        public void Update(VoiceCommandDescription command)
        {
            lock (_object)
            {
                _command.active = command.active;
                _command.command = command.command;
                _command.confidence = command.confidence;
                _command.language = command.language;
                _command.triggeredAt = command.triggeredAt;
            }
        }

        public bool IsValid(VoiceCommandDescription command)
        {
            return !string.IsNullOrEmpty(command.command) &&
                   !string.IsNullOrEmpty(command.triggeredAt);
        }
    }
}
