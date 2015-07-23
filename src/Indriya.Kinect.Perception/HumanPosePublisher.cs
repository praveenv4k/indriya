using Indriya.Core;
using Indriya.Core.Msgs;

namespace Indriya.Kinect.Perception
{
    /// <summary>
    /// Interaction logic for MainWindow
    /// </summary>
    public class HumanPosePublisher : MessagePublisher<Humans>
    {
        /// <summary>
        /// Initializes a new instance of the MainWindow class.
        /// </summary>
        public HumanPosePublisher()
            : this("tcp://*", 5571, "HPP")
        {
        }

        /// <summary>
        /// Initializes a new instance of the MainWindow class.
        /// </summary>
        public HumanPosePublisher(string host, uint port, string topic) : base(host, port, topic)
        {
        }

        /// <summary>
        /// Check if the instance of human is valid
        /// </summary>
        /// <param name="msg"></param>
        /// <returns></returns>
        protected override bool IsValid(Humans msg)
        {
            return msg != null && msg.human.Count > 0;
        }
    }
}
