using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using Experimot.Studio.Modules.FilterDesigner.ShaderEffects;
using Gemini.Modules.Toolbox;

namespace Experimot.Studio.Modules.FilterDesigner.ViewModels.Elements
{
    [ToolboxItem(typeof(GraphViewModel), "Robot", "Robot", "pack://application:,,,/Modules/FilterDesigner/Resources/nao.png")]
    public class Robot : DynamicElement
    {
        public Robot() : base()
        {
            AddInputConnector("Trigger", Colors.DarkSeaGreen);
        }

       
        protected override void Draw(DrawingContext drawingContext, Rect bounds)
        {
            drawingContext.DrawRectangle(new SolidColorBrush(Colors.Wheat), null, bounds);
        }
    }
}