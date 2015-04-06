using System.ComponentModel.Composition;
using Caliburn.Micro;
using ExperimotStudio.Modules.FilterDesigner.ViewModels;
using ExperimotStudio.Modules.SampleBrowser;
using Gemini.Framework.Services;
using Gemini.Modules.Inspector;
using Gemini.Modules.Toolbox;

namespace ExperimotStudio.Modules.FilterDesigner
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