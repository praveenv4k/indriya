using Gemini.Framework.Commands;

namespace Experimot.Studio.Modules.WebBrowser.Commands
{
    [CommandDefinition]
    public class ViewBrowserCommandDefinition : CommandDefinition
    {
        public const string CommandName = "View.Home";

        public override string Name
        {
            get { return CommandName; }
        }

        public override string Text
        {
            get { return "Home"; }
        }

        public override string ToolTip
        {
            get { return "Home"; }
        }
    }
}