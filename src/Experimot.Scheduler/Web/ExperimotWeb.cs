using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Common.Logging;
using Experimot.Core;

namespace Experimot.Scheduler.Web
{
    class ExperimotWeb: IDisposable
    {
        private bool _disposed;
        private static readonly ILog Log = LogManager.GetLogger(typeof (ExperimotWeb));
        private readonly Nancy.Hosting.Self.NancyHost _host;

        public ExperimotWeb(experimot_config config)
        {
            
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        public void Start()
        {
            
        }

        public void Stop()
        {
            

        }

        // Protected implementation of Dispose pattern. 
        protected virtual void Dispose(bool disposing)
        {
            if (_disposed)
                return;

            if (disposing)
            {
            }

            Stop();

            _disposed = true;
        }
    }
}
