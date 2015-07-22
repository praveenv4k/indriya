using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows;
using Experimot.Scheduler.Annotations;
using Experimot.Scheduler.Data;
using Experimot.Scheduler.Mvvm;
using Nancy.TinyIoc;

namespace Experimot.Scheduler
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    // ReSharper disable once RedundantExtendsListEntry
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
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

        private void ProgramExecution(ExecutionRequest req)
        {
            var bootStrapper = TinyIoCContainer.Current.Resolve<BootStrapper>();
            if (bootStrapper != null)
            {
                bootStrapper.MainProgramExecutionRequest(req);
            }
        }

        private void ProgramRun(object sender, RoutedEventArgs e)
        {
            ProgramExecution(ExecutionRequest.Start);
        }

        private void ProgramStop(object sender, RoutedEventArgs e)
        {
            ProgramExecution(ExecutionRequest.Stop);
        }
    }
}
