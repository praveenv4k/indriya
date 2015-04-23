using Nancy;
using Nancy.Bootstrapper;
using Nancy.Conventions;
using Nancy.TinyIoc;

namespace NancyFx
{
    class ExperimotWebBootStrapper: DefaultNancyBootstrapper
    {
        protected override void ApplicationStartup(TinyIoCContainer container, IPipelines pipelines)
        {
            base.ApplicationStartup(container, pipelines);
            Conventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("www"));
        }
    }
}
