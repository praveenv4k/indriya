using Microsoft.Speech.Synthesis;

namespace Experimot.Kinect.Speech
{
    internal class SpeechSynthesis
    {
        public static void Test()
        {
            SpeechSynthesizer synth = new SpeechSynthesizer();
            PromptBuilder pb = new PromptBuilder();
            pb.AppendText("Welcome, everyone");
            synth.Speak(pb);
        }
    }
}
