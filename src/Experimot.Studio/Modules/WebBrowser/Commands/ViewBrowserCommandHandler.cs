using System.ComponentModel.Composition;
using System.Threading.Tasks;
using Caliburn.Micro;
using Experimot.Studio.Modules.WebBrowser.ViewModels;
using Gemini.Framework;
using Gemini.Framework.Commands;
using Gemini.Framework.Services;
using Gemini.Framework.Threading;

namespace Experimot.Studio.Modules.WebBrowser.Commands
{
    [CommandHandler]
    public class ViewBrowserCommandHandler : CommandHandlerBase<ViewBrowserCommandDefinition>
    {
        private readonly IShell _shell;

        [ImportingConstructor]
        public ViewBrowserCommandHandler(IShell shell)
        {
            _shell = shell;
        }

        public override Task Run(Command command)
        {
            _shell.OpenDocument((IDocument) IoC.GetInstance(typeof(WebBrowserViewModel), null));
            return TaskUtility.Completed;
        }
    }
}