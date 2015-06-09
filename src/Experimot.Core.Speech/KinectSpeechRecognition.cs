using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Common.Logging;
using Microsoft.Kinect;
using Microsoft.Speech.AudioFormat;
using Microsoft.Speech.Recognition;

namespace Experimot.Core.Speech
{
    internal class KinectSpeechRecognition
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
        private const double ConfidenceThreshold = 0.3;

        // Number of degrees in a right angle.
        private const int DegreesInRightAngle = 90;

        // Number of pixels turtle should move forwards or backwards each time.
        private const int DisplacementAmount = 60;


        public bool Initialize(string grammarFile)
        {
            try
            {
                if (_kinectSensor == null && !string.IsNullOrEmpty(grammarFile))
                {
                    _kinectSensor = KinectSensor.GetDefault();
                    if (_kinectSensor != null)
                    {
                        // open the sensor
                        _kinectSensor.Open();

                        // grab the audio stream
                        IReadOnlyList<AudioBeam> audioBeamList = _kinectSensor.AudioSource.AudioBeams;
                        System.IO.Stream audioStream = audioBeamList[0].OpenInputStream();

                        // create the convert stream
                        _convertStream = new KinectAudioStream(audioStream);

                        var ri = TryGetKinectRecognizer();

                        if (ri != null)
                        {
                            // Create instance of the speech engine
                            _speechEngine = new SpeechRecognitionEngine(ri.Id);

                            // Load the grammar file
                            var g = new Grammar(grammarFile);
                            _speechEngine.LoadGrammar(g);

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
            if (e.Result.Confidence >= ConfidenceThreshold)
            {
                Console.WriteLine(e.Result.Semantics.Value.ToString());
            }
        }

        public void Terminate()
        {
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
        }

        public static RecognizerInfo TryGetKinectRecognizer()
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
                        "en-US".Equals(recognizer.Culture.Name, StringComparison.OrdinalIgnoreCase))
                    {
                        return recognizer;
                    }
                }
            }
            return null;
        }
    }
}
