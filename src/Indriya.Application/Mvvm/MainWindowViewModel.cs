using System.Collections.ObjectModel;
using System.Windows.Controls;
using Indriya.Core.Data;
using Nancy.TinyIoc;

namespace Indriya.Application.Mvvm
{
    public class MainWindowViewModel
    {
        private BrowserTabViewModel _browserTabViewModel;

        public MainWindowViewModel()
        {
            //TabViewModel = new BrowserTabViewModel("http://localhost:8888");
            Documents = new ObservableCollection<BrowserTabViewModel> {new BrowserTabViewModel("http://localhost:8888"){Title = "ÏndriyaWeb",ContentId = "IndriyaWeb_Content"}};
            //Anchorables = new ObservableCollection<Context>();
            //Anchorables.Add(TinyIoCContainer.Current.Resolve<Context>());
        }

        //public ObservableCollection<Context> Anchorables { get; set; }

        public ObservableCollection<BrowserTabViewModel> Documents { get; set; }

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