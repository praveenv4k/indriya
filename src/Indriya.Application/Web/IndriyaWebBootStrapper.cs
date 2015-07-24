using Nancy;
using Nancy.Bootstrapper;
using Nancy.Conventions;
using Nancy.TinyIoc;

namespace Indriya.Application.Web
{
    internal class IndriyaWebBootStrapper : DefaultNancyBootstrapper
    {
        protected override void ApplicationStartup(TinyIoCContainer container, IPipelines pipelines)
        {
            base.ApplicationStartup(container, pipelines);

            var root = IndriyaWebRootPath.GetRootPath();
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("files",
                System.IO.Path.Combine(root, "files")));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("fonts",
                System.IO.Path.Combine(root, "fonts")));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("js",
                System.IO.Path.Combine(root, "js")));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("libs",
                System.IO.Path.Combine(root, "libs")));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("../libs",
                System.IO.Path.Combine(root, "libs")));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("scenes",
                System.IO.Path.Combine(root, "scenes")));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("demo",
                System.IO.Path.Combine(root, "demo")));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("app",
                System.IO.Path.Combine(root, "app")));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("data",
                System.IO.Path.Combine(root, "data")));
        }

        protected override IRootPathProvider RootPathProvider
        {
            get { return new IndriyaWebRootPathProvider(); }
        }
    }
}
