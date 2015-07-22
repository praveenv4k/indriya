using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using experimot.msgs;
using Experimot.Core;

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
