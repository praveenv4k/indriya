using System.Collections.Generic;
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

    public void Run()
    {

    }
}