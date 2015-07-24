using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Common.Logging;
using Indriya.Core.Msgs;
using Indriya.Core.Schema;
using NetMQ;
using ProtoBuf;

namespace Indriya.Core.Util
{
    public class MessageUtil
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof (MessageUtil));

        public static Node XmlToMessageNode(node node)
        {
            var ret = new Node {name = node.name};
            foreach (var item in node.publishers)
            {
                ret.publisher.Add(new Publish()
                {
                    host = item.host,
                    msg_type = item.msg_type,
                    port = (uint) item.port,
                    topic = item.topic
                });
            }
            foreach (var item in node.subscribers)
            {
                ret.subscriber.Add(new Subscribe()
                {
                    host = item.host,
                    msg_type = item.msg_type,
                    port = (uint) item.port,
                    topic = item.topic
                });
            }
            foreach (var item in node.parameters)
            {
                ret.param.Add(new Param()
                {
                    key = item.key,
                    value = item.value,
                    dataType = item.type.ToString()
                });
            }
            return ret;
        }

        public static IList<Param> XmlToMessageParam(node node)
        {
            return node == null ? XmlToMessageParam(parameters: null) : XmlToMessageParam(node.parameters);
        }

        public static IList<Param> XmlToMessageParam(IList<param_type> parameters)
        {
            if (parameters != null)
            {
                return parameters.Select(item => new Param()
                {
                    key = item.key,
                    value = item.value,
                    dataType = item.type.ToString()
                }).ToList();
            }
            return new List<Param>();
        }

        public static T ParseProtoMessage<T>(byte[] msgBuffer) where T : class
        {
            if (msgBuffer != null)
            {
                try
                {
                    using (var memStream = new MemoryStream(msgBuffer))
                    {
                        var msg = Serializer.Deserialize<T>(memStream);
                        return msg;
                    }
                }
                catch (ProtoException ex)
                {
                    Log.ErrorFormat("Exception while deserializing registration message: {0} ", ex.Message);
                }
            }
            return default(T);
        }

        public static T ReceiveAndParseProtoMessage<T>(NetMQSocket socket, int timeout) where T : class
        {
            if (socket != null)
            {
                var msg = socket.ReceiveMessage(new TimeSpan(0, 0, 0, 0, timeout));
                if (msg != null)
                {
                    if (msg.FrameCount > 0)
                    {
                        return ParseProtoMessage<T>(msg.First.Buffer);
                    }
                }
                else
                {
                    Console.WriteLine(@"Message buffer empty!");
                }
            }
            return default(T);
        }

        public static T ReceiveAndParseProtoMessage<T>(NetMQSocket socket) where T : class
        {
            if (socket != null)
            {
                var msg = socket.ReceiveMessage();
                if (msg != null)
                {
                    if (msg.FrameCount > 0)
                    {
                        return ParseProtoMessage<T>(msg.First.Buffer);
                    }
                }
                else
                {
                    Console.WriteLine(@"Message buffer empty!");
                }
            }
            return default(T);
        }

        public static T RequestProtoMessage<T>(string server, string request, int timeout) where T : class
        {
            try
            {
                using (var context = NetMQContext.Create())
                {
                    using (var socket = context.CreateRequestSocket())
                    {
                        socket.Connect(server);
                        socket.Send(request);

                        return ReceiveAndParseProtoMessage<T>(socket, timeout);
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("{1} : {0}", ex.StackTrace, ex.Message);
            }
            return default(T);
        }

        public static T RequestProtoMessage<T>(string server, string request) where T : class
        {
            try
            {
                using (var context = NetMQContext.Create())
                {
                    using (var socket = context.CreateRequestSocket())
                    {
                        socket.Connect(server);
                        socket.Send(request);

                        return ReceiveAndParseProtoMessage<T>(socket);
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("{1} : {0}", ex.StackTrace, ex.Message);
            }
            return default(T);
        }

        public static void SerializeProtoMessage<T>(NetMQSocket socket, T msg) where T : class
        {
            if (socket != null)
            {
                using (var ms = new MemoryStream())
                {
                    Serializer.Serialize(ms, msg);
                    socket.Send(ms.GetBuffer(), (int) ms.Length);
                }
            }
        }
    }
}
