using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web.UI;
using Common.Logging;
using Nancy;

namespace Experimot.Scheduler.Web.Modules
{
    internal class DesignerModule : NancyModule
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof (DesignerModule));

        public DesignerModule()
        {
            Post["/designer/program/start"] = parameters =>
            {
                Log.InfoFormat("POST  : {0}", Request.Url);
                return (Response) HttpStatusCode.OK;
            };
            Post["/designer/program/stop"] = parameters =>
            {
                Log.InfoFormat("POST  : {0}", Request.Url);
                return (Response) HttpStatusCode.OK;
            };
            Post["/designer/program/code"] = parameters =>
            {
                Log.InfoFormat("POST  : {0}", Request.Url);
                Log.InfoFormat("Code  : {0}", Request.Body);
                return (Response) HttpStatusCode.OK;
            };
        }
    }
}
