using Gemini.Framework.Services;

namespace Experimot.Studio.Modules.SampleBrowser
{
    public interface ISample
    {
        string Name { get; }
        void Activate(IShell shell);
    }
}