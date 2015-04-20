using System;
using System.Net;
using System.Net.Sockets;
using Experimot.Core;
using Experimot.Core.Util;
using Experimot.Scheduler.Web.Controllers;
using Experimot.Scheduler.Web.Handlers;
using uhttpsharp;
using uhttpsharp.Handlers;
using uhttpsharp.Handlers.Compression;
using uhttpsharp.Listeners;
using uhttpsharp.ModelBinders;
using uhttpsharp.RequestProviders;

namespace Experimot.Scheduler.Web
{
    public class ExperimotServer : IDisposable
    {
        private HttpServer _server;

        public ExperimotServer(experimot_config config)
        {
            _config = config;
        }

        public void Start()
        {
            if (_server != null || _config==null)
            {
                return;
            }
            var port = ParameterUtil.Get(_config.parameters, "WebServerPort", 8080);
            _server = new HttpServer(new HttpRequestProvider());
            //_server.Use(new TcpListenerAdapter(new TcpListener(IPAddress.Any, port)));
            _server.Use(new TcpListenerAdapter(new TcpListener(IPAddress.Loopback, port)));

            //httpServer.Use(new SessionHandler<DateTime>(() => DateTime.Now));
            
            _server.Use(new ExceptionHandler());
            _server.Use(new CompressionHandler(DeflateCompressor.Default, GZipCompressor.Default));
            //_server.Use(new ControllerHandler(new BaseController(), new JsonModelBinder(), new JsonView()));

            _server.Use(new HttpRouter().With(string.Empty, new IndexHandler())
                .With("about", new AboutHandler())
                .With("Assets", new AboutHandler())
                .With("strings", new RestHandler<string>(new StringsRestController(), JsonResponseProvider.Default)));

            //_server.Use(new ClassRouter(new MySuperHandler()));
            //_server.Use(new TimingHandler());

            //_server.Use(new MyHandler());
            
            _server.Use(new FileHandler());
            _server.Use(new ErrorHandler());
            _server.Use((context, next) =>
            {
                Console.WriteLine(@"Got Request!");
                return next();
            });

            _server.Start();
            Console.ReadLine();
        }

        public void Stop()
        {
            if (_server != null)
            {
                _server.Dispose();
                _server = null;
            }
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        private bool _disposed;
        // Protected implementation of Dispose pattern. 
        protected virtual void Dispose(bool disposing)
        {
            if (_disposed)
                return;

            if (disposing)
            {
            }

            Stop();

            _disposed = true;
        }

        private readonly experimot_config _config;
    }
}