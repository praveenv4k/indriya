using System.ComponentModel.Composition;
using Caliburn.Micro;
using Experimot.Studio.Modules.FilterDesigner.ViewModels;
using Experimot.Studio.Modules.SampleBrowser;
using Gemini.Framework.Services;
using Gemini.Modules.Inspector;
using Gemini.Modules.Toolbox;

namespace Experimot.Studio.Modules.FilterDesigner
{
    [Export(typeof(ISample))]
    public class Sample : ISample
    {
        public string Name
        {
            get { return "Filter Designer"; }
        }

        public void Activate(IShell shell)
        {
            shell.OpenDocument(IoC.Get<GraphViewModel>());
            shell.ShowTool<IInspectorTool>();
            shell.ShowTool<IToolbox>();
        }
    }
}