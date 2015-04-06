using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Xml;
using System.Xml.Serialization;
using Common.Logging;
using IronPython.Hosting;
using Microsoft.Scripting.Hosting;

namespace Scheduler
{
    internal class BootStrapper
    {
        private readonly experimot_config _config;
        private bool _startup;
        private bool _shutdown;
        private ILog Log = LogManager.GetLogger(typeof (BootStrapper));
        private const string PYTHONPATH = @"C:\Python27";
        private readonly IList<Process> _processes; 

        public BootStrapper(string configFile)
        {
            _processes = new List<Process>();

            if (!string.IsNullOrEmpty(configFile))
            {
                using (var reader = XmlReader.Create(configFile))
                {
                    var serializer = new XmlSerializer(typeof (experimot_config));
                    var obj = serializer.Deserialize(reader);
                    _config = obj as experimot_config;
                }
            }
        }

        public void StartUp()
        {
            if (!_startup && _config != null)
            {
                foreach (var node in _config.nodes)
                {
                    if (node != null && node.process != null)
                    {
                        var exeFile = Environment.ExpandEnvironmentVariables(node.process.path);
                        if (!string.IsNullOrEmpty(exeFile))
                        {

                            if (node.process.type == "python")
                            {
                                bool ironPython = false;
                                if (ironPython)
                                {
                                    var ipy = Python.CreateEngine();
                                    if (ipy != null)
                                    {
                                        var scope = ipy.CreateScope();
                                        var paths = ipy.GetSearchPaths();
                                        Console.WriteLine("Path count: {0}", paths.Count);

                                        //var searchPaths =
                                        //    new List<string>()
                                        //    {
                                        //        System.IO.Path.Combine(PYTHONPATH),
                                        //        System.IO.Path.Combine(PYTHONPATH, "Lib"),
                                        //        System.IO.Path.Combine(PYTHONPATH, "DLLs"),
                                        //        System.IO.Path.Combine(PYTHONPATH, "Lib", "site-packages"),
                                        //        System.IO.Path.Combine(PYTHONPATH, "Lib", "site-packages", "google",
                                        //            "protobuf"),
                                        //        System.IO.Path.Combine(PYTHONPATH, "Lib", "site-packages", "google"),
                                        //        System.IO.Path.GetDirectoryName(exeFile)
                                        //    };

                                        var searchPaths =
                                            new List<string>()
                                            {
                                                "C:\\Python27\\lib\\site-packages\\protobuf-3.0.0a1-py2.7.egg",
                                                "C:\\Work\\Develop\\sdk_2013\\openrave\\lib\\site-packages\\openravepy",
                                                "C:\\windows\\SYSTEM32\\python27.zip",
                                                "C:\\Python27\\DLLs",
                                                "C:\\Python27\\lib",
                                                "C:\\Python27\\lib\\plat-win",
                                                "C:\\Python27\\lib\\lib-tk",
                                                "C:\\Python27",
                                                "C:\\Python27\\lib\\site-packages",
                                                @"C:\Python27\Lib\site-packages\zmq",
                                                System.IO.Path.GetDirectoryName(exeFile)
                                            };

                                        foreach (var path in searchPaths)
                                        {
                                            paths.Add(path);
                                        }

                                        ipy.SetSearchPaths(paths);
                                        ipy.ExecuteFile(exeFile, scope);
                                    }
                                }
                                else
                                {
                                    var myProcess = new Process
                                    {
                                        StartInfo =
                                        {
                                            UseShellExecute = true,
                                            FileName = "python.exe",
                                            CreateNoWindow = true,
                                            Arguments = exeFile
                                        }
                                    };
                                    myProcess.Start();
                                }
                            }
                            else
                            {
                                try
                                {
                                    var workingDir = System.IO.Path.GetDirectoryName(exeFile);
                                    var myProcess = new Process
                                    {
                                        StartInfo =
                                        {
                                            UseShellExecute = true,
                                            FileName = exeFile,
                                            CreateNoWindow = true,
                                            Arguments = node.process.args,
                                            WorkingDirectory = workingDir ?? string.Empty
                                        }
                                    };
                                    myProcess.Start();
                                    Log.InfoFormat("Started Process : {0}", exeFile);
                                    _processes.Add(myProcess);
                                }
                                catch (Exception ex)
                                {
                                    Log.ErrorFormat("Process: {0}, Message: {1}",exeFile, ex.Message);
                                }
                            }
                        }
                    }
                }
                _startup = true;
            }
        }

        public void Shutdown()
        {
            if (!_shutdown)
            {
                //TODO Shutdown here
                _shutdown = true;
            }
        }

        public experimot_config Config
        {
            get { return _config; }
        }
    }
}
