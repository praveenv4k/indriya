using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Windows;
using NetMQ;
using ProtoBuf;
using Scheduler;
using Context = Experimot.Scheduler.Core.Context;
using Expression = System.Linq.Expressions.Expression;

namespace Experimot.Scheduler.Tasks
{
    public class ContextSync
    {
        private readonly Context _ctx;

        private object _object;
        private readonly IList<socket> _publishers;

        public delegate void UpdateDelegate<in T>(T item);

        private struct DelegateInfo
        {
            public Type ArgType { get; set; }
            public Delegate DelegateType { get; set; }
        }

        private readonly IDictionary<string, DelegateInfo> _delegateDict;

        public ContextSync(experimot_config config, Context ctx)
        {
            _ctx = ctx;
            _publishers = new List<socket>();
            _delegateDict = new Dictionary<string, DelegateInfo>();
            string ns = "experimot.msgs";
            var msgTypes = GetMessageTypes(ns);


            var subDict = new Dictionary<string, socket>();
            foreach (var node in config.nodes)
            {
                foreach (var subscriber in node.subscribers)
                {
                    if (!subDict.ContainsKey(subscriber.msg_type))
                    {
                        subDict.Add(subscriber.msg_type, subscriber);
                    }
                }
            }

            foreach (var node in config.nodes)
            {
                if (node.enabled)
                {
                    foreach (var publisher in node.publishers)
                    {
                        if (subDict.ContainsKey(publisher.msg_type))
                        {
                            var sock = new socket()
                            {
                                host = subDict[publisher.msg_type].host,
                                msg_type = publisher.msg_type,
                                name = publisher.name,
                                port = publisher.port,
                                topic = publisher.topic
                            };
                            _publishers.Add(sock);
                        }
                        else
                        {
                            continue;
                        }

                        if (!_delegateDict.ContainsKey(publisher.msg_type))
                        {
                            var typeFound =
                                msgTypes.FirstOrDefault(s => s.Name == publisher.msg_type);
                            if (typeFound != null)
                            {
                                var methods = typeof (Context).GetMethods();
                                foreach (var method in methods)
                                {
                                    if (method.Name != "Update") continue;
                                    var prms = method.GetParameters();
                                    if (prms.Length > 0)
                                    {
                                        var prmType = prms.FirstOrDefault(s => s.ParameterType == typeFound);
                                        if (prmType != null)
                                        {
                                            _delegateDict.Add(publisher.msg_type,
                                                new DelegateInfo()
                                                {
                                                    DelegateType = CreateDelegate(method, _ctx),
                                                    ArgType = typeFound
                                                });
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        private static Delegate CreateDelegate(MethodInfo method, object target)
        {
            if (method == null)
            {
                throw new ArgumentNullException("method");
            }

            //if (!method.IsStatic)
            //{
            //    throw new ArgumentException("The provided method must be static.", "method");
            //}

            //if (method.IsGenericMethod)
            //{
            //    throw new ArgumentException("The provided method must not be generic.", "method");
            //}

            return method.CreateDelegate(Expression.GetDelegateType(
                (from parameter in method.GetParameters() select parameter.ParameterType)
                    .Concat(new[] {method.ReturnType})
                    .ToArray()), target);
        }

        public IList<Type> GetMessageTypes(string namespaceStr)
        {
            return AppDomain.CurrentDomain.GetAssemblies().SelectMany(t => t.GetTypes())
                .Where(t => t.IsClass && t.Namespace == namespaceStr).ToList();
        }

        private static byte[] GetBytes(string str)
        {
            byte[] bytes = new byte[str.Length*sizeof (char)];
            Buffer.BlockCopy(str.ToCharArray(), 0, bytes, 0, bytes.Length);
            return bytes;
        }

        private static string GetString(byte[] bytes)
        {
            char[] chars = new char[bytes.Length/sizeof (char)];
            Buffer.BlockCopy(bytes, 0, chars, 0, bytes.Length);
            return new string(chars);
        }

        public void Update(int timeout)
        {
            if (false)
            {
                using (var context = NetMQContext.Create())
                {
                    using (var socket = context.CreateSubscriberSocket())
                    {
                        //socket.Connect("tcp://127.0.0.1:5570");
                        socket.Connect("tcp://localhost:5570");
                        socket.Subscribe("KSP");

                        //socket.SetSockOpt(SocketOpt.SUBSCRIBE, GetBytes("KSP"));
                        var topic = socket.ReceiveString(new TimeSpan(0, 0, 0, 0, timeout));
                        //var topic = socket.ReceiveString();
                        if (topic != null)
                        {
                            byte[] msg = socket.Receive();
                            if (msg != null)
                            {
                                using (var memStream = new MemoryStream(msg))
                                {
                                    Console.WriteLine("Kinect bodies received");
                                }
                            }
                            else
                            {
                                MessageBox.Show(string.Format("Message buffer empty!"));
                            }
                        }
                    }
                }
                return;
            }
            else
            {
                foreach (var publisher in _publishers)
                {
                    if (!_delegateDict.ContainsKey(publisher.msg_type))
                    {
                        continue;
                    }
                    var delegateInfo = _delegateDict[publisher.msg_type];

                    using (var context = NetMQContext.Create())
                    {
                        using (var socket = context.CreateSubscriberSocket())
                        {
                            string addr = string.Format("{0}:{1}", publisher.host, publisher.port);
                            //addr = string.Format("{0}:{1}", "tcp://127.0.0.1", publisher.port);
                            socket.Connect(addr);
                            socket.Subscribe(publisher.topic);
                            //socket.SetSockOpt(SocketOpt.SUBSCRIBE, GetBytes(publisher.topic));
                            var topic = socket.ReceiveString(new TimeSpan(0, 0, 0, 0, timeout));
                            if (topic != null)
                            {
                                byte[] msg = socket.Receive();
                                if (msg != null)
                                {
                                    using (var memStream = new MemoryStream(msg))
                                    {
                                        MethodInfo method = typeof (Serializer).GetMethod("Deserialize");
                                        MethodInfo generic = method.MakeGenericMethod(delegateInfo.ArgType);
                                        var ret = generic.Invoke(null, new object[] {memStream});
                                        delegateInfo.DelegateType.DynamicInvoke(new object[] {ret});
                                    }
                                }
                                else
                                {
                                    MessageBox.Show(string.Format("Message buffer empty!"));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
