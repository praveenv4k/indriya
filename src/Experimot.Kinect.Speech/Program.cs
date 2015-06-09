using System;
using Microsoft.Speech.Recognition;

namespace Experimot.Core.Speech
{
    class Program
    {
        static void Main(string[] args)
        {
            //SpeechSynthesizer synth = new SpeechSynthesizer();
            //var voices = synth.GetInstalledVoices(new CultureInfo("en-US"));
            //if (voices != null)
            //{
                
            //}
            //PromptBuilder pb = new PromptBuilder();
            //pb.AppendText("Welcome, everyone");
            //synth.Speak(pb);
            //synth.Speak("This example speaks the text in a string.");
            var recognizers = SpeechRecognitionEngine.InstalledRecognizers();
            if (recognizers != null)
            {
                foreach (var recognizerInfo in recognizers)
                {
                    Console.WriteLine(recognizerInfo.Name);
                }
            }
        }
    }
}
