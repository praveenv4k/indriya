using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using experimot.msgs;
using Scheduler;

namespace Experimot.Scheduler
{
    internal class MessageUtil
    {
        public static Node XmlToMessage(node node)
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
            foreach (var item in node.@params)
            {
                ret.param.Add(new experimot.msgs.Node.Param()
                {
                    key = item.key,
                    value = item.value,
                    dataType = item.type.ToString()
                });
            }
            return ret;
        }
    }
}
