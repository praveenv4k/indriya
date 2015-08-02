using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows;
using CefSharp;
using Common.Logging;
using Indriya.Application.Properties;
using Indriya.Application.Mvvm;

namespace Indriya.Application
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    // ReSharper disable once RedundantExtendsListEntry
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        private static readonly ILog Log = LogManager.GetLogger<MainWindow>();
        public MainWindow()
        {
            DataContext = new MainWindowViewModel();
            InitializeComponent();
        }
        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }

        private void BrowserOnConsoleMessage(object sender, ConsoleMessageEventArgs e)
        {
            Log.InfoFormat("Browser message - [Line: {0}, Source: {1}] : , Message: {2}", e.Line, e.Source, e.Message);
        }
    }
}
