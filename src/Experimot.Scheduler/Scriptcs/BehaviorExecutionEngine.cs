using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;

public class BehaviorExecutionEngine
{
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
        Console.WriteLine(@"Loaded Types : {0}", string.Join("\n", types.Select(s => s.Name)));

        types = Assembly.GetCallingAssembly().GetTypes().ToList();
        Console.WriteLine(@"Calling assembly Types : {0}", string.Join("\n", types.Select(s => s.Name)));

        types = Assembly.GetExecutingAssembly().GetTypes().ToList();
        Console.WriteLine(@"Executing assembly Types : {0}", string.Join("\n", types.Select(s => s.Name)));

        types = Assembly.GetEntryAssembly().GetTypes().ToList();
        Console.WriteLine(@"Entry assembly Types : {0}", string.Join("\n", types.Select(s => s.Name)));
    }

    public void Run()
    {
        Console.WriteLine(@"Running ...");

        Console.WriteLine(@"Startup Classes : {0}", string.Join(",", GetTypes("StartupBehavior").Select(s => s.Name)));
        Console.WriteLine(@"Behavior Classes : {0}",
            string.Join(",", GetTypes(typeof (ITriggerBehavior)).Select(s => s.Name)));
        Console.WriteLine(@"Exit Classes : {0}", string.Join(",", GetTypes("ExitBehavior").Select(s => s.Name)));
    }

    public IList<Type> GetTypes(string className)
    {
        return Assembly.GetExecutingAssembly().GetTypes()
            .Where(t => t.IsClass && t.Name == className).ToList();
    }

    public IList<Type> GetTypes(Type interfaceType)
    {
        return Assembly.GetExecutingAssembly().GetTypes()
            .Where(t => t.IsClass && interfaceType.IsAssignableFrom(t)).ToList();
    }
}