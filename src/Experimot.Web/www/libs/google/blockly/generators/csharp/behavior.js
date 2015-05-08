Blockly.CSharp['behavior_sleek'] = function(block) {
    var text_behavior_name = block.getFieldValue('behavior_name');
    var dropdown_triggers = block.getFieldValue('triggers');
    var dropdown_confidence_levels = block.getFieldValue('confidence_levels');
    var statements_do = Blockly.CSharp.statementToCode(block, 'DO');
    var dropdown_priorities = block.getFieldValue('priorities');
    // TODO: Assemble Python into code variable.

    var actions = statements_do.split(",");
    var code = "";
    var actionFunction = function appendActions(element, index, array) {
        if (element) {
            if (element.length) {
                if (index !== 0) {
                    code += ", ";
                }
                code += "{ name : '" + element.trim() + "' }";
            }
        }
    };
    code = "{ name : '" + text_behavior_name + "' , " +
        "trigger  : '" + dropdown_triggers + "' , " +
        "confidence  : '" + dropdown_confidence_levels + "' , " +
        "priority : '" + dropdown_priorities + "' , " +
        "actions: [";
    actions.forEach(actionFunction);
    code += "] }";
    return code;
};

Blockly.CSharp['behavior'] = function (block) {
    var text_name = block.getFieldValue('NAME');
    var value_when = Blockly.CSharp.valueToCode(block, 'when', Blockly.CSharp.ORDER_ATOMIC);
    var value_priority = Blockly.CSharp.valueToCode(block, 'priority', Blockly.CSharp.ORDER_ATOMIC);
    var branch = Blockly.CSharp.statementToCode(block, 'do');
    branch = Blockly.CSharp.addLoopTrap(branch, block.id) ||
        Blockly.CSharp.PASS;
    // TODO: Assemble CSharp into code variable.
    console.log(branch);

    var actions = branch.split(",");
    var code = "";
    var actionFunction = function appendActions(element, index, array) {
        if (element) {
            if (element.length) {
                if (index !== 0) {
                    code += ", ";
                }
                code += "{ name : '" + element.trim() + "' }";
            }
        }
    };

    code =  "{ name : '" + text_name + "' , " +
        "trigger  : '" + value_when + "' , " +
        "priority : '" + value_priority + "' , " +
        "actions: [";
    actions.forEach(actionFunction);
    code += "] }";

    return [code, Blockly.CSharp.ORDER_ATOMIC];
};

Blockly.CSharp['robot_action'] = function (block) {
    //return "";
    var dropdown_actions = block.getFieldValue('actions');
    //console.log(dropdown_actions);
    // TODO: Assemble CSharp into code variable.
    //var code = '\'' + dropdown_actions + '\'';
    //var code = 'execute_action(' + dropdown_actions + '); \n';
    var code = dropdown_actions+",";
    //var code =  dropdown_actions ;
    //return [code, Blockly.CSharp.ORDER_ATOMIC];
    return code;
};

Blockly.CSharp['trigger'] = function (block) {
    var dropdown_triggers = block.getFieldValue('triggers');
    // TODO: Assemble CSharp into code variable.
    //var code = '\'' + dropdown_triggers + '\'';
    var code = dropdown_triggers;
    return [code, Blockly.CSharp.ORDER_ATOMIC];
};

Blockly.CSharp['priority'] = function (block) {
    var dropdown_priorities = block.getFieldValue('priorities');
    // TODO: Assemble CSharp into code variable.
    //var code = '\'' + dropdown_priorities + '\'';
    var code = dropdown_priorities;
    return [code, Blockly.CSharp.ORDER_ATOMIC];
};