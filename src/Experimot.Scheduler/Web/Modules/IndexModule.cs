using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using Common.Logging;
using Nancy;
using Nancy.TinyIoc;
using Newtonsoft.Json;

namespace Experimot.Scheduler.Web.Modules
{
    public class TestModel
    {
        public String Name { get; set; }
        public int Id { get; set; }
    }

    class IndexVal
    {
        public IndexVal()
        {
            val = new List<double>(25);
        }
        public int id { get; set; }
        public List<double> val { get; set; }
    }

    public class IndexModule : NancyModule
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof (IndexModule));
        private const string WebRoot = @"C:\Work\Develop\src\github\ExPeriMot\src\Experimot.Web\www";
        public IndexModule()
        {
            //Get["/"] = parameters => Response.AsFile(@"Web/www/index.html");
            //Get["/"] = parameters => Response.AsFile(Path.Combine(WebRoot, "index.html"));
            Get["/"] = parameters => Response.AsFile("index.html");

            Get["/req"] = parameters => Response.AsJson(new TestModel {Name = "Hello", Id = 1000});

            Get["/models/{type}/(?<all>.*)"] = parameters =>
            {
                Console.WriteLine(Request.Path);
                //return Response.AsFile(System.IO.Path.Combine("Web/www" + Request.Path));
                return Response.AsFile(Path.Combine(WebRoot, Request.Path));
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

            Get["/jointvals"] = parameters =>
            {
                try
                {
                    var dict = new Dictionary<int, int>()
                    {
                            {0,1},
                            {1,0},
                            {2,9},
                            {3,8},
                            {4,7},
                            {5,10},
                            {6,2},
                            {7,3},
                            {8,11},
                            {9,12},
                            {10,5},
                            {11,4},
                            {12,13},
                            {13,6},
                            {14,20},
                            {15,19},
                            {16,21},
                            {17,14},
                            {18,15},
                            {19,22},
                            {20,23},
                            {21,17},
                            {22,16},
                            {23,24},
                            {24,18},
                    };
                    var lines = System.IO.File.ReadAllLines(@"datalog.csv");
                    var csv = lines.Select(line => line.Split(',')).ToList(); // or, List<YourClass>
                    var jointList = new List<List<double>>();
                    for (int i = 0; i < csv.Count; i++)
                    {  
                        if(i == 0) continue;
                        //var list = new IndexVal() {id = i + 1};
                        var list = new List<double>();
                        for (int j = 4; j < 29; j++)
                        {
                            list.Add(double.Parse(csv[i][dict[j - 4]+4]));
                        }
                        jointList.Add(list);
                    }
                    string json = JsonConvert.SerializeObject(jointList);
                    //return StreamResponse(() => new MemoryStream(Encoding.UTF8.GetBytes(json ?? "")), "application/json");
                    var resp = new Response()
                    {
                        ContentType = "application/json",
                        Contents = s => {
                                    var bytes = Encoding.UTF8.GetBytes(json);
                                        s.Write(bytes, 0, bytes.Length);
                                }
                    };
                    ////application/json
                    return resp;
                }
                catch (Exception ex)
                {
                    Log.InfoFormat("Exception occured while GET jointvals : {0}", ex.Message);
                }
                return (Response)HttpStatusCode.OK;
            };
        }
    }
}
