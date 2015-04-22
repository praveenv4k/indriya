using System;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using Common.Logging;
using Experimot.Core;
using Experimot.Scheduler.Annotations;
using Experimot.Scheduler.Tasks;
using Quartz;
using Quartz.Impl;
using Quartz.Impl.Matchers;

namespace Experimot.Scheduler
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, IJobListener, INotifyPropertyChanged
    {
        private readonly ISchedulerFactory _schedulerFactory;
        private readonly IScheduler _scheduler;
        private readonly Context _context;
        private static readonly ILog Log = LogManager.GetLogger(typeof (MainWindow));

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
        }

        public Context Context
        {
            get { return _context; }
        }

        private void MainWindow_Closing(object sender, CancelEventArgs e)
        {
            if (_scheduler != null)
            {
                var keys = _scheduler.GetJobKeys(GroupMatcher<JobKey>.GroupEquals("MainGroup"));
                if (keys != null && keys.Count > 0)
                {
                    _scheduler.DeleteJobs(keys.ToList());
                }
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
                        Log.Info("Job already active");
                    }
                }
            }
        }

        public void JobExecutionVetoed(IJobExecutionContext context)
        {
        }

        private bool color;
        private readonly BootStrapper _bootStrapper;

        public void JobToBeExecuted(IJobExecutionContext ctx)
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
                        textBox.AppendText(string.Format("About to execute task : {0}\n", ctx.JobDetail.Key));
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

        public void JobWasExecuted(IJobExecutionContext ctx, JobExecutionException jobException)
        {
            Dispatcher.Invoke(() =>
            {
                textBox.AppendText(string.Format("Finished to execute task : {0}\n", ctx.JobDetail.Key));

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
