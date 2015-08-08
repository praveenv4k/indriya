using System;
using System.Reflection;

namespace Indriya.Core.Util
{
    public class ReflectionUtil
    {
        public static object InvokeStaticMethod(Type typeName, string methodName, params object[] parameters)
        {
            if (typeName != null && !string.IsNullOrEmpty(methodName))
            {
                MethodInfo staticMethodInfo = typeName.GetMethod(methodName);
                if (staticMethodInfo != null && staticMethodInfo.IsStatic)
                {
                    return staticMethodInfo.Invoke(null, parameters);
                }
            }
            return null;
        }

        public static object InvokeStaticProperty(Type typeName, string propName)
        {
            if (typeName != null && !string.IsNullOrEmpty(propName))
            {
                var staticPropertyInfo = typeName.GetProperty(propName);
                if (staticPropertyInfo != null)
                {
                    return staticPropertyInfo.GetValue(null);
                }
            }
            return null;
        }

        public static bool InvokeBooleanProperty(Type cyclicBehavior, string methodName)
        {
            var priorityObject = InvokeStaticProperty(cyclicBehavior, methodName);
            var ret = false;

            if (priorityObject != null)
            {
                if (bool.TryParse(priorityObject.ToString(), out ret))
                {
                }
            }
            return ret;
        }

        public static T InvokeGenericMethod<T>(Type cyclicBehavior, string methodName, params object[] parameters) where T : class
        {
            var returnObject = InvokeStaticMethod(cyclicBehavior, methodName, parameters);
            return returnObject as T;
        }
    }
}
