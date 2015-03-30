using System.ComponentModel.Composition;
using Caliburn.Micro;
using ExperimotStudio.Modules.SampleBrowser;
using ExperimotStudio.Modules.SharpDXSceneViewer.ViewModels;
using Gemini.Framework.Services;

namespace ExperimotStudio.Modules.SharpDXSceneViewer
{
    [Export(typeof(ISample))]
    public class Sample : ISample
    {
        public string Name
        {
            get { return "SharpDX"; }
        }

        public void Activate(IShell shell)
        {
            shell.OpenDocument(IoC.Get<SceneViewModel>());
        }
    }
}