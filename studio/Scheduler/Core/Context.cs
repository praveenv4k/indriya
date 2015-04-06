using System.Collections.Concurrent;
using System.Collections.Generic;

namespace Scheduler.Core
{
    public class Context
    {
        private readonly Robot _robot;
        private readonly IDictionary<int, Human> _humans;
        private readonly IDictionary<string, ManipulatableObject> _objects;

        public Context()
        {
            _humans = new ConcurrentDictionary<int, Human>();
            _robot = new Robot();
            _objects = new ConcurrentDictionary<string, ManipulatableObject>();
        }

        public Robot Robot
        {
            get { return _robot; }
        }

        public IDictionary<int, Human> Humans
        {
            get { return _humans; }
        }

        public IDictionary<string, ManipulatableObject> Objects
        {
            get { return _objects; }
        }
    }
}
