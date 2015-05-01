using Nancy;
using Nancy.Bootstrapper;
using Nancy.Conventions;
using Nancy.TinyIoc;

namespace Experimot.Scheduler.Web
{
    public class ExperimotRootPathProvider : IRootPathProvider
    {
        //private const string WebRoot = @"C:\Work\Develop\src\github\ExPeriMot\src\Experimot.Web\www";
        private const string WebRoot = @"../../src/Experimot.Web/www/";
        public string GetRootPath()
        {
            return WebRoot;
        }
    }

    internal class ExperimotWebBootStrapper : DefaultNancyBootstrapper
    {
        private const string WebRoot = @"../../src/Experimot.Web/www/";

        protected override void ApplicationStartup(TinyIoCContainer container, IPipelines pipelines)
        {
            base.ApplicationStartup(container, pipelines);

            //string[] folders = { "files", "fonts", "js", "libs", "scenes", "demo", "app" };
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

            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("files", "../../src/Experimot.Web/www/files"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("fonts", "../../src/Experimot.Web/www/fonts"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("js", "../../src/Experimot.Web/www/js"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("libs", "../../src/Experimot.Web/www/libs"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("scenes", "../../src/Experimot.Web/www/scenes"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("demo", "../../src/Experimot.Web/www/demo"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("app", "../../src/Experimot.Web/www/app"));
        }

        protected override IRootPathProvider RootPathProvider
        {
            get { return new ExperimotRootPathProvider(); }
        }
    }
}
