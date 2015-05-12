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

Blockly.Blocks['behavior_sleek'] = {
    init: function () {
        var nameText = "behavior";
        var name = Blockly.Blocks.behaviors.findLegalName(nameText, this);
        var nameField = new Blockly.FieldTextInput(name,Blockly.Blocks.behaviors.rename);

        this.setHelpUrl('http://www.example.com/');
        this.setColour(330);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Behavior Name :")
            //.appendField(new Blockly.FieldTextInput("behavior"), "behavior_name")
            .appendField(nameField, "behavior_name")
            .appendField("    Priority : ")
            .appendField(new Blockly.FieldDropdown([["Low", "low"], ["Normal", "normal"], ["High", "high"]]), "priorities");
        this.appendDummyInput();
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Human Motion");
        this.appendDummyInput()
            .appendField("When gesture is")
            .appendField(new Blockly.FieldDropdown([["WaveLeft", "Greet_Left"], ["WaveRight", "Greet_Right"], ["Bow", "Bow"]]), "triggers")
            .appendField("with confidence level")
            .appendField(new Blockly.FieldDropdown([["80%", "80"], ["85%", "85"], ["90%", "90"], ["95%", "95"]]), "confidence_levels");
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
            .appendField(new Blockly.FieldDropdown([["Greet", "greet"], ["Crouch", "crouch"], ["Stand", "stand"], ["Wish", "wish"]]), "actions");
        this.setPreviousStatement(true);
        this.setNextStatement(true, "robot_action");
        this.setTooltip('Robot Action response');
    }
};