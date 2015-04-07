using System;
using System.Collections.Generic;
using System.Linq;
using Scheduler;

namespace Experimot.Scheduler
{
    public class ParameterUtil
    {
        public static T Get<T>(IList<param_type> parameters, string key, T defaultValue)
        {
            var ret = defaultValue;

            if (parameters != null && parameters.Count > 0)
            {
                var paramExist = parameters.FirstOrDefault(s => s.key == key);
                if (paramExist != null)
                {
                    ret = (T) Convert.ChangeType(paramExist.value, defaultValue.GetType());
                }
            }

            return ret;
        }
    }
}