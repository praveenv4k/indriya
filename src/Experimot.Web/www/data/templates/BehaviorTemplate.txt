public class BehaviorTemplate
{
    private TriggerBasedBehavior _behavior;

    public BehaviorTemplate()
    {
        _behavior = new TriggerBasedBehavior();
    }

    public string ActiveResource { get; set; }

    public bool ExecuteInit(IBehaviorExecutionContext context)
    {
        if (!_behavior.InitActionsComplete)
        {
            // INIT_BLOCK
            // INIT_BLOCK_HERE
            _behavior.InitActionsComplete = true;
        }
        return _behavior.InitActionsComplete;
    }

    public bool ExecuteCyclic(IBehaviorExecutionContext context)
    {
        if (!_behavior.CyclicActionsComplete)
        {
            // CYCLIC_BLOCK
            // CYCLIC_BLOCK_HERE
        }
        return _behavior.CyclicActionsComplete;
    }

    public bool ExecuteExit(IBehaviorExecutionContext context)
    {
        if (!_behavior.ExitActionsComplete)
        {
            // EXIT_BLOCK
            // EXIT_BLOCK_HERE
            _behavior.ExitActionsComplete = true;
        }
        return _behavior.ExitActionsComplete;
    }
}