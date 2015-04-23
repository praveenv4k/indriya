using System;
using Common.Logging;
using Nancy;
using Nancy.TinyIoc;

namespace Experimot.Scheduler.Web.Modules
{
    public class TestModel
    {
        public String Name { get; set; }
        public int Id { get; set; }
    }

    public class IndexModule : NancyModule
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof (IndexModule));

        public IndexModule()
        {
            Get["/"] = parameters => Response.AsFile(@"Web/www/index.html");

            Get["/req"] = parameters => Response.AsJson(new TestModel {Name = "Hello", Id = 1000});

            Get["/models/{type}/(?<all>.*)"] = parameters =>
            {
                Console.WriteLine(Request.Path);
                return Response.AsFile(System.IO.Path.Combine("Web/www" + Request.Path));
            };

            Get["/context"] = parameters =>
            {
                try
                {
                    var context = TinyIoCContainer.Current.Resolve<Context>();
                    if (context != null)
                    {
                        return Response.AsJson(context);
                    }
                }
                catch (Exception ex)
                {
                    Log.InfoFormat("Exception occured while GET context : {0}", ex.Message);
                }
                return (Response) HttpStatusCode.OK;
            };
        }
    }
}
