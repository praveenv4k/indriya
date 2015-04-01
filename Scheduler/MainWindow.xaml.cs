using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Quartz;
using Quartz.Impl;
using System.Collections.Specialized;
using Quartz.Impl.Matchers;

namespace Scheduler
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
            Console.WriteLine(string.Format("About to execute task : {0}", context.Get("value").ToString()));
        }

        public void JobToBeExecuted(IJobExecutionContext context)
        {
            //_window.JobToBeExecuted(context);
            //Console.WriteLine(string.Format("About to execute task : {0}", context.JobDetail.Description));
        }

        public void JobWasExecuted(IJobExecutionContext context, JobExecutionException jobException)
        {
            Console.WriteLine(string.Format("Finished to execute task : {0}", context.Get("value").ToString()));
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
        //private string _message;
        //public SimpleTask(string message)
        //{
        //    _message = message;
        //}

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
                    System.Threading.Thread.Sleep(new TimeSpan(0, 0, 0, 0, 100));
                }
                context.Put("value", 2000);
            }
        }
    }

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, IJobListener
    {
        private ISchedulerFactory _schedulerFactory;
        private IScheduler _scheduler;
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

            this.Name = "ScheduleTest";
            _scheduler.ListenerManager.AddJobListener(new JobListener(this), GroupMatcher<JobKey>.AnyGroup());

            _scheduler.Start();

            this.Closing += MainWindow_Closing;
        }

        void MainWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (_scheduler != null)
            {
                _scheduler.Shutdown();
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

        bool color = false;
        public void JobToBeExecuted(IJobExecutionContext context)
        {
            try
            {
                this.Dispatcher.Invoke((Action)(() =>
                {
                    try
                    {
                        if (color) this.button1.Background = new SolidColorBrush(Colors.Green);
                        else this.button1.Background = new SolidColorBrush(Colors.Red);
                        color = !color;
                        this.textBox.AppendText(string.Format("About to execute task : {0}\n", context.JobDetail.Key));
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine(ex.Message);
                    }
                }));
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.Message);
            }
        }

        public void JobWasExecuted(IJobExecutionContext context, JobExecutionException jobException)
        {
            this.Dispatcher.Invoke((Action)(() =>
            {
                this.textBox.AppendText(string.Format("Finished to execute task : {0}\n", context.JobDetail.Key));

            }));
        }

        
    }
}
