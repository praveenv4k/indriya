using System;
using System.Windows.Media.Effects;

namespace ExperimotStudio.Modules.FilterDesigner.Util
{
    internal static class ShaderEffectUtility
    {
        public static PixelShader GetPixelShader(string name)
        {
            return new PixelShader
            {
                UriSource = new Uri(@"pack://application:,,,/Gemini.Demo;component/Modules/FilterDesigner/ShaderEffects/" + name + ".ps")
            };
        }
    }
}