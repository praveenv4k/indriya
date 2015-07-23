using CommandLine;

namespace Indriya.Kinect.Perception
{
    public class CommandLineOptions
    {
        [Option('n', "name", DefaultValue = "gesture_recognition", HelpText = "This is the name of the node!")]
        public string Name { get; set; }
        [Option('p', "param", DefaultValue = "tcp://localhost:5560", HelpText = "This is the address of parameter server!")]
        public string ParameterServer { get; set; }
    }
}