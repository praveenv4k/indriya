using Experimot.Core;
using Indriya.Core.Msgs;

namespace Experimot.Kinect.Speech
{
    internal class VoiceCommandPublisher : MessagePublisher<VoiceCommandDescription>
    {
        public VoiceCommandPublisher(string host, uint port, string topic) : base(host, port, topic)
        {
            SendFrequency = 0;
        }

        public VoiceCommandPublisher()
            : this("tcp://*", 5593, "VRP")
        {
            SendFrequency = 0;
        }
    }
}
