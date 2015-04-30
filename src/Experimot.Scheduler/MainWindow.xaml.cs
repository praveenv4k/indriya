using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Windows.Controls;
using Common.Logging;
using experimot.msgs;
using Experimot.Scheduler.Annotations;
using Experimot.Scheduler.Data;
using Nancy.TinyIoc;

namespace Experimot.Scheduler
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof (MainWindow));

        public MainWindow()
        {
            const string configFile = "experimot_config.xml";
            if (!string.IsNullOrEmpty(configFile))
            {
                _bootStrapper = new BootStrapper(configFile);
                _bootStrapper.StartUp();
            }
            DataContext = Context;
            InitializeComponent();
            Closing += MainWindow_Closing;
        }

        public Context Context
        {
            get
            {
                var ctx = TinyIoCContainer.Current.Resolve<Context>();
                return ctx;
            }
        }

        private void MainWindow_Closing(object sender, CancelEventArgs e)
        {
            if (_bootStrapper != null)
            {
                _bootStrapper.Shutdown();
            }
        }

        private readonly BootStrapper _bootStrapper;

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }

        private int prev = 7;
        private void ButtonBase_OnClick(object sender, RoutedEventArgs e)
        {
            if (Context != null)
            {
                Context.Humans.Add(new Data.Human(prev, Context.MotionModules)
                {
                    Body = new KinectBody() { TrackingId = prev++}
                });
            }
        }
    }
}
