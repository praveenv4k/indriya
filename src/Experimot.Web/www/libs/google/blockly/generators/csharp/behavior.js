Blockly.CSharp['behavior_sleek'] = function(block) {
    var text_behavior_name = block.getFieldValue('behavior_name');
    var dropdown_triggers = block.getFieldValue('triggers');
    var count_variable = block.getFieldValue('trigger_count');
    var dropdown_confidence_levels = block.getFieldValue('confidence_levels');
    var init_do = Blockly.CSharp.statementToCode(block, 'INIT_DO');
    var statements_do = Blockly.CSharp.statementToCode(block, 'DO');
    var exit_do = Blockly.CSharp.statementToCode(block, 'EXIT_DO');
    var dropdown_priorities = block.getFieldValue('priorities');
    var execution = block.getFieldValue('execution');
    // TODO: Assemble Python into code variable.

    //var actions = statements_do.split(",");
    //var code = "";
    //var actionFunction = function appendActions(element, index, array) {
    //    if (element) {
    //        if (element.length) {
    //            if (index !== 0) {
    //                code += ", ";
    //            }
    //            code += "{ name : '" + element.trim() + "' }";
    //        }
    //    }
    //};
    //code = "{ name : '" + text_behavior_name + "' , " +
    //    "trigger  : '" + dropdown_triggers + "' , " +
    //    "confidence  : '" + dropdown_confidence_levels + "' , " +
    //    "priority : '" + dropdown_priorities + "' , " +
    //    "actions: [";
    //actions.forEach(actionFunction);
    //code += "] }";
    var inputExists = block.getInput('RUN_UNTIL');
    var execute_logic = undefined;
    if (inputExists) {
        execute_logic = Blockly.CSharp.valueToCode(this, 'RUN_UNTIL', Blockly.CSharp.ORDER_ATOMIC);
    }
    var code = 'function ' + text_behavior_name + '(){\n';
    code += 'register_trigger(\"' + dropdown_triggers + '\", ' + dropdown_confidence_levels + ');\n';
    code += 'register_trigger_count(\"' + dropdown_triggers + '\", \"' + count_variable + '\");\n';
    code += 'set_priority(\"' + dropdown_priorities  + '\");\n';
    code += init_do;
    if (execute_logic != undefined) {
        code += 'while(evaluate_execution(\"' + execution + '\",\"' + execute_logic + '\")){\n';
    } else {
        code += 'while(evaluate_execution(\"' + execution + '\")){\n';
    }
    code += statements_do;
    code += '}\n';
    code += exit_do;
    code += '}\n';

    return code;
};


Blockly.CSharp['behavior_simple'] = function (block) {
    var text_behavior_name = block.getFieldValue('behavior_name');
    var dropdown_triggers = block.getFieldValue('triggers');
    var count_variable = block.getFieldValue('trigger_count');
    var dropdown_confidence_levels = block.getFieldValue('confidence_levels');
    var statements_do = Blockly.CSharp.statementToCode(block, 'DO');
    var dropdown_priorities = block.getFieldValue('priorities');
    var execution = block.getFieldValue('execution');
    // TODO: Assemble Python into code variable.
    var inputExists = block.getInput('RUN_UNTIL');
    var execute_logic = undefined;
    if (inputExists) {
        execute_logic = Blockly.CSharp.valueToCode(this, 'RUN_UNTIL', Blockly.CSharp.ORDER_ATOMIC);
    }
    var code = 'function ' + text_behavior_name + '(){\n';
    code += 'register_trigger(\"' + dropdown_triggers + '\", ' + dropdown_confidence_levels + ');\n';
    code += 'register_trigger_count(\"' + dropdown_triggers + '\", \"' + count_variable + '\");\n';
    code += 'set_priority(\"' + dropdown_priorities + '\");\n';
    if (execute_logic != undefined) {
        code += 'while(evaluate_execution(\"' + execution + '\",\"' + execute_logic + '\")){\n';
    } else {
        code += 'while(evaluate_execution(\"' + execution + '\")){\n';
    }
    code += statements_do;
    code += '}\n';
    code += '}\n';

    return code;
};

Blockly.CSharp['behavior_startup'] = function (block) {
    var statements_do = Blockly.CSharp.statementToCode(block, 'DO');
    // TODO: Assemble Python into code variable.

    //var actions = statements_do.split(",");
    //var code = "";
    //var actionFunction = function appendActions(element, index, array) {
    //    if (element) {
    //        if (element.length) {
    //            if (index !== 0) {
    //                code += ", ";
    //            }
    //            code += "{ name : '" + element.trim() + "' }";
    //        }
    //    }
    //};
    //code = "{ name : 'startup' , " +
    //    "actions: [";
    //actions.forEach(actionFunction);
    //code += "] }";

    var code = 'function behavior_startup(){\n';
    code += statements_do;
    code += '}\n';

    //var doStatement = this.getInputTargetBlock('DO');
    //console.log(doStatement);

    return code;
};

Blockly.CSharp['behavior_exit'] = function (block) {
    var statements_do = Blockly.CSharp.statementToCode(block, 'DO');
    // TODO: Assemble Python into code variable.

    //var actions = statements_do.split(",");
    //var code = "";
    //var actionFunction = function appendActions(element, index, array) {
    //    if (element) {
    //        if (element.length) {
    //            if (index !== 0) {
    //                code += ", ";
    //            }
    //            code += "{ name : '" + element.trim() + "' }";
    //        }
    //    }
    //};
    //code = "{ name : 'exit' , " +
    //    "actions: [";
    //actions.forEach(actionFunction);
    //code += "] }";

    var code = 'function behavior_exit(){\n';
    code += statements_do;
    code += '}\n';

    //var doStatement = this.getInputTargetBlock('DO');
    //console.log(doStatement);

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

    //var actions = branch.split(",");
    //var code = "";
    //var actionFunction = function appendActions(element, index, array) {
    //    if (element) {
    //        if (element.length) {
    //            if (index !== 0) {
    //                code += ", ";
    //            }
    //            code += "{ name : '" + element.trim() + "' }";
    //        }
    //    }
    //};

    //code =  "{ name : '" + text_name + "' , " +
    //    "trigger  : '" + value_when + "' , " +
    //    "priority : '" + value_priority + "' , " +
    //    "actions: [";
    //actions.forEach(actionFunction);
    //code += "] }";

    var code = 'function ' + text_name + '(){\n';
    code += value_when;
    code += value_priority;
    code += branch;
    code += '}\n';

    return [code, Blockly.CSharp.ORDER_ATOMIC];
};

Blockly.CSharp['robot_action'] = function (block) {
    //return "";
    var dropdown_actions = block.getFieldValue('actions');
    //console.log(dropdown_actions);
    // TODO: Assemble CSharp into code variable.
    //var code = '\'' + dropdown_actions + '\'';
    //var code = 'execute_action(' + dropdown_actions + '); \n';
    var code = 'do_action(' + dropdown_actions + ');\n';
    //var code =  dropdown_actions ;
    //return [code, Blockly.CSharp.ORDER_ATOMIC];
    return code;
};

Blockly.CSharp['animated_say_action'] = function (block) {
    //return "";
    var say_msg = block.getFieldValue('SAY_TEXT');
    //console.log(dropdown_actions);
    // TODO: Assemble CSharp into code variable.
    //var code = '\'' + dropdown_actions + '\'';
    //var code = 'execute_action(' + dropdown_actions + '); \n';
    var code = 'var msg = \"' + say_msg + '\";\n';
    code += 'animated_say(msg);\n';
    //var code =  dropdown_actions ;
    //return [code, Blockly.CSharp.ORDER_ATOMIC];
    return code;
};

Blockly.CSharp['animated_say_action_arg'] = function(block) {
    //return "";
    var arg_name = Blockly.CSharp.valueToCode(this, 'ARG_NAME', Blockly.CSharp.ORDER_ATOMIC);
    var prefix_msg = block.getFieldValue('PREFIX_TEXT');
    var suffix_msg = block.getFieldValue('SUFFIX_TEXT');
    //console.log(dropdown_actions);
    // TODO: Assemble CSharp into code variable.
    //var code = '\'' + dropdown_actions + '\'';
    //var code = 'execute_action(' + dropdown_actions + '); \n';
    var code = 'var msg = \"' + prefix_msg + ' {0} ' + suffix_msg + '\";\n';
    code += 'var text = string.Format(msg,' + arg_name + ');\n';
    code += 'animated_say(text);\n';
    //var code =  dropdown_actions ;
    //return [code, Blockly.CSharp.ORDER_ATOMIC];
    return code;
};

Blockly.CSharp['approach_action'] = function (block) {
    //return "";
    var distance = block.getFieldValue('approach_distance');
    //console.log(dropdown_actions);
    // TODO: Assemble CSharp into code variable.
    //var code = '\'' + dropdown_actions + '\'';
    //var code = 'execute_action(' + dropdown_actions + '); \n';
    var code = 'var approach_distance = ' + distance + ';\n';
    code += 'approach(approach_distance);\n';
    //var code =  dropdown_actions ;
    //return [code, Blockly.CSharp.ORDER_ATOMIC];
    return code;
};

Blockly.CSharp['trigger'] = function (block) {
    var dropdown_triggers = block.getFieldValue('triggers');
    // TODO: Assemble CSharp into code variable.
    //var code = '\'' + dropdown_triggers + '\'';
    var code = 'set_trigger(' + dropdown_triggers+ ');\n';
    return [code, Blockly.CSharp.ORDER_ATOMIC];
};

Blockly.CSharp['priority'] = function (block) {
    var dropdown_priorities = block.getFieldValue('priorities');
    // TODO: Assemble CSharp into code variable.
    //var code = '\'' + dropdown_priorities + '\'';
    var code = 'set_priority(' + dropdown_priorities + ');\n';
    return [code, Blockly.CSharp.ORDER_ATOMIC];
};