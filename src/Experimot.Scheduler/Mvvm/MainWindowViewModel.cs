using Experimot.Scheduler.Data;
using Nancy.TinyIoc;

namespace Experimot.Scheduler.Mvvm
{
    public class MainWindowViewModel
    {
        private BrowserTabViewModel _browserTabViewModel;

        public MainWindowViewModel()
        {
            TabViewModel = new BrowserTabViewModel("http://localhost:8888");
        }

        public BrowserTabViewModel TabViewModel
        {
            get { return _browserTabViewModel; }
            set { _browserTabViewModel = value; }
        }

        public Context Context
        {
            get { return TinyIoCContainer.Current.Resolve<Context>(); }
        }
    }
}