'use strict';

goog.provide('Blockly.Blocks.behaviors');

goog.require('Blockly.Blocks');

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
Blockly.Blocks.behaviors.rename = function (text) {
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

Blockly.Blocks['behavior_variables_get'] = {
    /**
     * Block for variable getter.
     * @this Blockly.Block
     */
    init: function () {
        this.setHelpUrl(Blockly.Msg.VARIABLES_GET_HELPURL);
        this.setColour(Blockly.Blocks.variables.HUE);
        this.appendDummyInput()
            .appendField(Blockly.Msg.VARIABLES_GET_TITLE)
            .appendField(new Blockly.FieldVariable(
            Blockly.Msg.VARIABLES_GET_ITEM), 'VAR')
            .appendField(Blockly.Msg.VARIABLES_GET_TAIL);
        this.setOutput(true);
        this.setTooltip(Blockly.Msg.VARIABLES_GET_TOOLTIP);
        this.contextMenuMsg_ = Blockly.Msg.VARIABLES_GET_CREATE_SET;
        this.contextMenuType_ = 'behavior_variables_set';
    },
    /**
     * Return all variables referenced by this block.
     * @return {!Array.<string>} List of variable names.
     * @this Blockly.Block
     */
    getVars: function () {
        return [this.getFieldValue('VAR')];
    },
    /**
     * Notification that a variable is renaming.
     * If the name matches one of this block's variables, rename it.
     * @param {string} oldName Previous name of variable.
     * @param {string} newName Renamed variable.
     * @this Blockly.Block
     */
    renameVar: function (oldName, newName) {
        if (Blockly.Names.equals(oldName, this.getFieldValue('VAR'))) {
            this.setFieldValue(newName, 'VAR');
        }
    },
    /**
     * Add menu option to create getter/setter block for this setter/getter.
     * @param {!Array} options List of menu options to add to.
     * @this Blockly.Block
     */
    customContextMenu: function (options) {
        var option = { enabled: true };
        var name = this.getFieldValue('VAR');
        option.text = this.contextMenuMsg_.replace('%1', name);
        var xmlField = goog.dom.createDom('field', null, name);
        xmlField.setAttribute('name', 'VAR');
        var xmlBlock = goog.dom.createDom('block', null, xmlField);
        xmlBlock.setAttribute('type', this.contextMenuType_);
        option.callback = Blockly.ContextMenu.callbackFactory(this, xmlBlock);
        options.push(option);
    }
};

Blockly.Blocks['behavior_variables_set'] = {
    /**
     * Block for variable setter.
     * @this Blockly.Block
     */
    init: function () {
        this.setHelpUrl(Blockly.Msg.VARIABLES_SET_HELPURL);
        this.setColour(Blockly.Blocks.variables.HUE);
        this.interpolateMsg(
            // TODO: Combine these messages instead of using concatenation.
            Blockly.Msg.VARIABLES_SET_TITLE + ' %1 ' +
            Blockly.Msg.VARIABLES_SET_TAIL + ' %2',
            ['VAR', new Blockly.FieldVariable(Blockly.Msg.VARIABLES_SET_ITEM)],
            ['VALUE', null, Blockly.ALIGN_RIGHT],
            Blockly.ALIGN_RIGHT);
        this.setPreviousStatement(true);
        this.setNextStatement(true);
        this.setTooltip(Blockly.Msg.VARIABLES_SET_TOOLTIP);
        this.contextMenuMsg_ = Blockly.Msg.VARIABLES_SET_CREATE_GET;
        this.contextMenuType_ = 'behavior_variables_get';
    },
    /**
     * Return all variables referenced by this block.
     * @return {!Array.<string>} List of variable names.
     * @this Blockly.Block
     */
    getVars: function () {
        return [this.getFieldValue('VAR')];
    },
    /**
     * Notification that a variable is renaming.
     * If the name matches one of this block's variables, rename it.
     * @param {string} oldName Previous name of variable.
     * @param {string} newName Renamed variable.
     * @this Blockly.Block
     */
    renameVar: function (oldName, newName) {
        if (Blockly.Names.equals(oldName, this.getFieldValue('VAR'))) {
            this.setFieldValue(newName, 'VAR');
        }
    },
    customContextMenu: Blockly.Blocks['behavior_variables_get'].customContextMenu
};

Blockly.Blocks['gesture_count_up'] = {
    /**
     * Block for 'counting' loop.
     * @this Blockly.Block
     */
    init: function() {
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
        var nameText = "behavior";
        var name = Blockly.Blocks.behaviors.findLegalName(nameText, this);
        var nameField = new Blockly.FieldTextInput(name, Blockly.Blocks.behaviors.rename);

        var priorityProperties =
        [
            ["Low", 'low'],
            ["Normal", 'normal'],
            ["High", 'high']
        ];

        var priorityDropdown = new Blockly.FieldDropdown(priorityProperties, function(option) {

        });

        var executionProperties =
        [
            ["Forever", 'forever'],
            ["Once", 'once'],
            ["Until", 'until']
        ];

        var executionDropdown = new Blockly.FieldDropdown(executionProperties, function(option) {

        });

        var gestureProperties =
        [
            ["WaveLeft", 'Greet_Left'],
            ["WaveRight", 'Greet_Right'],
            ["Bow", 'Bow']
        ];

        var gestureDropdown = new Blockly.FieldDropdown(gestureProperties, function(option) {
            //var trigger = this;
            //console.log(this);
            console.log("Old Value : " + this.value_ + ", New Value : " + option);
        });

        var confidenceProperties =
        [
            ["80%", "80"],
            ["85%", "85"],
            ["90%", "90"],
            ["95%", "95"]
        ];

        var confidenceDropdown = new Blockly.FieldDropdown(confidenceProperties, function(option) {
        });

        this.setHelpUrl('http://www.example.com/');
        this.setColour(330);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Behavior Name :")
            //.appendField(new Blockly.FieldTextInput("behavior"), "behavior_name")
            .appendField(nameField, "behavior_name")
            .appendField("    Priority : ")
            .appendField(priorityDropdown, "priorities");
        this.appendDummyInput()
            .appendField("    Execute : ")
            .appendField(executionDropdown, "execution");
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Human Motion");
        this.appendDummyInput()
            .appendField("When gesture is")
            .appendField(gestureDropdown, "triggers")
            .appendField("with confidence level")
            .appendField(confidenceDropdown, "confidence_levels");
        this.appendDummyInput()
            .appendField("Init : ");
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Init Actions");
        //.appendField(new Blockly.FieldVariable());
        this.appendStatementInput("INIT_DO")
            .appendField("do");
        this.appendDummyInput()
            .appendField("");
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Robot Actions");
        this.appendStatementInput("DO")
            .appendField("do");
        //this.setPreviousStatement(true, "behavior_sleek");
        //this.setNextStatement(true, "behavior_sleek");
        this.setTooltip('');

        var doStatement = this.getInput('INIT_DO');
        console.log(doStatement);

        if (doStatement != null || doStatement != undefined) {
            // Get connection of INIT_DO
            var doConnection = doStatement.connection;
            console.log(doConnection.targetConnection);

            var itemBlock = Blockly.Block.obtain(this.workspace, 'gesture_count_up');
            itemBlock.initSvg();

            //var trigger = this.getFieldValue("triggers");

            itemBlock.setFieldValue(gestureDropdown.value_, "GESTURE_NAME");
            itemBlock.setFieldValue(gestureDropdown.value_ + 'Count', "VAR");

            console.log(itemBlock);

            if (!doConnection.targetConnection && !itemBlock.previousConnection.targetConnection) {

                //if (itemBlock.previousConnection) {
                //    doConnection.connect(itemBlock.previousConnection);
                //}

                doConnection.connect(itemBlock.previousConnection);

                //var itemBlock = Blockly.Block.obtain(this.workspace, 'variables_set');
                //itemBlock.initSvg();
                //itemBlock.setFieldValue("WaveLeft", "VAR");
                //console.log(itemBlock);
                //if (itemBlock.previousConnection) {
                //    doConnection.connect(itemBlock.previousConnection);
                //    //
                //    var numberBlock = Blockly.Block.obtain(this.workspace, 'math_number');
                //    numberBlock.initSvg();
                //    console.log(numberBlock);

                //    numberBlock.setParent(itemBlock);
                //    //itemBlock.childBlocks_.push(numberBlock);

                //    //itemBlock.inputList[0].push(numberBlock);

                //    itemBlock.inputList[0].connection.connect(numberBlock.previousConnection);

                //    //var value = itemBlock.getFieldValue('VALUE');
                //    //if (value == null) {
                //    //    itemBlock.setFieldValue(numberBlock, "VALUE");
                //    //    //console.log("Value connection not null!");
                //    //}
                //}
            } else {
                itemBlock.dispose(false);
            }
        }

        //var statementBlock = new Blockly.Block();
        //statementBlock.initialize(this.workspace, 'variables_get');
        //console.log(statementBlock);
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
    }
};

Blockly.Blocks['behavior_startup'] = {
    init: function() {
        var nameText = "Startup Behavior";

        this.setHelpUrl('http://www.example.com/');
        this.setColour(200);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Behavior Name :")
            //.appendField(new Blockly.FieldTextInput("behavior"), "behavior_name")
            .appendField(nameText);
        this.appendDummyInput()
            .appendField("");
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

        this.setHelpUrl('http://www.example.com/');
        this.setColour(400);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Behavior Name :")
            //.appendField(new Blockly.FieldTextInput("behavior"), "behavior_name")
            .appendField(nameText);
        this.appendDummyInput()
            .appendField("");
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Robot Actions");
        this.appendStatementInput("DO")
            .appendField("do");
        this.setTooltip('Behavior to define a set of actions to execute during the system shutdown');
    }
};

Blockly.Blocks['behavior'] = {
    init: function () {
        var nameText = "behavior";
        var name = Blockly.Blocks.behaviors.findLegalName(nameText, this);
        var nameField = new Blockly.FieldTextInput(name,
            Blockly.Blocks.behaviors.rename);

        if (name !== nameText) {
            console.log("Resolved name : " + name);
        }
        this.setHelpUrl('http://www.example.com/');
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
    renameProcedure: function (oldName, newName) {
        if (Blockly.Names.equals(oldName, this.getBehaviorCall())) {
            this.setFieldValue(newName, 'NAME');
            this.setTooltip(
                (this.outputConnection ? Blockly.Msg.PROCEDURES_CALLRETURN_TOOLTIP :
                 Blockly.Msg.PROCEDURES_CALLNORETURN_TOOLTIP)
                .replace('%1', newName));
        }
    },
    getBehaviorCall: function () {
        // The NAME field is guaranteed to exist, null will never be returned.
        return /** @type {string} */ (this.getFieldValue('NAME'));
    }
};

Blockly.Blocks['trigger'] = {
    init: function () {
        this.setHelpUrl('http://www.example.com/');
        this.setColour(75);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField(new Blockly.FieldDropdown([["WaveLeft", "Greet_Left"], ["WaveRight", "Greet_Right"], ["Bow", "Bow"]]), "triggers");
        this.setOutput(true);
        this.setTooltip('Motion Trigger');
    }
};

Blockly.Blocks['priority'] = {
    init: function () {
        this.setHelpUrl('http://www.example.com/');
        this.setColour(100);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField(new Blockly.FieldDropdown([["High", "high"], ["Normal", "normal"], ["Low", "low"]]), "priorities");
        this.setOutput(true);
        this.setTooltip('Execution Priority');
    }
};

Blockly.Blocks['robot_action'] = {
    init: function() {
        this.setHelpUrl('http://www.example.com/');
        this.setColour(225);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField(new Blockly.FieldDropdown([["Greet", "greet"], ["Crouch", "crouch"], ["Stand", "stand"], ["Wish", "wish"], ["LabIntroduction", "introduction"]]), "actions");
        this.setPreviousStatement(true);
        this.setNextStatement(true, "robot_action");
        this.setTooltip('Robot Action response');
    }
};