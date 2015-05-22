using System.Windows;
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
    }
}
