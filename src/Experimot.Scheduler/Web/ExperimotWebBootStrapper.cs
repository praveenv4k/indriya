using Nancy;
using Nancy.Bootstrapper;
using Nancy.Conventions;
using Nancy.TinyIoc;

namespace Experimot.Scheduler.Web
{
    class ExperimotWebBootStrapper: DefaultNancyBootstrapper
    {
        protected override void ApplicationStartup(TinyIoCContainer container, IPipelines pipelines)
        {
            base.ApplicationStartup(container, pipelines);
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("files","Web/www/files"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("fonts", "Web/www/fonts"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("js", "Web/www/js"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("libs", "Web/www/libs"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("scenes", "Web/www/scenes"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("demo", "Web/www/demo"));
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("app", "Web/www/app"));
        }
    }
}
