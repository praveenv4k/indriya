using System;
using System.Collections.Generic;
using System.Linq;
using Indriya.Core.Msgs;

namespace Indriya.Core.Util
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

        public static T Get<T>(IList<Param> parameters, string key, T defaultValue)
        {
            var ret = defaultValue;

            if (parameters != null && parameters.Count > 0)
            {
                var paramExist = parameters.FirstOrDefault(s => s.key == key);
                if (paramExist != null)
                {
                    ret = (T)Convert.ChangeType(paramExist.value, defaultValue.GetType());
                }
            }

            return ret;
        }

        public static IList<string> GetCsvList(IList<param_type> parameters, string key, string defaultValue)
        {
            IList<string> ret = new List<string>();

            if (parameters != null && parameters.Count > 0)
            {
                var paramExist = parameters.FirstOrDefault(s => s.key == key);
                if (paramExist != null)
                {
                    var csv = paramExist.value;
                    ret = csv.Split(',').ToList();

                }
            }

            if (ret.Count <= 0)
            {
                ret.Add(defaultValue);
            }

            return ret;
        }

        public static IList<string> GetCsvList(IList<Param> parameters, string key, string defaultValue)
        {
            IList<string> ret = new List<string>();

            if (parameters != null && parameters.Count > 0)
            {
                var paramExist = parameters.FirstOrDefault(s => s.key == key);
                if (paramExist != null)
                {
                    var csv = paramExist.value;
                    ret = csv.Split(',').ToList();
                }
            }

            if (ret.Count <= 0)
            {
                ret.Add(defaultValue);
            }

            return ret;
        }
    }
}