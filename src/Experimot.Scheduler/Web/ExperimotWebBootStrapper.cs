using Nancy;
using Nancy.Bootstrapper;
using Nancy.Conventions;
using Nancy.TinyIoc;

namespace Experimot.Scheduler.Web
{
    public class ExperimotRootPathProvider : IRootPathProvider
    {
        private const string WebRoot = @"C:/Work/Develop/src/github/ExPeriMot/src/Experimot.Web/www";
        //private const string WebRoot = @"../../src/Experimot.Web/www/";
        public string GetRootPath()
        {
            return WebRoot;
        }
    }

    internal class ExperimotWebBootStrapper : DefaultNancyBootstrapper
    {
        private const string WebRoot = @"C:/Work/Develop/src/github/ExPeriMot/src/Experimot.Web/www";

        protected override void ApplicationStartup(TinyIoCContainer container, IPipelines pipelines)
        {
            base.ApplicationStartup(container, pipelines);

            //string[] folders = { "files", "fonts", "js", "libs", "../libs", "scenes", "demo", "app" };
            //foreach (var folder in folders)
            //{
            //    Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory(folder,
            //        System.IO.Path.Combine(WebRoot, folder)));
            //}

            //Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("files","Web/www/files"));
            //Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("fonts", "Web/www/fonts"));
            //Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("js", "Web/www/js"));
            //Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("libs", "Web/www/libs"));
            //Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("scenes", "Web/www/scenes"));
            //Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("demo", "Web/www/demo"));
            //Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("app", "Web/www/app"));

            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("files", @"C:/Work/Develop/src/github/ExPeriMot/src/Experimot.Web/www/files"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("fonts", @"C:/Work/Develop/src/github/ExPeriMot/src/Experimot.Web/www/fonts"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("js", @"C:/Work/Develop/src/github/ExPeriMot/src/Experimot.Web/www/js"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("libs", @"C:/Work/Develop/src/github/ExPeriMot/src/Experimot.Web/www/libs"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("../libs", @"C:/Work/Develop/src/github/ExPeriMot/src/Experimot.Web/www/libs"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("scenes", @"C:/Work/Develop/src/github/ExPeriMot/src/Experimot.Web/www/scenes"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("demo", @"C:/Work/Develop/src/github/ExPeriMot/src/Experimot.Web/www/demo"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("app", @"C:/Work/Develop/src/github/ExPeriMot/src/Experimot.Web/www/app"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("data", @"C:/Work/Develop/src/github/ExPeriMot/src/Experimot.Web/www/data"));
        }

        protected override IRootPathProvider RootPathProvider
        {
            get { return new ExperimotRootPathProvider(); }
        }
    }
}
