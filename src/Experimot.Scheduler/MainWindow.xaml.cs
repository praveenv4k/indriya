using System;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using Experimot.Core;
using Experimot.Scheduler.Annotations;
using Quartz;
using Quartz.Impl;
using Quartz.Impl.Matchers;

namespace Experimot.Scheduler
{
    internal class JobListener : IJobListener
    {
        private MainWindow _window;

        public JobListener(MainWindow window)
        {
            _window = window;
        }

        public void JobExecutionVetoed(IJobExecutionContext context)
        {
            Console.WriteLine("About to execute task : {0}", context.Get("value"));
        }

        public void JobToBeExecuted(IJobExecutionContext context)
        {
            //_window.JobToBeExecuted(context);
            //Console.WriteLine(string.Format("About to execute task : {0}", context.JobDetail.Description));
        }

        public void JobWasExecuted(IJobExecutionContext context, JobExecutionException jobException)
        {
            Console.WriteLine("Finished to execute task : {0}", context.Get("value"));
            //_window.JobWasExecuted(context,jobException);
            //Console.WriteLine(string.Format("Finished to execute task : {0}", context.JobDetail.Description));
        }

        public string Name
        {
            get { return "JobListener"; }
        }
    }

    internal class SimpleTask : IJob
    {
        public void Execute(IJobExecutionContext context)
        {
            if (context != null)
            {
                //var message = string.Format("Hello world : {0}", context.JobDetail.Key);
                //Console.WriteLine(message);
                for (int i = 0; i < 10; i++)
                {
                    //message = string.Format("Am still executing : {0}", context.JobDetail.Key);
                    //Console.WriteLine(message);
                    Thread.Sleep(new TimeSpan(0, 0, 0, 0, 100));
                }
                context.Put("value", 2000);
            }
        }
    }

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, IJobListener, INotifyPropertyChanged
    {
        private ISchedulerFactory _schedulerFactory;
        private IScheduler _scheduler;
        private Context _context;
        //private DispatcherTimer _timer;
        private BackgroundWorker _worker;

        public MainWindow()
        {
            InitializeComponent();

            // our properties that enable XML configuration plugin
            // and makes it watch for changes every two minutes (120 seconds)
            var properties = new NameValueCollection();
            properties["quartz.plugin.triggHistory.type"] = "Quartz.Plugin.History.LoggingJobHistoryPlugin";

            properties["quartz.plugin.jobInitializer.type"] = "Quartz.Plugin.Xml.XMLSchedulingDataProcessorPlugin";
            properties["quartz.plugin.jobInitializer.fileNames"] = "quartz_config.xml";
            properties["quartz.plugin.jobInitializer.failOnFileNotFound"] = "true";
            //properties["quartz.plugin.jobInitializer.scanInterval"] = "120";

            _schedulerFactory = new StdSchedulerFactory(properties);
            _scheduler = _schedulerFactory.GetScheduler();

            Name = "ScheduleTest";
            _scheduler.ListenerManager.AddJobListener(new JobListener(this), GroupMatcher<JobKey>.AnyGroup());

            _scheduler.Start();
            
            const string configFile = "experimot_config.xml";
            if (!string.IsNullOrEmpty(configFile))
            {
                //_config = new experimot_config();
                var config = experimot_config.LoadFromFile(configFile);

                _context = new Context(_scheduler);

                _bootStrapper = new BootStrapper(config, _context);
                _bootStrapper.StartUp();
            }
            Closing += MainWindow_Closing;
            DataContext = this;

            //_timer = new DispatcherTimer();
            //_timer.Tick += _timer_Tick;
            //_timer.Interval = new TimeSpan(0, 0, 0, 10);

            //_timer.IsEnabled = true;
        }

        public Context Context
        {
            get { return _context; }
        }

        private void MainWindow_Closing(object sender, CancelEventArgs e)
        {
            if (_worker != null)
            {
                if (_worker.IsBusy)
                {
                    _worker.CancelAsync();
                }
            }
            if (_scheduler != null)
            {
                _scheduler.Shutdown();
            }
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
                    int id = int.Parse(tag.ToString());
                    string message = string.Format("I am task: {0}", id);
                    IJobDetail detail = JobBuilder.Create<SimpleTask>()
                        .WithIdentity(string.Format("Task{0}", id), "MainGroup")
                        .Build();
                    ITrigger trigger = TriggerBuilder.Create().ForJob(detail).StartNow().Build();

                    if (!_scheduler.CheckExists(detail.Key))
                    {
                        _scheduler.ScheduleJob(detail, trigger);
                    }
                    else
                    {
                        Console.WriteLine("Job already active");
                    }
                }
            }
        }



        public void JobExecutionVetoed(IJobExecutionContext context)
        {
        }

        private bool color;
        private readonly BootStrapper _bootStrapper;

        public void JobToBeExecuted(IJobExecutionContext context)
        {
            try
            {
                Dispatcher.Invoke(() =>
                {
                    try
                    {
                        if (color) button1.Background = new SolidColorBrush(Colors.Green);
                        else button1.Background = new SolidColorBrush(Colors.Red);
                        color = !color;
                        textBox.AppendText(string.Format("About to execute task : {0}\n", context.JobDetail.Key));
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine(ex.Message);
                    }
                });
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
            }
        }

        public void JobWasExecuted(IJobExecutionContext context, JobExecutionException jobException)
        {
            Dispatcher.Invoke(() =>
            {
                textBox.AppendText(string.Format("Finished to execute task : {0}\n", context.JobDetail.Key));

            });
        }


        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
