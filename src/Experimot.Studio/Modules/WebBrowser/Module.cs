using System.Collections.Generic;
using System.ComponentModel.Composition;
using Caliburn.Micro;
using Experimot.Studio.Modules.WebBrowser.Commands;
using Experimot.Studio.Modules.WebBrowser.ViewModels;
using Gemini.Framework;
using Gemini.Framework.Menus;
using Gemini.Modules.PropertyGrid;

namespace Experimot.Studio.Modules.WebBrowser
{
	[Export(typeof(IModule))]
	public class Module : ModuleBase
	{
        [Export]
        public static MenuItemGroupDefinition ViewDemoMenuGroup = new MenuItemGroupDefinition(
            Gemini.Modules.MainMenu.MenuDefinitions.ViewMenu, 10);

        [Export]
	    public static MenuItemDefinition ViewHomeMenuItem = new CommandMenuItemDefinition<ViewBrowserCommandDefinition>(
            ViewDemoMenuGroup, 0);

        public override IEnumerable<IDocument> DefaultDocuments
	    {
	        get
	        {
                yield return IoC.Get<WebBrowserViewModel>();
            }
	    }

        public override void PostInitialize()
        {
            IoC.Get<IPropertyGrid>().SelectedObject = IoC.Get<WebBrowserViewModel>();
            Shell.OpenDocument(IoC.Get<WebBrowserViewModel>());
        }
	}
}