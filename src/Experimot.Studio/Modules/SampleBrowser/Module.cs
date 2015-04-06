using System.ComponentModel.Composition;
using Caliburn.Micro;
using ExperimotStudio.Modules.SampleBrowser.ViewModels;
using Gemini.Framework;

namespace ExperimotStudio.Modules.SampleBrowser
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