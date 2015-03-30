using Gemini.Framework.Services;

namespace ExperimotStudio.Modules.SampleBrowser
{
    public interface ISample
    {
        string Name { get; }
        void Activate(IShell shell);
    }
}