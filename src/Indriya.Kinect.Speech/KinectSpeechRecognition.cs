using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using Common.Logging;
using experimot.msgs;
using Experimot.Core.Util;
using Microsoft.Kinect;
using Microsoft.Speech.AudioFormat;
using Microsoft.Speech.Recognition;

namespace Experimot.Kinect.Speech
{
    internal class KinectSpeechRecognition:ISpeechRecognitionModule
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof (KinectSpeechRecognition));

        /// <summary>
        /// Active Kinect sensor.
        /// </summary>
        private KinectSensor _kinectSensor;

        /// <summary>
        /// Stream for 32b-16b conversion.
        /// </summary>
        private KinectAudioStream _convertStream;

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

        public KinectSpeechRecognition(Node node)
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
                if (_kinectSensor == null && !string.IsNullOrEmpty(_grammarFile) && System.IO.File.Exists(_grammarFile))
                {
                    _kinectSensor = KinectSensor.GetDefault();
                    if (_kinectSensor != null)
                    {
                        // open the sensor
                        _kinectSensor.Open();

                        Console.WriteLine("Sensor Opened");

                        // grab the audio stream
                        IReadOnlyList<AudioBeam> audioBeamList = _kinectSensor.AudioSource.AudioBeams;
                        System.IO.Stream audioStream = audioBeamList[0].OpenInputStream();

                        // create the convert stream
                        _convertStream = new KinectAudioStream(audioStream);

                        Console.WriteLine("Stream created");

                        var ri = TryGetKinectRecognizer();

                        if (ri != null)
                        {
                            Console.WriteLine("Kinect recognizer exists");
                            // Create instance of the speech engine
                            _speechEngine = new SpeechRecognitionEngine(ri.Id);

                            Console.WriteLine("Speech Engine created");

                            // Load the grammar file
                            var g = new Grammar(_grammarFile);
                            _speechEngine.LoadGrammar(g);

                            Console.WriteLine("Loaded Grammar File : {0}", _grammarFile);

                            // Subscribe to events
                            _speechEngine.SpeechRecognized += SpeechRecognized;
                            _speechEngine.SpeechRecognitionRejected += SpeechRejected;

                            // let the convertStream know speech is going active
                            _convertStream.SpeechActive = true;

                            // For long recognition sessions (a few hours or more), it may be beneficial to turn off adaptation of the acoustic model. 
                            // This will prevent recognition accuracy from degrading over time.
                            ////speechEngine.UpdateRecognizerSetting("AdaptationOn", 0);

                            _speechEngine.SetInputToAudioStream(
                                _convertStream,
                                new SpeechAudioFormatInfo(EncodingFormat.Pcm, 16000, 16, 1, 32000, 2, null));
                            _speechEngine.RecognizeAsync(RecognizeMode.Multiple);

                            if (_voiceCommandPublisher != null)
                            {
                                _voiceCommandPublisher.Initialize();
                            }

                            _speechCommand = new SpeechCommand(_voiceCommandPublisher);
                            _speechCommandTask = Task.Factory.StartNew(() => _speechCommand.Run(200));

                            Console.WriteLine("Started recognizing");
                        }
                    }
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
                    //_voiceCommandPublisher.Update(new VoiceCommandDescription
                    //{
                    //    active = true,
                    //    command = value,
                    //    confidence = (int) (e.Result.Confidence*100),
                    //    language = _language,
                    //    triggeredAt = DateTime.Now.ToString(_dateTimeFormatString)
                    //});
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

            if (_convertStream != null)
            {
                _convertStream.SpeechActive = false;
            }

            if (_speechEngine != null)
            {
                _speechEngine.SpeechRecognized -= SpeechRecognized;
                _speechEngine.SpeechRecognitionRejected -= SpeechRejected;
                _speechEngine.RecognizeAsyncStop();
            }

            if (_kinectSensor != null)
            {
                _kinectSensor.Close();
                _kinectSensor = null;
            }
            Console.WriteLine("Kinect Speech Recognition terminated");
        }

        public RecognizerInfo TryGetKinectRecognizer()
        {
            IEnumerable<RecognizerInfo> recognizers = null;

            // This is required to catch the case when an expected recognizer is not installed.
            // By default - the x86 Speech Runtime is always expected. 
            try
            {
                recognizers = SpeechRecognitionEngine.InstalledRecognizers();
            }
            catch (COMException ex)
            {
                Log.ErrorFormat("Error retrieving installed recognizers : {0}", ex.StackTrace);
            }

            if (recognizers != null)
            {
                foreach (var recognizer in recognizers)
                {
                    string value;
                    recognizer.AdditionalInfo.TryGetValue("Kinect", out value);
                    if ("True".Equals(value, StringComparison.OrdinalIgnoreCase) &&
                        _culture.Equals(recognizer.Culture.Name, StringComparison.OrdinalIgnoreCase))
                    {
                        return recognizer;
                    }
                }
            }
            return null;
        }

        // TODO Audio Body Correlation
    }
}
