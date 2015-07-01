using System;
using System.Windows;
using Experimot.Core;
using Nancy.TinyIoc;

namespace Experimot.Scheduler
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            const string configFile = "experimot_config.xml";
            if (!string.IsNullOrEmpty(configFile))
            {
                var bootStrapper = new BootStrapper(configFile);
                RunTests(TinyIoCContainer.Current.Resolve<experimot_config>());
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

        private void RunTests(experimot_config config)
        {
            Tests.Test.CheckRelativeAngle();
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
