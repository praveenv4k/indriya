using System;
using System.Web;

namespace ExperimotWeb
{
    /// <summary>
    /// Summary description for HandlerFactory
    /// </summary>
    class HandlerFactory : IHttpHandlerFactory
    {
        public IHttpHandler GetHandler(HttpContext context,
            string requestType, String url, String pathTranslated)
        {
            IHttpHandler handlerToReturn;
            if ("get" == context.Request.RequestType.ToLower())
            {
                if (context.Request.Url.AbsolutePath.Contains(".dae"))
                {
                    handlerToReturn = new DaeRequestHandler(pathTranslated);
                }
                else
                {
                    handlerToReturn = new DefaultHttpHandler();
                }
            }
            else if ("post" == context.Request.RequestType.ToLower())
            {
                //handlerToReturn = new HelloWorldAsyncHandler();
                handlerToReturn = null;
            }

            else
            {
                handlerToReturn = null;
            }
            return handlerToReturn;
        }

        public void ReleaseHandler(IHttpHandler handler)
        {
        }

        public bool IsReusable
        {
            get
            {
                return false;
            }
        }
    }
}