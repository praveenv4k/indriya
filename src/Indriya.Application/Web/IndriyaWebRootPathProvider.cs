using Nancy;

namespace Indriya.Application.Web
{
    public class IndriyaWebRootPathProvider : IRootPathProvider
    {
        public string GetRootPath()
        {
            return IndriyaWebRootPath.GetRootPath();
        }
    }
}