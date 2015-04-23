using System;
using System.Collections.ObjectModel;
using Nancy;

namespace Experimot.Scheduler.Web.Modules
{
    public class AnotherModel
    {
        public string Name { get; set; }
        public int Id { get; set; }
    }

    public class TestModel
    {
        public TestModel()
        {
            Children = new ObservableCollection<AnotherModel>
            {
                new AnotherModel() {Name = "Praveen", Id = 1},
                new AnotherModel() {Name = "Krishna", Id = 2}
            };
        }

        public String Name { get; set; }
        public int Id { get; set; }
        public ObservableCollection<AnotherModel> Children { get; set; }
    }

    public class IndexModule : NancyModule
    {
        public IndexModule()
        {
            //Get["/"] = parameters => View["index", this.Request.Url];
            Get["/"] = parameters => Response.AsFile(@"index.html");

            Get["/testing"] = parameters => View["staticview", Request.Url];

            Get["/req"] = parameters => Response.AsJson(new TestModel {Name = "Hello", Id = 1000});

            //Get["/models/collada/nao.dae"] = parameters =>
            Get["/models/{type}/(?<all>.*)"] = parameters =>
            {
                Console.WriteLine(Request.Path);
                return Response.AsFile(System.IO.Path.Combine("www" + Request.Path));
            };
        }
    }
}
