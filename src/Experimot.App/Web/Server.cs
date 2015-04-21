using System;
using System.Collections.Concurrent;
using System.Globalization;
using System.Threading.Tasks;
using uhttpsharp;
using uhttpsharp.Handlers;
using uhttpsharp.ModelBinders;

namespace Experimot.Scheduler.Web
{
    public class MySuperHandler : IHttpRequestHandler
    {
        private int _index;

        public MySuperHandler Child
        {
            get
            {
                _index++;
                return this;
            }
        }

        public Task Handle(IHttpContext context, Func<Task> next)
        {
            context.Response = HttpResponse.CreateWithMessage(HttpResponseCode.Ok, "Hello!" + _index, true);
            return Task.Factory.GetCompleted();
        }


        [Indexer]
        public Task<IHttpRequestHandler> GetChild(IHttpContext context, int index)
        {
            _index += index;
            return Task.FromResult<IHttpRequestHandler>(this);
        }

    }

    internal class MyModel
    {
        public int MyProperty { get; set; }

        public MyModel Model { get; set; }
    }

    internal class MyHandler : IHttpRequestHandler
    {
        public Task Handle(IHttpContext context, Func<Task> next)
        {
            var model = new ModelBinder(new ObjectActivator()).Get<MyModel>(context.Request.QueryString);

            return Task.Factory.GetCompleted();
        }
    }

    internal class SessionHandler<TSession> : IHttpRequestHandler
    {
        private readonly Func<TSession> _sessionFactory;

        private static readonly Random RandomGenerator = new Random();

        private class SessionHolder
        {
            private readonly TSession _session;
            private DateTime _lastAccessTime = DateTime.Now;

            public TSession Session
            {
                get
                {
                    _lastAccessTime = DateTime.Now;
                    return _session;
                }
            }

            public DateTime LastAccessTime
            {
                get { return _lastAccessTime; }
            }

            public SessionHolder(TSession session)
            {
                _session = session;
            }
        }

        private readonly ConcurrentDictionary<string, TSession> _sessions = new ConcurrentDictionary<string, TSession>();

        public SessionHandler(Func<TSession> sessionFactory)
        {
            _sessionFactory = sessionFactory;
        }

        public Task Handle(IHttpContext context, Func<Task> next)
        {

            string sessId;
            if (!context.Cookies.TryGetByName("SESSID", out sessId))
            {
                sessId = RandomGenerator.Next().ToString(CultureInfo.InvariantCulture);
                context.Cookies.Upsert("SESSID", sessId);
            }

            var session = _sessions.GetOrAdd(sessId, CreateSession);

            context.State.Session = session;

            return next();
        }

        private TSession CreateSession(string sessionId)
        {
            return _sessionFactory();
        }
    }
}
