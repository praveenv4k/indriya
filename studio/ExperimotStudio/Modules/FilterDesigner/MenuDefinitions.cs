using System.ComponentModel.Composition;
using ExperimotStudio.Modules.FilterDesigner.Commands;
using Gemini.Framework.Menus;

namespace ExperimotStudio.Modules.FilterDesigner
{
    public static class MenuDefinitions
    {
        [Export]
        public static MenuItemDefinition OpenGraphMenuItem = new CommandMenuItemDefinition<OpenGraphCommandDefinition>(
            Gemini.Modules.MainMenu.MenuDefinitions.FileNewOpenMenuGroup, 2);
    }
}