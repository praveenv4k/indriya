using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace ExperimotPerception
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        //private JointStatePublisher _jStatePub;
        private KinectBodyPublisher _kBodyPub;

        public MainWindow()
        {
            _kBodyPub = new KinectBodyPublisher();
            this.DataContext = _kBodyPub;

            InitializeComponent();
            this.Loaded += MainWindow_Loaded;
            this.Closing += MainWindow_Closing;
            
            //_jStatePub = new JointStatePublisher();
        }

        void MainWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            _kBodyPub.Terminate();
            //if (_jStatePub != null)
            //{
            //    _jStatePub.Terminate();
            //}
        }

        void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            _kBodyPub.Initialize();
            //_jStatePub.Initialize();
        }
    }
}
