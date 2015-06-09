using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Speech.Recognition;

namespace Experimot.Core.Speech
{
    class Program
    {
        static void Main(string[] args)
        {
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
