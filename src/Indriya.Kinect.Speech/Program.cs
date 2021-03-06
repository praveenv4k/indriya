﻿using System;
using System.IO;
using System.Text;
using System.Threading.Tasks;
using CommandLine;
using Indriya.Core.Msgs;
using Indriya.Core.Util;
using NetMQ;
using ProtoBuf;

namespace Indriya.Kinect.Speech
{
    internal class CommandLineOptions
    {
        [Option('n', "name", DefaultValue = "speech_recognition", HelpText = "This is the name of the node!")]
        public string Name { get; set; }

        [Option('p', "param", DefaultValue = "tcp://localhost:5560",
            HelpText = "This is the address of parameter server!")]
        public string ParameterServer { get; set; }
    }

    internal class Program
    {
        private static volatile bool _stopRecognizer;

        private static void Main(string[] args)
        {
            Console.OutputEncoding = Encoding.Unicode;
            var str = "あかい";
            Console.WriteLine(str);

            Node info = null;
            try
            {
                if (args.Length > 0)
                {
                    var options = new CommandLineOptions();
                    Parser.Default.ParseArguments(args, options);
                    info = MessageUtil.RequestProtoMessage<Node>(options.ParameterServer, options.Name);

                    if (info != null)
                    {
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Retrieving the parameter from server failed : {0}", ex.StackTrace);
            }
            var task = Task.Factory.StartNew(() => RunRecognizer(info));
            Console.WriteLine("Press any key to stop the recognizer.");
            Console.Read();
            _stopRecognizer = true;
            task.Wait();
            Console.WriteLine("About to exit. Press enter to close the console window.");
            Console.Read();
        }

        private static void RunRecognizer(object nodeArg)
        {
            var nodeInfo = nodeArg as Node;
            if (nodeInfo != null)
            {
                var module = ParameterUtil.Get(nodeInfo.param, "RecognitionModule", "KinectSpeechRecognition");
                ISpeechRecognitionModule recognizer = null;
                if (module == "KinectSpeechRecognition")
                {
                    recognizer = new KinectSpeechRecognition(nodeInfo);
                    recognizer.Initialize();
                }
                else
                {
                    recognizer = new StandardSpeechRecognition(nodeInfo);
                    recognizer.Initialize();
                }
                while (!_stopRecognizer)
                {

                }
                recognizer.Terminate();
            }
        }
    }
}
