using System;
using Common.Logging;
using Quartz;

namespace Experimot.Scheduler.Tasks
{
    internal class JobListenerImpl : IJobListener
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof (JobListenerImpl));

        public void JobExecutionVetoed(IJobExecutionContext context)
        {
            Log.InfoFormat("About to execute task : {0}", context.JobDetail.Key);
        }

        public void JobToBeExecuted(IJobExecutionContext context)
        {
        }

        public void JobWasExecuted(IJobExecutionContext context, JobExecutionException jobException)
        {
            Log.InfoFormat("Finished to execute task : {0}", context.JobDetail.Key);
        }

        public string Name
        {
            get { return "JobListenerImpl"; }
        }
    }
}