using System;
using Quartz;

namespace Experimot.Scheduler.Tasks
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
}