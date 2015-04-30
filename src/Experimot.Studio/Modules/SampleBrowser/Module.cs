using System.ComponentModel.Composition;
using Caliburn.Micro;
using Experimot.Studio.Modules.SampleBrowser.ViewModels;
using Gemini.Framework;

namespace Experimot.Studio.Modules.SampleBrowser
{
    [Export(typeof(IModule))]
    public class Module : ModuleBase
    {
        public override void PostInitialize()
        {
            Shell.OpenDocument(IoC.Get<SampleBrowserViewModel>());
        }
    }
}