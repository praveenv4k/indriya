using System;
using System.Windows;
using Common.Logging;
using experimot.msgs;

namespace Experimot.Kinect.Perception
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow2 : Window
    {
        private readonly Node _node;
        //private JointStatePublisher _jStatePub;
        private readonly KinectBodyPublisher _kBodyPub;
        private readonly ILog Log = LogManager.GetLogger<MainWindow2>();

        public MainWindow2()
        {
            InitializeComponent();
        }

        public MainWindow2(experimot.msgs.Node node) : this()
        {
            _node = node;
            if (_node != null)
            {
                if (node.publisher != null)
                {
                    foreach (var item in node.publisher)
                    {
                        if (item.msg_type == "KinectBodies")
                        {
                            _kBodyPub = new KinectBodyPublisher(item.host, item.port, item.topic);
                            DataContext = _kBodyPub;
                            Loaded += MainWindow_Loaded;
                            Closing += MainWindow_Closing;
                        }
                        Log.Info("Gesture recognition node initialized from the config file");
                    }
                }
            }
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
