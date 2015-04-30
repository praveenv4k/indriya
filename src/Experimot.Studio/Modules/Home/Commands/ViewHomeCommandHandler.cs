using System.ComponentModel.Composition;
using System.Threading.Tasks;
using Caliburn.Micro;
using Experimot.Studio.Modules.Home.ViewModels;
using Gemini.Framework;
using Gemini.Framework.Commands;
using Gemini.Framework.Services;
using Gemini.Framework.Threading;

namespace Experimot.Studio.Modules.Home.Commands
{
    [CommandHandler]
    public class ViewHomeCommandHandler : CommandHandlerBase<ViewHomeCommandDefinition>
    {
        private readonly IShell _shell;

        [ImportingConstructor]
        public ViewHomeCommandHandler(IShell shell)
        {
            _shell = shell;
        }

        public override Task Run(Command command)
        {
            _shell.OpenDocument((IDocument) IoC.GetInstance(typeof(HomeViewModel), null));
            return TaskUtility.Completed;
        }
    }
}