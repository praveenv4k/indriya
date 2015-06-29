function getURL(url) {
    return $.ajax({
        type: "GET",
        url: url,
        cache: false,
        async: false
    }).responseText;
}

function generateUUID() {
    var d = new Date().getTime();
    var uuid = 'xxxxxxxx_xxxx_xxxx_yxxx_xxxxxxxxxxxx'.replace(/[xy]/g, function (c) {
        var r = (d + Math.random() * 16) % 16 | 0;
        d = Math.floor(d / 16);
        return (c == 'x' ? r : (r & 0x3 | 0x8)).toString(16);
    });
    return uuid;
};

function generateUniqueVarName() {
    var uid = generateUUID();
    return 'var_' + uid;
};

function replaceAll(find, replace, str) {
    return str.replace(new RegExp(find, 'g'), replace);
}

Blockly.CSharp['behavior_sleek'] = function (block) {
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

Blockly.CSharp['behavior_composable'] = function(block) {
    var textBehaviorName = block.getFieldValue('behavior_name');
    var trigger = Blockly.CSharp.valueToCode(this, 'trigger', Blockly.CSharp.ORDER_ATOMIC);
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
    var guid = generateUUID();
    var priority = 'Priority = BehaviorExecutionPriority.' + dropdownPriorities + ';\n';
    //var code = 'function ' + textBehaviorName + '(){\n';
    var code = 'public static void ' + guid + '(){\n';
    code += 'var behavior = ComposableBehavior.Create(@\"' + textBehaviorName + '\");\n';
    code += trigger;
    code += 'behavior.SetPriority(@\"' + dropdownPriorities + '\");\n';
    code += '// Init Block \n';
    //code += initDo;
    code += 'behavior.RegisterInitBlock(@\"' + initDo + '\");\n';
    code += '// Cyclic Block \n';
    var cyclic = '';
    var lifeTime = 'ExecutionLifetime = BehaviorExecutionLifetime.' + execution + ';\n';
    if (executeLogic != undefined) {
        cyclic += 'while(EvaluateExecution(\"' + execution + '\",\"' + executeLogic + '\")){\n';
        //lifeTime += executeLogic + ';\n';
    } else {
        cyclic += 'while(EvaluateExecution(\""' + execution + '\"")){\n';
    }
    cyclic += statementsDo;
    cyclic += '}\n';
    code += 'behavior.RegisterCyclicBlock(@\"' + cyclic + '\");\n';
    code += '// Exit Block \n';
    //code += exitDo;
    code += 'behavior.RegisterExitBlock(@\"' + exitDo + '\");\n';
    code += '}\n';

    var template = getURL('data/templates/BehaviorTemplate.cs');
    //console.log(template);

    var className = 'Behavior_' + guid;
    var replaced = template.replace('// INIT_BLOCK_HERE', initDo);
    var replaced2 = replaced.replace('// CYCLIC_BLOCK_HERE', statementsDo);
    var replaced3 = replaced2.replace('// EXIT_BLOCK_HERE', exitDo);
    var replaced4 = replaceAll('BehaviorTemplate', className, replaced3);
    var replaced5 = replaced4.replace('// SET_PRIORITY_HERE', priority);
    var replaced6 = replaced5.replace('// SET_TRIGGER_HERE', trigger);
    var replaced7 = replaced6.replace('// SET_EXECUTION_LIFETIME_HERE', lifeTime);
    var uid = 'Uid = \"' + guid + '\";\n';
    var replaced8 = replaced7.replace('// SET_UID_HERE', uid);
    if (executeLogic != undefined) {
        replaced8 = replaced8.replace('// EXECUTE_UNTIL_HERE', 'return '+ executeLogic + ';');
    }
    return replaced8;

    //return code;
};

Blockly.CSharp['behavior_composable_simple'] = function(block) {
    var textBehaviorName = block.getFieldValue('behavior_name');
    var trigger = Blockly.CSharp.valueToCode(this, 'trigger', Blockly.CSharp.ORDER_ATOMIC);
    var statementsDo = Blockly.CSharp.statementToCode(block, 'DO');

    var dropdownPriorities = block.getFieldValue('priorities');
    var execution = block.getFieldValue('execution');

    var inputExists = block.getInput('RUN_UNTIL');
    var executeLogic = undefined;
    if (inputExists) {
        executeLogic = Blockly.CSharp.valueToCode(this, 'RUN_UNTIL', Blockly.CSharp.ORDER_ATOMIC);
    }
    var lifeTime = 'ExecutionLifetime = BehaviorExecutionLifetime.' + execution + ';\n';

    var guid = generateUUID();
    var priority = 'Priority = BehaviorExecutionPriority.' + dropdownPriorities + ';\n';

    var template = getURL('data/templates/BehaviorTemplate.cs');

    var className = 'Behavior_' + guid;
    var replaced = template.replace('// CYCLIC_BLOCK_HERE', statementsDo);
    var replaced4 = replaceAll('BehaviorTemplate', className, replaced);
    var replaced5 = replaced4.replace('// SET_PRIORITY_HERE', priority);
    var replaced6 = replaced5.replace('// SET_TRIGGER_HERE', trigger);
    var replaced7 = replaced6.replace('// SET_EXECUTION_LIFETIME_HERE', lifeTime);
    var uid = 'Uid = \"' + guid + '\";\n';
    var replaced8 = replaced7.replace('// SET_UID_HERE', uid);
    if (executeLogic != undefined) {
        replaced8 = replaced8.replace('// EXECUTE_UNTIL_HERE', 'return ' + executeLogic + ';');
    }
    return replaced8;
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

    var template = getURL('data/templates/StartupBehaviorTemplate.cs');

    var replaced = template.replace('// STARTUP_BLOCK_HERE', statementsDo);
    var replaced2 = replaced.replace('StartupBehaviorTemplate', 'StartupBehavior');

    return replaced2;
};

Blockly.CSharp['behavior_exit'] = function (block) {
    var statementsDo = Blockly.CSharp.statementToCode(block, 'DO');

    var template = getURL('data/templates/ExitBehaviorTemplate.cs');

    var replaced = template.replace('// EXIT_BLOCK_HERE', statementsDo);
    var replaced2 = replaced.replace('ExitBehaviorTemplate', 'ExitBehavior');

    return replaced2;
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
    var robotName = block.getFieldValue('ROBOT');
    
    var newVarName = generateUniqueVarName();
    var behavior = 'var ' + newVarName +
        '= new BehaviorInfo' +
        '{' +
        'BehaviorName = \"' + dropdownActions + '\",' +
        'RobotName = \"' + robotName + '\"' +
        '};\n';

    var genCode = behavior + '\n';
    genCode += 'BehaviorModuleHelper.Execute(context, ' + newVarName + ');\n';
    return genCode;
};

Blockly.CSharp['set_language'] = function (block) {
    var language = block.getFieldValue('language');
    var robotName = block.getFieldValue('ROBOT');

    var newVarName = generateUniqueVarName();
    var behavior = 'var ' + newVarName +
        '= new BehaviorInfo' +
        '{' +
        'BehaviorName = \"' + 'Set Language' + '\",' +
        'RobotName = \"' + robotName + '\",' +
        'Parameters = new Dictionary<string, object>\n' +
        '{\n' +
        '{"lang", BehaviorModuleHelper.CreateBehaviorParameterOptions(\"' + language + '\", true, "string")}\n' +
        '}\n' +
        '};\n';

    var genCode = behavior + '\n';
    genCode += 'BehaviorModuleHelper.Execute(context, ' + newVarName + ');\n';
    return genCode;
};

Blockly.CSharp['animated_say_action'] = function(block) {
    var sayMsg = block.getFieldValue('SAY_TEXT');
    var robotName = block.getFieldValue('ROBOT');

    var newVarName = generateUniqueVarName();
    var behavior = 'var ' + newVarName +
        '= new BehaviorInfo\n' +
        '{\n' +
        'BehaviorName = "Say Expressively",\n' +
        'RobotName = \"' + robotName + '\",' +
        'Parameters = new Dictionary<string, object>\n' +
        '{\n' +
        '{"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions(\"' + sayMsg + '\", true, "string")}\n' +
        '}\n' +
        '};\n';

    var genCode = behavior + '\n';
    genCode += 'BehaviorModuleHelper.Execute(context, ' + newVarName + ');\n';
    return genCode;
};

Blockly.CSharp['robot_rest_action'] = function (block) {
    var robotName = block.getFieldValue('ROBOT');

    var newVarName = generateUniqueVarName();
    var behavior = 'var ' + newVarName +
        '= new BehaviorInfo\n' +
        '{\n' +
        'BehaviorName = "Take Rest",\n' +
        'RobotName = \"' + robotName + '\",' +
        'Parameters = new Dictionary<string, object>()\n' +
        '};\n';

    var genCode = behavior + '\n';
    genCode += 'BehaviorModuleHelper.Execute(context, ' + newVarName + ');\n';
    return genCode;
};

Blockly.CSharp['animated_say_action_arg'] = function(block) {
    //return "";
    var argName = Blockly.CSharp.valueToCode(this, 'ARG_NAME', Blockly.CSharp.ORDER_ATOMIC);
    var prefixMsg = block.getFieldValue('PREFIX_TEXT');
    var suffixMsg = block.getFieldValue('SUFFIX_TEXT');
    var robotName = block.getFieldValue('ROBOT');
    //var code = 'var msg = \"' + prefixMsg + ' {0} ' + suffixMsg + '\";\n';
    //code += 'var text = string.Format(msg,' + argName + ');\n';
    //code += 'animated_say(text);\n';
    var text = 'string.Format(' + '""' + prefixMsg + ' {0} ' + suffixMsg + '""' + ',' + argName + ')';
    var code = 'animated_say(' + text + ');\n';

    var newVarName = generateUniqueVarName();
    var msgText = generateUniqueVarName();
    var msg = 'var ' + msgText + '= string.Format(\"' + prefixMsg + ' {0} ' + suffixMsg + '\",' + argName + ');\n';
    var behavior = 'var ' + newVarName +
        '= new BehaviorInfo\n' +
        '{\n' +
        'BehaviorName = "Say Expressively",\n' +
        'RobotName = \"' + robotName + '\",' +
        'Parameters = new Dictionary<string, object>\n' +
        '{\n' +
        '{"msg", BehaviorModuleHelper.CreateBehaviorParameterOptions(' + msgText + ', true, "string")},\n' +
        //'{"arg", BehaviorModuleHelper.CreateBehaviorParameterOptions(' + argName + ', true, "string")}' +
        '}\n' +
        '};\n';

    var genCode = msg;
    genCode += behavior + '\n';
    genCode += 'BehaviorModuleHelper.Execute(context, ' + newVarName + ');\n';
    return genCode;
};

Blockly.CSharp['approach_action'] = function(block) {
    var distance = block.getFieldValue('approach_distance');
    //var code = 'var approach_distance = ' + distance + ';\n';
    //code += 'approach(approach_distance);\n';
    var robotName = block.getFieldValue('ROBOT');
    var code = 'approach_action(""' + distance + '"");\n';

    // Pure rotation
    var newVarName1 = generateUniqueVarName();
    var behavior1 = 'var ' + newVarName1 +
        '= new BehaviorInfo\n' +
        '{\n' +
        'BehaviorName = "Move To",\n' +
        'RobotName = \"' + robotName + '\",' +
        'Parameters = new Dictionary<string, object>\n' +
        '{\n' +
        '{"translation", BehaviorModuleHelper.CreateBehaviorParameterOptions("0", false, "float")},\n' +
        '{"rotation", BehaviorModuleHelper.CreateBehaviorParameterOptions("1", false, "float")},\n' +
        '{"human", BehaviorModuleHelper.CreateBehaviorParameterOptions("1", false, "float")},\n' +
        '{"dist", BehaviorModuleHelper.CreateBehaviorParameterOptions(' + distance + ', false, "float")},\n' +
        '{"x", BehaviorModuleHelper.CreateBehaviorParameterOptions(0.0, true, "float")},\n' +
        '{"y", BehaviorModuleHelper.CreateBehaviorParameterOptions(0.0, true, "float")},\n' +
        '{"theta", BehaviorModuleHelper.CreateBehaviorParameterOptions(0.0, true, "float")}\n' +
        '}\n' +
        '};\n';

    var newVarName2 = generateUniqueVarName();
    var behavior2 = 'var ' + newVarName2 +
        '= new BehaviorInfo\n' +
        '{\n' +
        'BehaviorName = "Move To",\n' +
        'RobotName = \"' + robotName + '\",' +
        'Parameters = new Dictionary<string, object>\n' +
        '{\n' +
        '{"translation", BehaviorModuleHelper.CreateBehaviorParameterOptions("1", false, "float")},\n' +
        '{"rotation", BehaviorModuleHelper.CreateBehaviorParameterOptions("0", false, "float")},\n' +
        '{"human", BehaviorModuleHelper.CreateBehaviorParameterOptions("1", false, "float")},\n' +
        '{"dist", BehaviorModuleHelper.CreateBehaviorParameterOptions(' + distance + ', false, "float")},\n' +
        '{"x", BehaviorModuleHelper.CreateBehaviorParameterOptions(' + distance + ', true, "float")},\n' +
        '{"y", BehaviorModuleHelper.CreateBehaviorParameterOptions(0.0, true, "float")},\n' +
        '{"theta", BehaviorModuleHelper.CreateBehaviorParameterOptions(0.0, true, "float")}\n' +
        '}\n' +
        '};\n';

    var genCode = behavior1 + '\n';
    genCode += 'if (context.RefreshApproachParameters(' + newVarName1 + ', trigger)) {\n' +
                        'BehaviorModuleHelper.Execute(context, ' + newVarName1 + ');\n' +
                '}\n';
    genCode += behavior2 + '\n';
    genCode += 'if (context.RefreshApproachParameters(' + newVarName2 + ', trigger)) {\n' +
                        'BehaviorModuleHelper.Execute(context, ' + newVarName2 + ');\n' +
                '}\n';

    return genCode;
};

Blockly.CSharp['turn_action'] = function (block) {
    var direction = block.getFieldValue('actions');
    var angle = 0;
    if (direction === 'left') {
        angle = Math.PI / 2;
    }else if (direction === 'right') {
        angle = -Math.PI / 2;
    }else if (direction === 'around') {
        angle = Math.PI;
    }

    var robotName = block.getFieldValue('ROBOT');

    // Pure rotation
    var newVarName1 = generateUniqueVarName();
    var behavior1 = 'var ' + newVarName1 +
        '= new BehaviorInfo\n' +
        '{\n' +
        'BehaviorName = "Move To",\n' +
        'RobotName = \"' + robotName + '\",' +
        'Parameters = new Dictionary<string, object>\n' +
        '{\n' +
        '{"x", BehaviorModuleHelper.CreateBehaviorParameterOptions(0.0, false, "float")},\n' +
        '{"y", BehaviorModuleHelper.CreateBehaviorParameterOptions(0.0, false, "float")},\n' +
        '{"theta", BehaviorModuleHelper.CreateBehaviorParameterOptions('+angle+', false, "float")}\n' +
        '}\n' +
        '};\n';


    var genCode = behavior1 + '\n';
    genCode += 'BehaviorModuleHelper.Execute(context, ' + newVarName1 + ');\n';

    return genCode;
};

Blockly.CSharp['move_action'] = function(block) {
    var value = block.getFieldValue('distance');

    var robotName = block.getFieldValue('ROBOT');

    var dist = parseFloat(value);
    var genCode = '';
    if (!isNaN(dist)) {
        // Pure translation
        var newVarName1 = generateUniqueVarName();
        var behavior1 = 'var ' + newVarName1 +
            '= new BehaviorInfo\n' +
            '{\n' +
            'BehaviorName = "Move To",\n' +
            'RobotName = \"' + robotName + '\",' +
            'Parameters = new Dictionary<string, object>\n' +
            '{\n' +
            '{"x", BehaviorModuleHelper.CreateBehaviorParameterOptions(' + dist + ', false, "float")},\n' +
            '{"y", BehaviorModuleHelper.CreateBehaviorParameterOptions(0.0, false, "float")},\n' +
            '{"theta", BehaviorModuleHelper.CreateBehaviorParameterOptions(0.0, false, "float")}\n' +
            '}\n' +
            '};\n';
        genCode = behavior1 + '\n';
        genCode += 'BehaviorModuleHelper.Execute(context, ' + newVarName1 + ');\n';
    } else {
        alert('Move action: distance should be a number');
    }
    return genCode;
};

Blockly.CSharp['therapy_action'] = function(block) {
    var therapyName = block.getFieldValue('therapy_exercise');
    var robotName = block.getFieldValue('ROBOT');

    var newVarName = generateUniqueVarName();
    var behavior = 'var ' + newVarName +
        '= new BehaviorInfo' +
        '{' +
        'BehaviorName = \"' + therapyName + '\",' +
        'RobotName = \"' + robotName + '\"' +
        '};\n';

    var genCode = behavior + '\n';
    genCode += 'BehaviorModuleHelper.Execute(context, ' + newVarName + ');\n';
    return genCode;
};

Blockly.CSharp['trigger'] = function (block) {
    var trigger = block.getFieldValue('MOTION_TRIGGER');

    var genCode = 'var gestureInfoList = context.GetGestureInfoList(\"' + trigger + '\");\n' +
        'var gestureInfo = gestureInfoList.FirstOrDefault(s=>s.Confidence > 90);\n'+
        'if (gestureInfo.Active && gestureInfo.Confidence > 90)\n' +
        '{\n' +
        'Console.WriteLine("Gesture trigger received : {0} - {1}", gestureInfo.Name, gestureInfo.Confidence);\n' +
        'result.HumanId = gestureInfo.HumanId;\n' +
        'result.HumanInLoop = true;\n' +
        'result.Active = true;\n' +
        '}\n';
    return [genCode, Blockly.CSharp.ORDER_ATOMIC];
};

Blockly.CSharp['voice_trigger'] = function (block) {
    var trigger = block.getFieldValue('VOICE_TRIGGER');

    var genCode = 'var voiceCommand = context.GetVoiceCommand(\"' + trigger + '\");\n' +
        'if (voiceCommand.Active && voiceCommand.Confidence > 80)\n' +
        '{\n' +
        'Console.WriteLine("Voice trigger received : {0} - {1}", voiceCommand.Name, voiceCommand.Confidence);\n' +
        'result.Active = true;\n' +
        '}\n';
    return [genCode, Blockly.CSharp.ORDER_ATOMIC];
};

Blockly.CSharp['voice_trigger2'] = function (block) {
    var trigger = block.getFieldValue('VOICE_TRIGGER');

    var genCode = 'var gestureInfo = context.GetVoiceCommand(\"' + trigger + '\");\n' +
        'if (voiceCommand.Active && voiceCommand.Confidence > 80)\n' +
        '{\n' +
        'Console.WriteLine("Voice trigger received : {0} - {1}", voiceCommand.Name, voiceCommand.Confidence);\n' +
        'result.Active = true;\n' +
        '}\n';
    return [genCode, Blockly.CSharp.ORDER_ATOMIC];
};

Blockly.CSharp['wait_voice_response'] = function(block) {
    var statements_do_choice1 = Blockly.CSharp.statementToCode(block, 'DO_CHOICE1');
    var statements_do_choice2 = Blockly.CSharp.statementToCode(block, 'DO_CHOICE2');
    var text_choice2 = block.getFieldValue('CHOICE2');
    var text_choice1 = block.getFieldValue('CHOICE1');
    var code = [];
    var varName = generateUniqueVarName();
    var commandVarName = generateUniqueVarName();
    var choice1VarName = generateUniqueVarName();
    var choice2VarName = generateUniqueVarName();
    code.push('while (true)');
    code.push('{');
    code.push('var ' + varName + ' = context.GetVoiceCommand();');
    code.push('if (' + varName + '.Active && ' + varName + '.Confidence > 80)');
    code.push('{');
    code.push('string ' + commandVarName + ' = ' + varName + '.Name;');
    code.push('string ' + choice1VarName + ' = \"' + text_choice1 + '\";');
    code.push('string ' + choice2VarName + ' = \"' + text_choice2 + '\";');
    code.push('if (String.Compare(' + choice1VarName + ', ' + commandVarName + ', StringComparison.OrdinalIgnoreCase)==0)');
    code.push('{');
    code.push(statements_do_choice1);
    code.push('break;');
    code.push('}');
    code.push('if (String.Compare(' + choice2VarName + ', ' + commandVarName + ', StringComparison.OrdinalIgnoreCase)==0)');
    code.push('{');
    code.push(statements_do_choice2);
    code.push('break;');
    code.push('}');
    code.push('}');
    code.push('}');
    return code.join('\n');
};

Blockly.CSharp['priority'] = function (block) {
    var priority = block.getFieldValue('priorities');
    var code = 'set_priority(\"' + priority + '\");\n';
    return [code, Blockly.CSharp.ORDER_ATOMIC];
};

Blockly.CSharp['sleep_for'] = function (block) {
    var duration = block.getFieldValue('SLEEP_FOR');
    var code = 'System.Threading.Thread.Sleep(' + duration + ');\n';
    return code;
};

Blockly.CSharp['debug_print'] = function (block) {
    var debugStr = block.getFieldValue('DEBUG_STRING');
    var code = 'System.Console.WriteLine(\"' + debugStr + '\");\n';
    return code;
};

Blockly.CSharp['parallel_execute'] = function(block) {
    var statements_branch1 = Blockly.CSharp.statementToCode(block, 'BRANCH1');
    var statements_branch2 = Blockly.CSharp.statementToCode(block, 'BRANCH2');
    // TODO: Assemble JavaScript into code variable.
    var code = [];
    var listVarName = generateUniqueVarName();
    var action1Name = generateUniqueVarName();
    var action2Name = generateUniqueVarName();

    code.push('var ' + listVarName + ' = new List<Task>();');
    code.push('var ' + action1Name + ' = new Action( () => ');
    code.push('{');
    code.push(statements_branch1);
    code.push('});');

    code.push('var ' + action2Name + ' = new Action( () => ');
    code.push('{');
    code.push(statements_branch2);
    code.push('});');

    code.push(listVarName + '.Add(Task.Run(' + action1Name + '));');
    code.push(listVarName + '.Add(Task.Run(' + action2Name + '));');
    code.push('Task.WaitAll(' + listVarName + '.ToArray());');
    code.push('System.Console.WriteLine("Parallel action execution complete");');
    return code.join('\n');
};