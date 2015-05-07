Blockly.Python['behavior'] = function (block) {
    var value_when = Blockly.Python.valueToCode(block, 'when', Blockly.Python.ORDER_ATOMIC);
    var value_priority = Blockly.Python.valueToCode(block, 'priority', Blockly.Python.ORDER_ATOMIC);
    var branch = Blockly.Python.statementToCode(block, 'do');
    branch = Blockly.Python.addLoopTrap(branch, block.id) ||
        Blockly.Python.PASS;
    // TODO: Assemble Python into code variable.
    console.log(branch);
    var code = 'when trigger = ' + value_when + ' do = \'' + branch.join() + '\' at priority='+ value_priority;
    return [code, Blockly.Python.ORDER_ATOMIC];
};

Blockly.Python['robot_action'] = function (block) {
    //return "";
    var dropdown_actions = block.getFieldValue('actions');
    //console.log(dropdown_actions);
    // TODO: Assemble Python into code variable.
    var code = '\'' + dropdown_actions + '\'';
    //var code =  dropdown_actions ;
    //return [code, Blockly.Python.ORDER_ATOMIC];
    return code;
};

Blockly.Python['trigger'] = function (block) {
    var dropdown_triggers = block.getFieldValue('triggers');
    // TODO: Assemble Python into code variable.
    var code = '\'' + dropdown_triggers + '\'';
    return [code, Blockly.Python.ORDER_ATOMIC];
};

Blockly.Python['priority'] = function (block) {
    var dropdown_priorities = block.getFieldValue('priorities');
    // TODO: Assemble Python into code variable.
    var code = '\'' + dropdown_priorities + '\'';
    return [code, Blockly.Python.ORDER_ATOMIC];
};