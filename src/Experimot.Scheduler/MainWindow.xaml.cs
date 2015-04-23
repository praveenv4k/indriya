using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Windows.Controls;
using Common.Logging;
using Experimot.Scheduler.Annotations;
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
            InitializeComponent();
            const string configFile = "experimot_config.xml";
            if (!string.IsNullOrEmpty(configFile))
            {
                _bootStrapper = new BootStrapper(configFile);
                _bootStrapper.StartUp();
            }
            Closing += MainWindow_Closing;
            DataContext = this;
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

        private void ClickButton(object sender, RoutedEventArgs e)
        {
            var btn = sender as Button;
            if (btn != null)
            {
                var tag = btn.Tag;
                if (tag != null)
                {
                }
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
    }
}
