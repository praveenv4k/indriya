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

namespace Sample
{
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
                var message = string.Format("Hello world : {0}", context.JobDetail.Key);
                System.Diagnostics.Debug.WriteLine(message);
                for (int i = 0; i < 10; i++)
                {
                    message = string.Format("Am still executing : {0}", context.JobDetail.Key);
                    System.Diagnostics.Debug.WriteLine(message);
                    System.Threading.Thread.Sleep(new TimeSpan(0, 0, 0, 0, 100));
                }
            }
        }
    }

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private ISchedulerFactory _schedulerFactory;
        private IScheduler _scheduler;
        public MainWindow()
        {
            InitializeComponent();
            _schedulerFactory = new StdSchedulerFactory();
            _scheduler = _schedulerFactory.GetScheduler();
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
                        System.Diagnostics.Debug.WriteLine("Job already active");
                    }
                }
            }
        }


    }
}
