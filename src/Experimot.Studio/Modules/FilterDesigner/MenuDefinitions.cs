using System.ComponentModel.Composition;
using Experimot.Studio.Modules.FilterDesigner.Commands;
using Gemini.Framework.Menus;

namespace Experimot.Studio.Modules.FilterDesigner
{
    public static class MenuDefinitions
    {
        [Export]
        public static MenuItemDefinition OpenGraphMenuItem = new CommandMenuItemDefinition<OpenGraphCommandDefinition>(
            Gemini.Modules.MainMenu.MenuDefinitions.FileNewOpenMenuGroup, 2);
    }
}