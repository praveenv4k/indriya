using System;
using System.Threading;
using Quartz;

namespace Experimot.Scheduler.Tasks
{
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
}