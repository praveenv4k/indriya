using System;

namespace Indriya.Application.Web
{
    public static class IndriyaWebRootPath
    {
        private const string WebRoot = @"C:/Work/Develop/src/github/indriya/src/Indriya.Web/www";

        public static string GetRootPath()
        {
            string root = string.Empty;
            try
            {
                root = Environment.GetEnvironmentVariable("INDRIYA_WEB_ROOT");
                if (string.IsNullOrEmpty(root))
                {
                    root = WebRoot;
                }
            }
            catch (Exception ex)
            {
                if (string.IsNullOrEmpty(root))
                {
                    root = WebRoot;
                }
            }
            return root;
        }
    }
}