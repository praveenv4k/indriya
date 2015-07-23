using System;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Common.Logging;
using Indriya.Core.Msgs;
using Indriya.Core.Util;
using Microsoft.Speech.Recognition;

namespace Indriya.Kinect.Speech
{
    internal class StandardSpeechRecognition: ISpeechRecognitionModule
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof (StandardSpeechRecognition));

        /// <summary>
        /// Speech recognition engine using audio data from Kinect.
        /// </summary>
        private SpeechRecognitionEngine _speechEngine;

        // Speech utterance confidence below which we treat speech as if it hadn't been heard
        private readonly double _confidenceThreshold = 0.6;

        // Number of degrees in a right angle.
        private readonly int _degreesInRightAngle = 90;

        // Number of pixels turtle should move forwards or backwards each time.
        private readonly int _displacementAmount = 60;

        //private readonly string _grammarFile = "SpeechGrammar.xml";
        private readonly string _grammarFileBase = "SpeechGrammar";
        private readonly string _grammarFile = "SpeechGrammar_en-US.xml";
        private readonly string _language = "Japanese";

        private readonly VoiceCommandPublisher _voiceCommandPublisher;
        private readonly string _culture = "en-US";
        private readonly string _fallbackLanguage = "English";
        private readonly string _fallbackCulture = "en-US";
        private readonly string _dateTimeFormatString = "yyyy/MM/dd HH:mm:ss.fff";
        private SpeechCommand _speechCommand;
        private Task _speechCommandTask;

        public StandardSpeechRecognition(Node node)
        {
            if (node != null)
            {
                
                //<param key="ConfidenceThreshold" type="double" value="0.60"/>
                //<param key="DegreesInRightAngle" type="int" value="90"/>
                //<param key="DisplacementAmount" type="int" value="60"/>
                //<param key="GrammarFileBase" type="string" value="SpeechGrammar"/>
                //<param key="Language" type="string" value="Japanese"/>
                //<param key="Culture" type="string" value="ja-JP"/>
                //<param key="FallbackLanguage" type="string" value="English"/>
                //<param key="FallbackCulture" type="string" value="en-US"/>

                _confidenceThreshold = ParameterUtil.Get(node.param, "ConfidenceThreshold", _confidenceThreshold);
                _degreesInRightAngle = ParameterUtil.Get(node.param, "DegreesInRightAngle", _degreesInRightAngle);
                _displacementAmount = ParameterUtil.Get(node.param, "DisplacementAmount", _displacementAmount);
                _grammarFileBase = ParameterUtil.Get(node.param, "GrammarFileBase", _grammarFileBase);
                _language = ParameterUtil.Get(node.param, "Language", _language);
                _culture = ParameterUtil.Get(node.param, "Culture", _culture);
                _fallbackLanguage = ParameterUtil.Get(node.param, "FallbackLanguage", _fallbackLanguage);
                _fallbackCulture = ParameterUtil.Get(node.param, "FallbackCulture", _fallbackCulture);
                _dateTimeFormatString = ParameterUtil.Get(node.param, "DateTimeFormatString", _dateTimeFormatString);
                _grammarFile = string.Concat(_grammarFileBase, "_", _culture, ".xml");

                if (node.publisher != null)
                {
                    var vcp = node.publisher.FirstOrDefault(s => s.msg_type == "VoiceCommandDescription");
                    if (vcp != null)
                    {
                        _voiceCommandPublisher = new VoiceCommandPublisher(vcp.host, vcp.port, vcp.topic);
                        Console.WriteLine(@"Created Voice command publisher : {0}, {1}, {2}", vcp.host, vcp.port, vcp.topic);
                    }
                }
            }
            if (_voiceCommandPublisher == null)
            {
                Console.WriteLine(@"Node info null");
                _voiceCommandPublisher = new VoiceCommandPublisher();
            }
        }

        public bool Initialize()
        {
            try
            {
                if (!string.IsNullOrEmpty(_grammarFile) && File.Exists(_grammarFile))
                {
                    _speechEngine = new SpeechRecognitionEngine();

                    Console.WriteLine("Speech Engine created");

                    // Load the grammar file
                    var g = new Grammar(_grammarFile);
                    _speechEngine.LoadGrammar(g);

                    Console.WriteLine("Loaded Grammar File : {0}", _grammarFile);

                    // Subscribe to events
                    _speechEngine.SpeechRecognized += SpeechRecognized;
                    _speechEngine.SpeechRecognitionRejected += SpeechRejected;

                    _speechEngine.SetInputToDefaultAudioDevice();
                    _speechEngine.RecognizeAsync(RecognizeMode.Multiple);

                    if (_voiceCommandPublisher != null)
                    {
                        _voiceCommandPublisher.Initialize();
                    }

                    _speechCommand = new SpeechCommand(_voiceCommandPublisher);
                    _speechCommandTask = Task.Factory.StartNew(() => _speechCommand.Run(100));

                    Console.WriteLine("Started recognizing");
                }
            }
            catch (Exception ex)
            {
                Log.Error(ex.Message);
                Log.Error(ex.StackTrace);
            }
            return false;
        }

        private void SpeechRejected(object sender, SpeechRecognitionRejectedEventArgs e)
        {
        }

        private void SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {
            Console.WriteLine("Speech recognized: {0}", e.Result.Confidence);
            if (e.Result.Confidence >= _confidenceThreshold)
            {
                var value = string.Format(new CultureInfo(_culture), "{0}", e.Result.Semantics.Value);
                Console.WriteLine(value);
                if (_voiceCommandPublisher != null)
                {
                    Console.WriteLine("Publishing recognized voice command: {0}", e.Result.Confidence);
                    if (_speechCommand != null)
                    {
                        _speechCommand.Update(new VoiceCommandDescription
                        {
                            active = true,
                            command = value,
                            confidence = (int) (e.Result.Confidence*100),
                            language = _language,
                            triggeredAt = DateTime.Now.ToString(_dateTimeFormatString)
                        });
                    }
                }
            }
        }

        public void Terminate()
        {
            if (_speechCommand != null)
            {
                _speechCommand.Stop = true;
            }
            if (_speechCommandTask != null)
            {
                _speechCommandTask.Wait();
            }
            if (_voiceCommandPublisher != null)
            {
                _voiceCommandPublisher.Terminate();
            }

            if (_speechEngine != null)
            {
                _speechEngine.SpeechRecognized -= SpeechRecognized;
                _speechEngine.SpeechRecognitionRejected -= SpeechRejected;
                _speechEngine.RecognizeAsyncStop();
            }
            Console.WriteLine("Kinect Speech Recognition terminated");
        }

        // TODO Audio Body Correlation
    }
}
