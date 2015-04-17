using System.Collections.Generic;
using System.Linq;
using experimot.msgs;

namespace Experimot.Core.Util
{
    public class MessageUtil
    {
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
                ret.param.Add(new Node.Param()
                {
                    key = item.key,
                    value = item.value,
                    dataType = item.type.ToString()
                });
            }
            return ret;
        }

        public static IList<Node.Param> XmlToMessageParam(node node)
        {
            return node == null ? XmlToMessageParam(parameters: null) : XmlToMessageParam(node.parameters);
        }

        public static IList<Node.Param> XmlToMessageParam(IList<param_type> parameters)
        {
            if (parameters != null)
            {
                return parameters.Select(item => new Node.Param()
                {
                    key = item.key,
                    value = item.value,
                    dataType = item.type.ToString()
                }).ToList();
            }
            return new List<Node.Param>();
        }
    }
}
