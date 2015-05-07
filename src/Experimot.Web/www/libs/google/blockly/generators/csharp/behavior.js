Blockly.CSharp['behavior'] = function (block) {
    var value_when = Blockly.CSharp.valueToCode(block, 'when', Blockly.CSharp.ORDER_ATOMIC);
    var value_priority = Blockly.CSharp.valueToCode(block, 'priority', Blockly.CSharp.ORDER_ATOMIC);
    var branch = Blockly.CSharp.statementToCode(block, 'do');
    branch = Blockly.CSharp.addLoopTrap(branch, block.id) ||
        Blockly.CSharp.PASS;
    // TODO: Assemble CSharp into code variable.
    console.log(branch);
    var code = 'when trigger = ' + value_when + ' do = \'' + branch.join() + '\' at priority='+ value_priority;
    return [code, Blockly.CSharp.ORDER_ATOMIC];
};

Blockly.CSharp['robot_action'] = function (block) {
    //return "";
    var dropdown_actions = block.getFieldValue('actions');
    //console.log(dropdown_actions);
    // TODO: Assemble CSharp into code variable.
    var code = '\'' + dropdown_actions + '\'';
    //var code =  dropdown_actions ;
    //return [code, Blockly.CSharp.ORDER_ATOMIC];
    return code;
};

Blockly.CSharp['trigger'] = function (block) {
    var dropdown_triggers = block.getFieldValue('triggers');
    // TODO: Assemble CSharp into code variable.
    var code = '\'' + dropdown_triggers + '\'';
    return [code, Blockly.CSharp.ORDER_ATOMIC];
};

Blockly.CSharp['priority'] = function (block) {
    var dropdown_priorities = block.getFieldValue('priorities');
    // TODO: Assemble CSharp into code variable.
    var code = '\'' + dropdown_priorities + '\'';
    return [code, Blockly.CSharp.ORDER_ATOMIC];
};