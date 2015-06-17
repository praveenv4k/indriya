using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using Common.Logging;

public class BehaviorExecutionEngine
{
    private static readonly ILog Log = LogManager.GetLogger(typeof (BehaviorExecutionEngine));
    private readonly BehaviorExecutionContext _context;

    public BehaviorExecutionContext Context
    {
        get { return _context; }
    }

    public BehaviorExecutionEngine(BehaviorExecutionContext context)
    {
        _context = context;
    }

    public static void DisplayLoadedTypes()
    {
        var types = Assembly.GetAssembly(typeof (StartupBehavior)).GetTypes().ToList();
        Log.InfoFormat(@"Loaded Types : {0}", string.Join("\n", types.Select(s => s.Name)));

        types = Assembly.GetCallingAssembly().GetTypes().ToList();
        Log.InfoFormat(@"Calling assembly Types : {0}", string.Join("\n", types.Select(s => s.Name)));

        types = Assembly.GetExecutingAssembly().GetTypes().ToList();
        Log.InfoFormat(@"Executing assembly Types : {0}", string.Join("\n", types.Select(s => s.Name)));

        types = Assembly.GetEntryAssembly().GetTypes().ToList();
        Log.InfoFormat(@"Entry assembly Types : {0}", string.Join("\n", types.Select(s => s.Name)));

        Log.InfoFormat(@"Startup Classes : {0}", string.Join(",", GetTypes("StartupBehavior").Select(s => s.Name)));

        Log.InfoFormat(@"Behavior Classes : {0}",
            string.Join(",", GetTypes(typeof (ITriggerBehavior)).Select(s => s.Name)));
        Log.InfoFormat(@"Exit Classes : {0}", string.Join(",", GetTypes("ExitBehavior").Select(s => s.Name)));
    }

    public void ExecuteInitExitBlock(string blockName)
    {
        try
        {
            var startupType = GetTypes(blockName).FirstOrDefault();
            // Check Startup behavior exists
            if (startupType != null)
            {
                Log.InfoFormat("{0} Exists", blockName);
                // Check Execute method exists
                var execMethodInfo = startupType.GetMethod("Execute");
                if (execMethodInfo != null)
                {
                    // Create the instance of the Startupbehavior type
                    var startupInstance = Activator.CreateInstance(startupType);
                    if (startupInstance != null)
                    {
                        // Invoke the execute method
                        execMethodInfo.Invoke(startupInstance, new object[] {_context});
                    }
                }
            }
        }
        catch (Exception ex)
        {
            Log.ErrorFormat("Message : {0}, StackTrace : {1}", ex.Message, ex.StackTrace);
        }
    }

    public object InvokeStaticMethod(Type typeName, string methodName, params object[] parameters)
    {
        if (typeName != null && !string.IsNullOrEmpty(methodName))
        {
            MethodInfo staticMethodInfo = typeName.GetMethod(methodName);
            if (staticMethodInfo!=null && staticMethodInfo.IsStatic)
            {
                return staticMethodInfo.Invoke(null, parameters);
            }
        }
        return null;
    }

    public object InvokeStaticProperty(Type typeName, string propName, params object[] parameters)
    {
        if (typeName != null && !string.IsNullOrEmpty(propName))
        {
            var staticPropertyInfo = typeName.GetProperty(propName, BindingFlags.Static);
            if (staticPropertyInfo != null)
            {
                return staticPropertyInfo.GetValue(null);
            }
        }
        return null;
    }

    public void Run()
    {
        Log.Info(@"Running ...");

        // Startup Behavior Execution
        ExecuteInitExitBlock("StartupBehavior");

        // Cyclic Behavior Execution
        var cyclicBehaviors = GetTypes(typeof (ITriggerBehavior));
        Log.InfoFormat(@"Cyclic Behaviors : \n {0}", string.Join("\n", cyclicBehaviors.Select(s => s.Name)));

        // Exit Behavior Execution
        ExecuteInitExitBlock("ExitBehavior");
    }

    public static IList<Type> GetTypes(string className)
    {
        return Assembly.GetExecutingAssembly().GetTypes()
            .Where(t => t.IsClass && t.Name == className).ToList();
    }

    public static IList<Type> GetTypes(Type interfaceType)
    {
        return Assembly.GetExecutingAssembly().GetTypes()
            .Where(t => t.IsClass && interfaceType.IsAssignableFrom(t)).ToList();
    }
}