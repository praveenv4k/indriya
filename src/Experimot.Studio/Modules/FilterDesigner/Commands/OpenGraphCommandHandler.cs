using System.ComponentModel.Composition;
using System.Threading.Tasks;
using Caliburn.Micro;
using Experimot.Studio.Modules.FilterDesigner.ViewModels;
using Gemini.Framework.Commands;
using Gemini.Framework.Services;
using Gemini.Framework.Threading;
using Gemini.Modules.Inspector;

namespace Experimot.Studio.Modules.FilterDesigner.Commands
{
    [CommandHandler]
    public class OpenGraphCommandHandler : CommandHandlerBase<OpenGraphCommandDefinition>
    {
        private readonly IShell _shell;

        [ImportingConstructor]
        public OpenGraphCommandHandler(IShell shell)
        {
            _shell = shell;
        }

        public override Task Run(Command command)
        {
            _shell.OpenDocument(new GraphViewModel(IoC.Get<IInspectorTool>()));
            return TaskUtility.Completed;
        }
    }
}