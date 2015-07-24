using System;
using System.Windows;
using Indriya.Application.Core;
using Indriya.Core.Schema;
using Nancy.TinyIoc;

namespace Indriya.Application
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : System.Windows.Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            const string configFile = "IndriyaConfig.xml";
            if (!string.IsNullOrEmpty(configFile))
            {
                var bootStrapper = new BootStrapper(configFile);
                RunTests(TinyIoCContainer.Current.Resolve<AppConfig>());
                bootStrapper.StartUp();
            }
            base.OnStartup(e);
        }

        protected override void OnExit(ExitEventArgs e)
        {
            var bootStrapper = TinyIoCContainer.Current.Resolve<BootStrapper>();
            if (bootStrapper != null)
            {
                bootStrapper.Shutdown();
            }
            base.OnExit(e);
        }

        private void RunTests(AppConfig config)
        {
            //Tests.Test.TestReadSkeletonFile();
            //Tests.Test.MultihumanGestureTest();
            //Tests.Test.CheckRelativeAngle();
            //Tests.Test.ExecuteParallel();
            //Tests.Test.TestVoiceCommandJson();
            //Tests.Test.TestSharpDxMatrixRotation();
            //Tests.Test.TestReadBehaviorXml(config);
            //Tests.Test.TestJson(JsonConvert.SerializeObject(config));
            //Tests.Test.TestProgramGeneration(config);
            //Tests.Test.TestJsonToProgram(config);
            //MainProgramUtil.ReadBehaviorXmlFile("complex_behavior.xml");
            //MainProgramUtil.ReadBehaviorXmlFile(@"C:\Work\Develop\sdk_2013\experimot\bin\scriptcs\behavior.xml");
            //Tests.Test.GestureConfidenceDataIterate();
        }
    }
}
