using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Experimot.Core;
using Experimot.Scheduler;

namespace Experimot.App
{
    class Program
    {
        private static Context _context;
        private static BootStrapper _bootStrapper;

        static void Main(string[] args)
        {
            const string configFile = "experimot_config.xml";
            if (!string.IsNullOrEmpty(configFile))
            {
                //_config = new experimot_config();
                var config = experimot_config.LoadFromFile(configFile);

                _context = new Context();

                _bootStrapper = new BootStrapper(config, _context);
                _bootStrapper.StartUp();
                Console.ReadLine();
            }
        }
    }
}
