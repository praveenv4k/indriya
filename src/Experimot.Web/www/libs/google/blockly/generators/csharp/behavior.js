Blockly.CSharp['behavior_sleek'] = function(block) {
    var name = block.getFieldValue('behavior_name');
    var dropdownTriggers = block.getFieldValue('triggers');
    var countVariable = block.getFieldValue('trigger_count');
    var dropdownConfidenceLevels = block.getFieldValue('confidence_levels');
    var initDo = Blockly.CSharp.statementToCode(block, 'INIT_DO');
    var statementsDo = Blockly.CSharp.statementToCode(block, 'DO');
    var exitDo = Blockly.CSharp.statementToCode(block, 'EXIT_DO');
    var dropdownPriorities = block.getFieldValue('priorities');
    var execution = block.getFieldValue('execution');
    var inputExists = block.getInput('RUN_UNTIL');
    var executeLogic = undefined;
    if (inputExists) {
        executeLogic = Blockly.CSharp.valueToCode(this, 'RUN_UNTIL', Blockly.CSharp.ORDER_ATOMIC);
    }
    var code = 'function ' + name + '(){\n';
    code += 'register_trigger(\"' + dropdownTriggers + '\", ' + dropdownConfidenceLevels + ');\n';
    code += 'register_trigger_count(\"' + dropdownTriggers + '\", \"' + countVariable + '\");\n';
    code += 'set_priority(\"' + dropdownPriorities  + '\");\n';
    code += initDo;
    if (executeLogic != undefined) {
        code += 'while(evaluate_execution(\"' + execution + '\",\"' + executeLogic + '\")){\n';
    } else {
        code += 'while(evaluate_execution(\"' + execution + '\")){\n';
    }
    code += statementsDo;
    code += '}\n';
    code += exitDo;
    code += '}\n';

    return code;
};


Blockly.CSharp['behavior_simple'] = function(block) {
    var textBehaviorName = block.getFieldValue('behavior_name');
    var dropdownTriggers = block.getFieldValue('triggers');
    var statementsDo = Blockly.CSharp.statementToCode(block, 'DO');
    var dropdownPriorities = block.getFieldValue('priorities');
    var execution = block.getFieldValue('execution');

    var inputExists = block.getInput('RUN_UNTIL');
    var executeLogic = undefined;
    if (inputExists) {
        executeLogic = Blockly.CSharp.valueToCode(this, 'RUN_UNTIL', Blockly.CSharp.ORDER_ATOMIC);
    }
    var code = 'function ' + textBehaviorName + '(){\n';
    code += 'register_trigger(\"' + dropdownTriggers + '\");\n';
    code += 'set_priority(\"' + dropdownPriorities + '\");\n';
    if (executeLogic != undefined) {
        code += 'while(evaluate_execution(\"' + execution + '\",\"' + executeLogic + '\")){\n';
    } else {
        code += 'while(evaluate_execution(\"' + execution + '\")){\n';
    }
    code += statementsDo;
    code += '}\n';
    code += '}\n';

    return code;
};

Blockly.CSharp['behavior_simple_count'] = function(block) {
    var textBehaviorName = block.getFieldValue('behavior_name');
    var dropdownTriggers = block.getFieldValue('triggers');
    var countVariable = block.getFieldValue('trigger_count');
    var dropdownConfidenceLevels = block.getFieldValue('confidence_levels');
    var statementsDo = Blockly.CSharp.statementToCode(block, 'DO');
    var dropdownPriorities = block.getFieldValue('priorities');
    var execution = block.getFieldValue('execution');

    var inputExists = block.getInput('RUN_UNTIL');
    var executeLogic = undefined;
    if (inputExists) {
        executeLogic = Blockly.CSharp.valueToCode(this, 'RUN_UNTIL', Blockly.CSharp.ORDER_ATOMIC);
    }
    var code = 'function ' + textBehaviorName + '(){\n';
    code += 'register_trigger(\"' + dropdownTriggers + '\", ' + dropdownConfidenceLevels + ');\n';
    code += 'register_trigger_count(\"' + dropdownTriggers + '\", \"' + countVariable + '\");\n';
    code += 'set_priority(\"' + dropdownPriorities + '\");\n';
    if (executeLogic != undefined) {
        code += 'while(evaluate_execution(\"' + execution + '\",\"' + executeLogic + '\")){\n';
    } else {
        code += 'while(evaluate_execution(\"' + execution + '\")){\n';
    }
    code += statementsDo;
    code += '}\n';
    code += '}\n';

    return code;
};

Blockly.CSharp['behavior_startup'] = function (block) {
    var statementsDo = Blockly.CSharp.statementToCode(block, 'DO');
    var code = 'function behavior_startup(){\n';
    code += statementsDo;
    code += '}\n';
    return code;
};

Blockly.CSharp['behavior_exit'] = function (block) {
    var statementsDo = Blockly.CSharp.statementToCode(block, 'DO');
    var code = 'function behavior_exit(){\n';
    code += statementsDo;
    code += '}\n';
    return code;
};

Blockly.CSharp['behavior'] = function (block) {
    var name = block.getFieldValue('NAME');
    var when = Blockly.CSharp.valueToCode(block, 'when', Blockly.CSharp.ORDER_ATOMIC);
    var priority = Blockly.CSharp.valueToCode(block, 'priority', Blockly.CSharp.ORDER_ATOMIC);
    var branch = Blockly.CSharp.statementToCode(block, 'do');
    branch = Blockly.CSharp.addLoopTrap(branch, block.id) ||
        Blockly.CSharp.PASS;
    console.log(branch);
    var code = 'function ' + name + '(){\n';
    code += when;
    code += priority;
    code += branch;
    code += '}\n';
    return [code, Blockly.CSharp.ORDER_ATOMIC];
};

Blockly.CSharp['robot_action'] = function (block) {
    var dropdownActions = block.getFieldValue('actions');
    var code = 'do_action(' + dropdownActions + ');\n';
    return code;
};

Blockly.CSharp['animated_say_action'] = function (block) {
    var sayMsg = block.getFieldValue('SAY_TEXT');
    var code = 'var msg = \"' + sayMsg + '\";\n';
    code += 'animated_say(msg);\n';
    return code;
};

Blockly.CSharp['animated_say_action_arg'] = function(block) {
    //return "";
    var argName = Blockly.CSharp.valueToCode(this, 'ARG_NAME', Blockly.CSharp.ORDER_ATOMIC);
    var prefixMsg = block.getFieldValue('PREFIX_TEXT');
    var suffixMsg = block.getFieldValue('SUFFIX_TEXT');
    var code = 'var msg = \"' + prefixMsg + ' {0} ' + suffixMsg + '\";\n';
    code += 'var text = string.Format(msg,' + argName + ');\n';
    code += 'animated_say(text);\n';
    return code;
};

Blockly.CSharp['approach_action'] = function (block) {
    var distance = block.getFieldValue('approach_distance');
    var code = 'var approach_distance = ' + distance + ';\n';
    code += 'approach(approach_distance);\n';
    return code;
};

Blockly.CSharp['therapy_action'] = function(block) {
    var therapyName = block.getFieldValue('therapy_exercise');
    var code = 'var therapy_action = ' + therapyName + ';\n';
    code += 'do_action(therapy_action);\n';
    return code;
};

Blockly.CSharp['trigger'] = function (block) {
    var trigger = block.getFieldValue('MOTION_TRIGGER');
    var code = 'set_gesture_trigger(' + trigger + ');\n';
    return [code, Blockly.CSharp.ORDER_ATOMIC];
};

Blockly.CSharp['voice_trigger'] = function (block) {
    var trigger = block.getFieldValue('VOICE_TRIGGER');
    var code = 'set_voice_trigger(' + trigger + ');\n';
    return [code, Blockly.CSharp.ORDER_ATOMIC];
};

Blockly.CSharp['voice_trigger2'] = function (block) {
    var trigger = block.getFieldValue('VOICE_TRIGGER');
    var code = 'set_voice_trigger(' + trigger + ');\n';
    return [code, Blockly.CSharp.ORDER_ATOMIC];
};

Blockly.CSharp['priority'] = function (block) {
    var priority = block.getFieldValue('priorities');
    var code = 'set_priority(' + priority + ');\n';
    return [code, Blockly.CSharp.ORDER_ATOMIC];
};