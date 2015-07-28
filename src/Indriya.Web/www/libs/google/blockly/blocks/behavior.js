'use strict';

goog.provide('Blockly.Blocks.behaviors');

goog.require('Blockly.Blocks');
//goog.require('Blockly.CSharp');
/**
 * Ensure two identically-named behaviors don't exist.
 * @param {string} name Proposed procedure name.
 * @param {!Blockly.Block} block Block to disambiguate.
 * @return {string} Non-colliding name.
 */
Blockly.Blocks.behaviors.findLegalName = function (name, block) {
    if (block.isInFlyout) {
        // Flyouts can have multiple behaviors called 'behavior'.
        return name;
    }
    while (!Blockly.Blocks.behaviors.isLegalName(name, block.workspace, block)) {
        // Collision with another behavior.
        var r = name.match(/^(.*?)(\d+)$/);
        if (!r) {
            name += '2';
        } else {
            name = r[1] + (parseInt(r[2], 10) + 1);
        }
    }
    return name;
};

/**
 * Does this procedure have a legal name?  Illegal names include names of
 * behaviors already defined.
 * @param {string} name The questionable name.
 * @param {!Blockly.Workspace} workspace The workspace to scan for collisions.
 * @param {Blockly.Block} opt_exclude Optional block to exclude from
 *     comparisons (one doesn't want to collide with oneself).
 * @return {boolean} True if the name is legal.
 */
Blockly.Blocks.behaviors.isLegalName = function (name, workspace, opt_exclude) {
    var blocks = workspace.getAllBlocks();
    // Iterate through every block and check the name.
    for (var x = 0; x < blocks.length; x++) {
        if (blocks[x] == opt_exclude) {
            continue;
        }
        var func = blocks[x].getBehaviorDef;
        if (func) {
            var procName = func.call(blocks[x]);
            if (Blockly.Names.equals(procName[0], name)) {
                return false;
            }
        }
    }
    return true;
};

/**
 * Rename a procedure.  Called by the editable field.
 * @param {string} text The proposed new name.
 * @return {string} The accepted name.
 * @this {!Blockly.Field}
 */
Blockly.Blocks.behaviors.rename = function(text) {
    // Strip leading and trailing whitespace.  Beyond this, all names are legal.
    text = text.replace(/^[\s\xa0]+|[\s\xa0]+$/g, '');

    // Ensure two identically-named behaviors don't exist.
    text = Blockly.Blocks.behaviors.findLegalName(text, this.sourceBlock_);

    // Rename any callers.
    //var blocks = this.sourceBlock_.workspace.getAllBlocks();
    //for (var x = 0; x < blocks.length; x++) {
    //    var func = blocks[x].renameProcedure;
    //    if (func) {
    //        func.call(blocks[x], this.text_, text);
    //    }
    //}

    return text;
};

Blockly.Blocks.behaviors.GestureProperties =
[
    ["WaveLeft", 'Greet_Left'],
    ["WaveRight", 'Greet_Right'],
    ["LiftLeftHand", "LiftHand_Left"],
    ["LiftRightHand", "LiftHand_Right"],
    ["HumanDetected", 'HumanDetected']
    ,["Seated", "Seated"]
    //,["SmartWave", 'IMU_WAVE']
];

Blockly.Blocks.behaviors.Languages =
[
    ["English", 'English'],
    ["Japanese", 'Japanese']
    //,["French", 'French'],
    //["Italian", "Italian"],
    //["Chinese", "Chinese"],
    //["Spanish", "Spanish"]
];

Blockly.Blocks.behaviors.StandardBehaviors =
[
    ["Greet", "Greet"],
    //["LyingBelly", 'LyingBelly'],
    //["Sit Relax", 'Sit Relax'],
    ["Stand", 'Stand'],
    ["Crouch", "Crouch"],
    //["LyingBack", "LyingBack"],
    //["Sit", "Sit"],
    ["LabIntroduction", "LabIntroduction"]
    ,["Dance", "Dance"]
];

Blockly.Blocks.behaviors.Robots =
[
    ["Hiro", 'Hiro'],
    ["Taro", 'Taro']
];

Blockly.Blocks.behaviors.VoiceProperties =
[
    ["GO", "GO"],
    //["START", "START"],
    ["STOP", "STOP"],
    ["SIT", "SIT"],
    ["STAND", "STAND"],
    ["Good bye", "Good bye"]
    //,["RED", 'RED'],
    //["GREEN", 'GREEN'],
    //["BLUE", 'BLUE']
    //,["NAME", "NAME"]
];

Blockly.Blocks.behaviors.PriorityProperties =
[
    ["Low", 'low'],
    ["Normal", 'normal'],
    ["High", 'high']
];

Blockly.Blocks.behaviors.ExecutionProperties =
[
    ["Once", 'once'],
    ["Until", 'until'],
    ["Forever", 'forever']
];

Blockly.Blocks.behaviors.ConfidenceProperties =
[
    ["80%", "80"],
    ["85%", "85"],
    ["90%", "90"],
    ["95%", "95"]
];

Blockly.Blocks['gesture_count_up_trigger'] = {
    /**
     * Block for 'counting' loop.
     * @this Blockly.Block
     */
    init: function () {

        //var gestureDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.GestureProperties, function (option) {
        //});

        this.setHelpUrl(Blockly.Msg.CONTROLS_FOR_HELPURL);
        this.setColour(Blockly.Blocks.loops.HUE);
        this.appendDummyInput()
            .appendField('Count Gesture : ')
            .appendField('gesture_name', 'GESTURE_NAME')
            .appendField(' with ')
            .appendField(new Blockly.FieldVariable(null), 'VAR');

        //this.interpolateMsg(Blockly.Msg.CONTROLS_FOR_INPUT_FROM_TO_BY,
        //    ['FROM', 'Number', Blockly.ALIGN_RIGHT],
        //    ['TO', 'Number', Blockly.ALIGN_RIGHT],
        //    ['BY', 'Number', Blockly.ALIGN_RIGHT],
        //    Blockly.ALIGN_RIGHT);
        this.setPreviousStatement(true);
        this.setNextStatement(true);
        this.setInputsInline(true);
        // Assign 'this' to a variable for use in the tooltip closure below.
        //var thisBlock = this;
        //this.setTooltip(function () {
        //    return Blockly.Msg.CONTROLS_FOR_TOOLTIP.replace('%1',
        //        thisBlock.getFieldValue('VAR'));
        //});
    },
    /**
     * Return all variables referenced by this block.
     * @return {!Array.<string>} List of variable names.
     * @this Blockly.Block
     */
    getVars: function() {
        return [this.getFieldValue('VAR')];
    },
    /**
     * Notification that a variable is renaming.
     * If the name matches one of this block's variables, rename it.
     * @param {string} oldName Previous name of variable.
     * @param {string} newName Renamed variable.
     * @this Blockly.Block
     */
    renameVar: function(oldName, newName) {
        if (Blockly.Names.equals(oldName, this.getFieldValue('VAR'))) {
            this.setFieldValue(newName, 'VAR');
        }
    },
    /**
     * Add menu option to create getter block for loop variable.
     * @param {!Array} options List of menu options to add to.
     * @this Blockly.Block
     */
    customContextMenu: function(options) {
        if (!this.isCollapsed()) {
            var option = { enabled: true };
            var name = this.getFieldValue('VAR');
            option.text = Blockly.Msg.VARIABLES_SET_CREATE_GET.replace('%1', name);
            var xmlField = goog.dom.createDom('field', null, name);
            xmlField.setAttribute('name', 'VAR');
            var xmlBlock = goog.dom.createDom('block', null, xmlField);
            xmlBlock.setAttribute('type', 'variables_get');
            option.callback = Blockly.ContextMenu.callbackFactory(this, xmlBlock);
            options.push(option);
        }
    }
};

Blockly.Blocks['behavior_sleek'] = {
    init: function() {
        var thisBlock = this;
        var nameText = "behavior";
        var name = Blockly.Blocks.behaviors.findLegalName(nameText, this);
        var nameField = new Blockly.FieldTextInput(name, Blockly.Blocks.behaviors.rename);

        var priorityDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.PriorityProperties, function(option) {

        });

        var executionDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.ExecutionProperties, function(option) {
            var runUntilInput = (option == 'until');
            this.sourceBlock_.updateShape_(runUntilInput);
        });

        var gestureDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.GestureProperties, function(option) {
            //var trigger = this;
            //console.log(this);
            //console.log("Old Value : " + this.value_ + ", New Value : " + option);

            var kvp = Blockly.Blocks.behaviors.GestureProperties.filter(function(gesture) { return gesture[1] === option });
            if (kvp.length > 0) {
                thisBlock.setFieldValue(kvp[0][0] + 'Count', 'trigger_count');
            }
        });

        var confidenceDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.ConfidenceProperties, function(option) {
        });

        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(330);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Behavior Name : ")
            //.appendField(new Blockly.FieldTextInput("behavior"), "behavior_name")
            .appendField(nameField, "behavior_name");
        this.appendDummyInput()
            .appendField("");
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_LEFT)
            .appendField("Human Motion : ");
        this.appendDummyInput()
            .appendField("When gesture is")
            .appendField(gestureDropdown, "triggers")
            .appendField("with confidence level")
            .appendField(confidenceDropdown, "confidence_levels");
        this.appendDummyInput()
            .appendField("count with")
            .appendField(new Blockly.FieldVariable(null), 'trigger_count');
        this.appendDummyInput()
            .appendField("");
        this.appendDummyInput()
            .appendField("")
            .appendField("Robot Actions : ");
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Startup Actions");

        this.appendStatementInput("INIT_DO")
            .appendField("do");

        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Cyclic Actions");
        this.appendStatementInput("DO")
            .appendField("do");

        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Exit Actions");
        this.appendStatementInput("EXIT_DO")
            .appendField("do");

        this.appendDummyInput()
            .appendField("");

        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_LEFT)
            .appendField("Execution Settings : ");
        this.appendDummyInput()
            .appendField("With priority ")
            .appendField(priorityDropdown, "priorities")
            .appendField(" execute ")
            .appendField(executionDropdown, "execution");

        //this.setPreviousStatement(true, "behavior_sleek");
        //this.setNextStatement(true, "behavior_sleek");
        this.setTooltip('');
        //this.setInputsInline(true);
        this.setFieldValue(gestureDropdown.text_ + 'Count', 'trigger_count');
    },

    /**
       * Return the signature of this behavior definition.
       * @return {!Array} Tuple containing Behavior signature:
       *     - the name of the defined procedure,
       * @this Blockly.Block
       */
    getBehaviorDef: function() {
        return [this.getFieldValue('behavior_name')];
    },
    renameProcedure: function(oldName, newName) {
        if (Blockly.Names.equals(oldName, this.getBehaviorCall())) {
            this.setFieldValue(newName, 'behavior_name');
            this.setTooltip(
                (this.outputConnection ? Blockly.Msg.PROCEDURES_CALLRETURN_TOOLTIP :
                    Blockly.Msg.PROCEDURES_CALLNORETURN_TOOLTIP)
                .replace('%1', newName));
        }
    },
    getBehaviorCall: function() {
        // The NAME field is guaranteed to exist, null will never be returned.
        return /** @type {string} */ (this.getFieldValue('behavior_name'));
    },
    /**
     * Return all variables referenced by this block.
     * @return {!Array.<string>} List of variable names.
     * @this Blockly.Block
     */
    getVars: function() {
        return [this.getFieldValue('trigger_count')];
    },
    /**
     * Notification that a variable is renaming.
     * If the name matches one of this block's variables, rename it.
     * @param {string} oldName Previous name of variable.
     * @param {string} newName Renamed variable.
     * @this Blockly.Block
     */
    renameVar: function(oldName, newName) {
        if (Blockly.Names.equals(oldName, this.getFieldValue('trigger_count'))) {
            this.setFieldValue(newName, 'trigger_count');
        }
    },
    /**
     * Add menu option to create getter block for loop variable.
     * @param {!Array} options List of menu options to add to.
     * @this Blockly.Block
     */
    customContextMenu: function(options) {
        if (!this.isCollapsed()) {
            var option = { enabled: true };
            var name = this.getFieldValue('trigger_count');
            option.text = Blockly.Msg.VARIABLES_SET_CREATE_GET.replace('%1', name);
            var xmlField = goog.dom.createDom('field', null, name);
            xmlField.setAttribute('name', 'trigger_count');
            var xmlBlock = goog.dom.createDom('block', null, xmlField);
            xmlBlock.setAttribute('type', 'variables_get');
            option.callback = Blockly.ContextMenu.callbackFactory(this, xmlBlock);
            options.push(option);
        }
    },
    /**
   * Create XML to represent whether the 'divisorInput' should be present.
   * @return {Element} XML storage element.
   * @this Blockly.Block
   */
    mutationToDom: function() {
        var container = document.createElement('mutation');
        var runUntilInput = (this.getFieldValue('execution') == 'until');
        container.setAttribute('run_until', runUntilInput);
        if (runUntilInput) {
            Blockly.CSharp.init(this.workspace);
            container.setAttribute('run_logic', Blockly.CSharp.valueToCode(this, 'RUN_UNTIL', Blockly.CSharp.ORDER_ATOMIC));
        } else {
            container.setAttribute('run_logic', '');
        }
        return container;
    },
    /**
     * Parse XML to restore the 'divisorInput'.
     * @param {!Element} xmlElement XML storage element.
     * @this Blockly.Block
     */
    domToMutation: function(xmlElement) {
        var runUntilInput = (xmlElement.getAttribute('run_until') == 'true');
        this.updateShape_(runUntilInput);
    },
    /**
   * Modify this block to have (or not have) an input for 'is divisible by'.
   * @param {boolean} divisorInput True if this block has a divisor input.
   * @private
   * @this Blockly.Block
   */
    updateShape_: function(runUntilInput) {
        // Add or remove a Value Input.
        var inputExists = this.getInput('RUN_UNTIL');
        if (runUntilInput) {
            if (!inputExists) {
                this.appendValueInput('RUN_UNTIL')
                    .setCheck('Boolean');
            }
        } else if (inputExists) {
            this.removeInput('RUN_UNTIL');
        }
    }
};

Blockly.Blocks['behavior_simple'] = {
    init: function() {
        var thisBlock = this;
        var nameText = "behavior";
        var name = Blockly.Blocks.behaviors.findLegalName(nameText, this);
        var nameField = new Blockly.FieldTextInput(name, Blockly.Blocks.behaviors.rename);

        var priorityDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.PriorityProperties, function(option) {

        });

        var executionDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.ExecutionProperties, function(option) {
            var runUntilInput = (option == 'until');
            this.sourceBlock_.updateShape_(runUntilInput);
        });

        var gestureDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.GestureProperties, function(option) {
            var kvp = Blockly.Blocks.behaviors.GestureProperties.filter(function(gesture) { return gesture[1] === option });
            if (kvp.length > 0) {
                thisBlock.setFieldValue(kvp[0][0] + 'Count', 'trigger_count');
            }
        });

        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(330);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Behavior Name : ")
            .appendField(nameField, "behavior_name");
        this.appendDummyInput()
            .appendField("");
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_LEFT)
            .appendField("Human Motion : ");
        this.appendDummyInput()
            .appendField("When trigger is")
            .appendField(gestureDropdown, "triggers");
        this.appendDummyInput()
            .appendField("")
            .appendField("Robot Actions : ");
        this.appendStatementInput("DO")
            .appendField("do");
        this.appendDummyInput()
            .appendField("");

        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_LEFT)
            .appendField("Execution Settings : ");
        this.appendDummyInput()
            .appendField("With priority ")
            .appendField(priorityDropdown, "priorities")
            .appendField(" execute ")
            .appendField(executionDropdown, "execution");
        this.setTooltip('');
    },

    /**
       * Return the signature of this behavior definition.
       * @return {!Array} Tuple containing Behavior signature:
       *     - the name of the defined procedure,
       * @this Blockly.Block
       */
    getBehaviorDef: function() {
        return [this.getFieldValue('behavior_name')];
    },
    renameProcedure: function(oldName, newName) {
        if (Blockly.Names.equals(oldName, this.getBehaviorCall())) {
            this.setFieldValue(newName, 'behavior_name');
            this.setTooltip(
                (this.outputConnection ? Blockly.Msg.PROCEDURES_CALLRETURN_TOOLTIP :
                    Blockly.Msg.PROCEDURES_CALLNORETURN_TOOLTIP)
                .replace('%1', newName));
        }
    },
    getBehaviorCall: function() {
        // The NAME field is guaranteed to exist, null will never be returned.
        return /** @type {string} */ (this.getFieldValue('behavior_name'));
    },
    /**
   * Create XML to represent whether the 'divisorInput' should be present.
   * @return {Element} XML storage element.
   * @this Blockly.Block
   */
    mutationToDom: function() {
        var container = document.createElement('mutation');
        var runUntilInput = (this.getFieldValue('execution') == 'until');
        container.setAttribute('run_until', runUntilInput);
        if (runUntilInput) {
            Blockly.CSharp.init(this.workspace);
            container.setAttribute('run_logic', Blockly.CSharp.valueToCode(this, 'RUN_UNTIL', Blockly.CSharp.ORDER_ATOMIC));
        } else {
            container.setAttribute('run_logic', '');
        }
        return container;
    },
    /**
     * Parse XML to restore the 'divisorInput'.
     * @param {!Element} xmlElement XML storage element.
     * @this Blockly.Block
     */
    domToMutation: function(xmlElement) {
        var runUntilInput = (xmlElement.getAttribute('run_until') == 'true');
        this.updateShape_(runUntilInput);
    },
    /**
   * Modify this block to have (or not have) an input for 'is divisible by'.
   * @param {boolean} divisorInput True if this block has a divisor input.
   * @private
   * @this Blockly.Block
   */
    updateShape_: function(runUntilInput) {
        // Add or remove a Value Input.
        var inputExists = this.getInput('RUN_UNTIL');
        if (runUntilInput) {
            if (!inputExists) {
                this.appendValueInput('RUN_UNTIL')
                    .setCheck('Boolean');
            }
        } else if (inputExists) {
            this.removeInput('RUN_UNTIL');
        }
    }
};

Blockly.Blocks['behavior_simple_count'] = {
    init: function () {
        var thisBlock = this;
        var nameText = "behavior";
        var name = Blockly.Blocks.behaviors.findLegalName(nameText, this);
        var nameField = new Blockly.FieldTextInput(name, Blockly.Blocks.behaviors.rename);

        var priorityDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.PriorityProperties, function (option) {

        });

        var executionDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.ExecutionProperties, function (option) {
            var runUntilInput = (option == 'until');
            this.sourceBlock_.updateShape_(runUntilInput);
        });

        var gestureDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.GestureProperties, function (option) {
            var kvp = Blockly.Blocks.behaviors.GestureProperties.filter(function (gesture) { return gesture[1] === option });
            if (kvp.length > 0) {
                thisBlock.setFieldValue(kvp[0][0] + 'Count', 'trigger_count');
            }
        });

        var confidenceDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.ConfidenceProperties, function (option) {
        });

        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(330);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Behavior Name : ")
            .appendField(nameField, "behavior_name");
        this.appendDummyInput()
            .appendField("");
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_LEFT)
            .appendField("Human Motion : ");
        this.appendDummyInput()
            .appendField("When gesture is")
            .appendField(gestureDropdown, "triggers")
            .appendField("with confidence level")
            .appendField(confidenceDropdown, "confidence_levels");
        this.appendDummyInput()
            .appendField("count with")
            .appendField(new Blockly.FieldVariable(null), 'trigger_count');
        this.appendDummyInput()
            .appendField("");
        this.appendDummyInput()
            .appendField("")
            .appendField("Robot Actions : ");
        this.appendStatementInput("DO")
            .appendField("do");
        this.appendDummyInput()
            .appendField("");

        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_LEFT)
            .appendField("Execution Settings : ");
        this.appendDummyInput()
            .appendField("With priority ")
            .appendField(priorityDropdown, "priorities")
            .appendField(" execute ")
            .appendField(executionDropdown, "execution");
        this.setTooltip('');
        this.setFieldValue(gestureDropdown.text_ + 'Count', 'trigger_count');
    },

    /**
       * Return the signature of this behavior definition.
       * @return {!Array} Tuple containing Behavior signature:
       *     - the name of the defined procedure,
       * @this Blockly.Block
       */
    getBehaviorDef: function () {
        return [this.getFieldValue('behavior_name')];
    },
    renameProcedure: function (oldName, newName) {
        if (Blockly.Names.equals(oldName, this.getBehaviorCall())) {
            this.setFieldValue(newName, 'behavior_name');
            this.setTooltip(
                (this.outputConnection ? Blockly.Msg.PROCEDURES_CALLRETURN_TOOLTIP :
                    Blockly.Msg.PROCEDURES_CALLNORETURN_TOOLTIP)
                .replace('%1', newName));
        }
    },
    getBehaviorCall: function () {
        // The NAME field is guaranteed to exist, null will never be returned.
        return /** @type {string} */ (this.getFieldValue('behavior_name'));
    },
    /**
     * Return all variables referenced by this block.
     * @return {!Array.<string>} List of variable names.
     * @this Blockly.Block
     */
    getVars: function () {
        return [this.getFieldValue('trigger_count')];
    },
    /**
     * Notification that a variable is renaming.
     * If the name matches one of this block's variables, rename it.
     * @param {string} oldName Previous name of variable.
     * @param {string} newName Renamed variable.
     * @this Blockly.Block
     */
    renameVar: function (oldName, newName) {
        if (Blockly.Names.equals(oldName, this.getFieldValue('trigger_count'))) {
            this.setFieldValue(newName, 'trigger_count');
        }
    },
    /**
     * Add menu option to create getter block for loop variable.
     * @param {!Array} options List of menu options to add to.
     * @this Blockly.Block
     */
    customContextMenu: function (options) {
        if (!this.isCollapsed()) {
            var option = { enabled: true };
            var name = this.getFieldValue('trigger_count');
            option.text = Blockly.Msg.VARIABLES_SET_CREATE_GET.replace('%1', name);
            var xmlField = goog.dom.createDom('field', null, name);
            xmlField.setAttribute('name', 'trigger_count');
            var xmlBlock = goog.dom.createDom('block', null, xmlField);
            xmlBlock.setAttribute('type', 'variables_get');
            option.callback = Blockly.ContextMenu.callbackFactory(this, xmlBlock);
            options.push(option);
        }
    },
    /**
   * Create XML to represent whether the 'divisorInput' should be present.
   * @return {Element} XML storage element.
   * @this Blockly.Block
   */
    mutationToDom: function () {
        var container = document.createElement('mutation');
        var runUntilInput = (this.getFieldValue('execution') == 'until');
        container.setAttribute('run_until', runUntilInput);
        if (runUntilInput) {
            Blockly.CSharp.init(this.workspace);
            container.setAttribute('run_logic', Blockly.CSharp.valueToCode(this, 'RUN_UNTIL', Blockly.CSharp.ORDER_ATOMIC));
        } else {
            container.setAttribute('run_logic', '');
        }
        return container;
    },
    /**
     * Parse XML to restore the 'divisorInput'.
     * @param {!Element} xmlElement XML storage element.
     * @this Blockly.Block
     */
    domToMutation: function (xmlElement) {
        var runUntilInput = (xmlElement.getAttribute('run_until') == 'true');
        this.updateShape_(runUntilInput);
    },
    /**
   * Modify this block to have (or not have) an input for 'is divisible by'.
   * @param {boolean} divisorInput True if this block has a divisor input.
   * @private
   * @this Blockly.Block
   */
    updateShape_: function (runUntilInput) {
        // Add or remove a Value Input.
        var inputExists = this.getInput('RUN_UNTIL');
        if (runUntilInput) {
            if (!inputExists) {
                this.appendValueInput('RUN_UNTIL')
                    .setCheck('Boolean');
            }
        } else if (inputExists) {
            this.removeInput('RUN_UNTIL');
        }
    }
};

Blockly.Blocks['behavior_startup'] = {
    init: function() {
        var nameText = "Startup Behavior";

        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(200);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField(nameText);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Robot Actions");
        this.appendStatementInput("DO")
            .appendField("do");
        this.setTooltip('Behavior to define a set of actions to execute during the system startup');
    }
};

Blockly.Blocks['behavior_exit'] = {
    init: function() {
        var nameText = "Exit Behavior";

        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(400);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField(nameText);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Robot Actions");
        this.appendStatementInput("DO")
            .appendField("do");
        this.setTooltip('Behavior to define a set of actions to execute during the system shutdown');
    }
};

Blockly.Blocks['behavior'] = {
    init: function() {
        var nameText = "behavior";
        var name = Blockly.Blocks.behaviors.findLegalName(nameText, this);
        var nameField = new Blockly.FieldTextInput(name,
            Blockly.Blocks.behaviors.rename);

        if (name !== nameText) {
            console.log("Resolved name : " + name);
        }
        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(300);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            //.appendField(new Blockly.FieldTextInput("behavior"), "NAME");
            .appendField(nameField, "NAME");
        this.appendValueInput("when")
            .setCheck("trigger")
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField("when trigger");
        this.appendValueInput("priority")
            .setCheck("priority")
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField("priority");
        this.appendStatementInput("do")
            .appendField("do");
        //this.setPreviousStatement(true, "behavior");
        //this.setNextStatement(true, "behavior");
        this.setTooltip('Block to design the behavior of a robot');
    },
    /**
   * Return the signature of this behavior definition.
   * @return {!Array} Tuple containing Behavior signature:
   *     - the name of the defined procedure,
   * @this Blockly.Block
   */
    getBehaviorDef: function() {
        return [this.getFieldValue('NAME')];
    },
    renameProcedure: function(oldName, newName) {
        if (Blockly.Names.equals(oldName, this.getBehaviorCall())) {
            this.setFieldValue(newName, 'NAME');
            this.setTooltip(
                (this.outputConnection ? Blockly.Msg.PROCEDURES_CALLRETURN_TOOLTIP :
                    Blockly.Msg.PROCEDURES_CALLNORETURN_TOOLTIP)
                .replace('%1', newName));
        }
    },
    getBehaviorCall: function() {
        // The NAME field is guaranteed to exist, null will never be returned.
        return /** @type {string} */ (this.getFieldValue('NAME'));
    }
};

Blockly.Blocks['behavior_composable'] = {
    init: function() {

        var priorityDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.PriorityProperties, function(option) {

        });

        var executionDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.ExecutionProperties, function(option) {
            var runUntilInput = (option == 'until');
            this.sourceBlock_.updateShape_(runUntilInput);
        });

        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(210);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField("Behavior Name")
            .appendField(new Blockly.FieldTextInput("default"), "behavior_name");
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField("Execution Priority")
            .appendField(priorityDropdown, "priorities");
        this.appendValueInput("trigger")
            .setCheck("Boolean")
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField("trigger");
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Init block");
        this.appendStatementInput("INIT_DO");
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Cyclic block");
        this.appendStatementInput("DO");
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Exit block");
        this.appendStatementInput("EXIT_DO");

        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField("Execute")
            .appendField(executionDropdown, "execution");

        this.setTooltip('');
    },
    /**
  * Create XML to represent whether the 'divisorInput' should be present.
  * @return {Element} XML storage element.
  * @this Blockly.Block
  */
    mutationToDom: function () {
        var container = document.createElement('mutation');
        var runUntilInput = (this.getFieldValue('execution') == 'until');
        container.setAttribute('run_until', runUntilInput);
        if (runUntilInput) {
            Blockly.CSharp.init(this.workspace);
            container.setAttribute('run_logic', Blockly.CSharp.valueToCode(this, 'RUN_UNTIL', Blockly.CSharp.ORDER_ATOMIC));
        } else {
            container.setAttribute('run_logic', '');
        }
        return container;
    },
    /**
     * Parse XML to restore the 'divisorInput'.
     * @param {!Element} xmlElement XML storage element.
     * @this Blockly.Block
     */
    domToMutation: function (xmlElement) {
        var runUntilInput = (xmlElement.getAttribute('run_until') == 'true');
        this.updateShape_(runUntilInput);
    },
    /**
   * Modify this block to have (or not have) an input for 'is divisible by'.
   * @param {boolean} divisorInput True if this block has a divisor input.
   * @private
   * @this Blockly.Block
   */
    updateShape_: function (runUntilInput) {
        // Add or remove a Value Input.
        var inputExists = this.getInput('RUN_UNTIL');
        if (runUntilInput) {
            if (!inputExists) {
                this.appendValueInput('RUN_UNTIL')
                    .setAlign(Blockly.ALIGN_RIGHT)
                    .appendField("Execute until condition")
                    .setCheck('Boolean');
            }
        } else if (inputExists) {
            this.removeInput('RUN_UNTIL');
        }
    }
};

Blockly.Blocks['behavior_composable_simple'] = {
    init: function () {

        var priorityDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.PriorityProperties, function (option) {

        });

        var executionDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.ExecutionProperties, function (option) {
            var runUntilInput = (option == 'until');
            this.sourceBlock_.updateShape_(runUntilInput);
        });

        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(210);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField("Behavior Name")
            .appendField(new Blockly.FieldTextInput("default"), "behavior_name");
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField("Execution Priority")
            .appendField(priorityDropdown, "priorities");
        this.appendValueInput("trigger")
            .setCheck("Boolean")
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField("trigger");
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Robot actions");
        this.appendStatementInput("DO");
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField("Execute")
            .appendField(executionDropdown, "execution");

        this.setTooltip('');
    },
    /**
  * Create XML to represent whether the 'divisorInput' should be present.
  * @return {Element} XML storage element.
  * @this Blockly.Block
  */
    mutationToDom: function () {
        var container = document.createElement('mutation');
        var runUntilInput = (this.getFieldValue('execution') == 'until');
        container.setAttribute('run_until', runUntilInput);
        if (runUntilInput) {
            Blockly.CSharp.init(this.workspace);
            container.setAttribute('run_logic', Blockly.CSharp.valueToCode(this, 'RUN_UNTIL', Blockly.CSharp.ORDER_ATOMIC));
        } else {
            container.setAttribute('run_logic', '');
        }
        return container;
    },
    /**
     * Parse XML to restore the 'divisorInput'.
     * @param {!Element} xmlElement XML storage element.
     * @this Blockly.Block
     */
    domToMutation: function (xmlElement) {
        var runUntilInput = (xmlElement.getAttribute('run_until') == 'true');
        this.updateShape_(runUntilInput);
    },
    /**
   * Modify this block to have (or not have) an input for 'is divisible by'.
   * @param {boolean} divisorInput True if this block has a divisor input.
   * @private
   * @this Blockly.Block
   */
    updateShape_: function (runUntilInput) {
        // Add or remove a Value Input.
        var inputExists = this.getInput('RUN_UNTIL');
        if (runUntilInput) {
            if (!inputExists) {
                this.appendValueInput('RUN_UNTIL')
                    .setAlign(Blockly.ALIGN_RIGHT)
                    .appendField("Execute until condition")
                    .setCheck('Boolean');
            }
        } else if (inputExists) {
            this.removeInput('RUN_UNTIL');
        }
    }
};

Blockly.Blocks['gesture_trigger'] = {
    init: function() {
        var gestureDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.GestureProperties, function(option) {
        });
        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(20);
        this.appendDummyInput()
            .appendField("When");
        this.appendDummyInput()
            .appendField(gestureDropdown);
        this.appendDummyInput()
            .appendField("count is");
        this.appendDummyInput()
            .appendField(new Blockly.FieldDropdown([["option", "OPTIONNAME"], ["option", "OPTIONNAME"], ["option", "OPTIONNAME"]]), "operators");
        this.appendValueInput("VAR")
            .setCheck("Number");
        this.setInputsInline(true);
        this.setOutput(true, "Boolean");
        this.setTooltip('');
    }
};

Blockly.Blocks['trigger'] = {
    init: function () {
        var gestureDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.GestureProperties, function (option) {
        });
        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(75);
        this.appendDummyInput()
            .appendField("Gesture : ");
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField(gestureDropdown, "MOTION_TRIGGER");
        this.setOutput(true, "Boolean");
        this.setInputsInline(true);
        this.setTooltip('Motion Trigger');
    }
};

Blockly.Blocks['voice_trigger'] = {
    init: function () {
        var voiceDropdown = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.VoiceProperties, function (option) {
        });
        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(75);
        this.appendDummyInput()
            .appendField("Speech trigger : ");
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField(voiceDropdown, "VOICE_TRIGGER");
        this.setOutput(true, "Boolean");
        this.setInputsInline(true);
        this.setTooltip('Voice Trigger');
    }
};

Blockly.Blocks['voice_trigger2'] = {
    init: function () {
        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(290);
        this.appendDummyInput()
            .appendField("Speech trigger : ");
        this.appendDummyInput()
            .appendField(new Blockly.FieldTextInput("YES"), "VOICE_TRIGGER");
        this.setOutput(true, "Boolean");
        this.setInputsInline(true);
        this.setTooltip('Voice Trigger');
    }
};

Blockly.Blocks['priority'] = {
    init: function() {
        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(100);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField(new Blockly.FieldDropdown([["High", "high"], ["Normal", "normal"], ["Low", "low"]]), "priorities");
        this.setOutput(true);
        this.setTooltip('Execution Priority');
    }
};

Blockly.Blocks['wait_voice_response'] = {
    init: function () {
        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(195);
        this.appendDummyInput()
            .appendField("Wait Voice response");
        this.appendStatementInput("DO_CHOICE1")
            .appendField("Choice 1: ")
            .appendField(new Blockly.FieldTextInput("YES"), "CHOICE1");
        this.appendStatementInput("DO_CHOICE2")
            .appendField("Choice 2: ")
            .appendField(new Blockly.FieldTextInput("NO"), "CHOICE2");
        this.setInputsInline(true);
        this.setPreviousStatement(true);
        this.setNextStatement(true);
        this.setTooltip('');
    }
};

Blockly.Blocks['robot_action'] = {
    init: function () {
        var standardBehaviors = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.StandardBehaviors, function (option) {
        });

        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(225);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField("Do ")
            .appendField(standardBehaviors, "actions");
        var robots = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.Robots, function (option) {
        });
        this.appendDummyInput()
            .appendField(" with robot: ")
            .appendField(robots, "ROBOT");
        this.setPreviousStatement(true);
        this.setInputsInline(true);
        this.setNextStatement(true, "robot_action");
        this.setTooltip('Robot Action response');
    }
};

Blockly.Blocks['set_language'] = {
    init: function () {
        var languages = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.Languages, function (option) {
        });

        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(225);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField("Set Language ")
            .appendField(languages, "language");
        var robots = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.Robots, function (option) {
        });
        this.appendDummyInput()
            .appendField(" for robot: ")
            .appendField(robots, "ROBOT");
        this.setPreviousStatement(true);
        this.setInputsInline(true);
        this.setNextStatement(true, "robot_action");
        this.setTooltip('Set the robot spoken language');
    }
};

Blockly.Blocks['turn_action'] = {
    init: function () {
        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(225);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField("Turn ")
            .appendField(new Blockly.FieldDropdown([["Left", "left"], ["Right", "right"], ["Around", "around"]]), "actions");
        var robots = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.Robots, function (option) {
        });
        this.appendDummyInput()
            .appendField(" with robot: ")
            .appendField(robots, "ROBOT");
        this.setPreviousStatement(true);
        this.setInputsInline(true);
        this.setNextStatement(true, "robot_action");
        this.setTooltip('Robot Action response');
    }
};

Blockly.Blocks['move_action'] = {
    init: function () {
        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(225);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField("Move ")
            .appendField(new Blockly.FieldTextInput("0.5"), "distance")
            .appendField("metres");
        var robots = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.Robots, function (option) {
        });
        this.appendDummyInput()
            .appendField(" with robot: ")
            .appendField(robots, "ROBOT");
        this.setPreviousStatement(true);
        this.setInputsInline(true);
        this.setNextStatement(true, "robot_action");
        this.setTooltip('Robot Action response');
    }
};

Blockly.Blocks['approach_action'] = {
    init: function() {
        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(225);
        this.appendDummyInput()
            .appendField("approach human with distance")
            .appendField(new Blockly.FieldDropdown([["2.00", "2.00"], ["1.50", "1.50"], ["1.20", "1.20"]]), "approach_distance")
            .appendField("metres");
        var robots = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.Robots, function (option) {
        });
        this.appendDummyInput()
            .appendField("with robot: ")
            .appendField(robots, "ROBOT");
        this.setInputsInline(true);
        this.setPreviousStatement(true);
        this.setNextStatement(true, "robot_action");
        this.setTooltip('Approach a human with a specified distance of separation');
    }
};

Blockly.Blocks['therapy_action'] = {
    init: function() {
        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(215);
        this.appendDummyInput()
            .appendField("Demonstrate therapy exercise ")
            .appendField(new Blockly.FieldDropdown([["Lifting left hand", "liftLeftHand"], ["Lifting right hand", "liftRightHand"]]), "therapy_exercise");
        var robots = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.Robots, function (option) {
        });
        this.appendDummyInput()
            .appendField("with robot: ")
            .appendField(robots, "ROBOT");
        this.setInputsInline(true);
        this.setPreviousStatement(true);
        this.setNextStatement(true, "robot_action");
        this.setTooltip('Demonstrate a particular therapy action');
    }
};

Blockly.Blocks['animated_say_action'] = {
    init: function() {
        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(230);
        this.appendDummyInput()
            .appendField("Say Expressively \"")
            .appendField(new Blockly.FieldTextInput("text"), "SAY_TEXT")
            .appendField("\"");
        var robots = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.Robots, function (option) {
        });
        this.appendDummyInput()
            .appendField("with robot: ")
            .appendField(robots, "ROBOT");
        this.setInputsInline(true);
        this.setPreviousStatement(true);
        this.setNextStatement(true);
        this.setTooltip('Say expressively to the human');
    }
};

Blockly.Blocks['robot_rest_action'] = {
    init: function () {
        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(230);
        this.appendDummyInput()
            .appendField("Rest ");
        var robots = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.Robots, function (option) {
        });
        this.appendDummyInput()
            .appendField(robots, "ROBOT");
        this.setInputsInline(true);
        this.setPreviousStatement(true);
        this.setNextStatement(true);
        this.setTooltip('Say expressively to the human');
    }
};

Blockly.Blocks['animated_say_action_arg'] = {
    init: function() {
        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(120);
        this.appendDummyInput()
            .appendField("Say Expressively")
            .appendField(new Blockly.FieldTextInput("default"), "PREFIX_TEXT");
        this.appendValueInput("ARG_NAME")
            .setCheck(["String", "Number"]);
        this.appendDummyInput()
            .appendField(new Blockly.FieldTextInput("!"), "SUFFIX_TEXT");
        var robots = new Blockly.FieldDropdown(Blockly.Blocks.behaviors.Robots, function (option) {
        });
        this.appendDummyInput()
            .appendField("with robot: ")
            .appendField(robots, "ROBOT");
        this.setInputsInline(true);
        this.setPreviousStatement(true);
        this.setNextStatement(true);
        this.setTooltip('');
    },
    /**
      * Create XML to represent whether the 'divisorInput' should be present.
      * @return {Element} XML storage element.
      * @this Blockly.Block
      */
    mutationToDom: function() {
        var container = document.createElement('mutation');
        //var argName = this.getInput('ARG_NAME');
        //if (argName != undefined) {
            Blockly.CSharp.init(this.workspace);
            //container.setAttribute('say_arg', argName);
            container.setAttribute('say_arg', Blockly.CSharp.valueToCode(this, 'ARG_NAME', Blockly.CSharp.ORDER_ATOMIC));
        //}
        return container;
    },
    /**
     * Parse XML to restore the 'divisorInput'.
     * @param {!Element} xmlElement XML storage element.
     * @this Blockly.Block
     */
    domToMutation: function(xmlElement) {
        //var runUntilInput = (xmlElement.getAttribute('run_until') == 'true');
        //this.updateShape_(runUntilInput);
    },
    /**
    * Modify this block to have (or not have) an input for 'is divisible by'.
    * @param {boolean} divisorInput True if this block has a divisor input.
    * @private
    * @this Blockly.Block
    */
    updateShape_: function(runUntilInput) {
        // Add or remove a Value Input.
        
    }
};

Blockly.Blocks['parallel_execute'] = {
    init: function () {
        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(20);
        this.appendStatementInput("BRANCH1")
            .appendField("ROBOT1 DO");
        this.appendStatementInput("BRANCH2")
            .appendField("ROBOT2 DO");
        this.setPreviousStatement(true);
        this.setNextStatement(true);
        this.setTooltip('');
    }
};

Blockly.Blocks['sleep_for'] = {
    init: function () {
        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(20);
        this.appendDummyInput()
            .appendField("Sleep for ")
            .appendField(new Blockly.FieldTextInput("1000"), "SLEEP_FOR");
        this.appendDummyInput()
            .appendField(" milliseconds");
        this.setInputsInline(true);
        this.setPreviousStatement(true);
        this.setNextStatement(true);
        this.setTooltip('');
    }
};

Blockly.Blocks['debug_print'] = {
    init: function () {
        this.setHelpUrl('https://github.com/praveenv4k/ExPeriMot');
        this.setColour(20);
        this.appendDummyInput()
            .appendField("Console print ")
            .appendField(new Blockly.FieldTextInput("This is a debug string"), "DEBUG_STRING");
        this.setPreviousStatement(true);
        this.setNextStatement(true);
        this.setTooltip('');
    }
};

Blockly.Blocks['trigger_logic_operation'] = {
    /**
     * Block for logical operations: 'and', 'or'.
     * @this Blockly.Block
     */
    init: function () {
        var OPERATORS =
            [[Blockly.Msg.LOGIC_OPERATION_AND, 'AND'],
             [Blockly.Msg.LOGIC_OPERATION_OR, 'OR']];
        this.setHelpUrl(Blockly.Msg.LOGIC_OPERATION_HELPURL);
        this.setColour(Blockly.Blocks.logic.HUE);
        this.setOutput(true, 'Boolean');
        this.appendValueInput('A')
            .setCheck('Boolean');
        this.appendValueInput('B')
            .setCheck('Boolean')
            .appendField(new Blockly.FieldDropdown(OPERATORS), 'OP');
        this.setInputsInline(true);
        // Assign 'this' to a variable for use in the tooltip closure below.
        var thisBlock = this;
        this.setTooltip(function () {
            var op = thisBlock.getFieldValue('OP');
            var TOOLTIPS = {
                'AND': Blockly.Msg.LOGIC_OPERATION_TOOLTIP_AND,
                'OR': Blockly.Msg.LOGIC_OPERATION_TOOLTIP_OR
            };
            return TOOLTIPS[op];
        });
    }
};