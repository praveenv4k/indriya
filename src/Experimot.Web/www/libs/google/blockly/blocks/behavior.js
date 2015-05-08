Blockly.Blocks['behavior_sleek'] = {
    init: function() {
        this.setHelpUrl('http://www.example.com/');
        this.setColour(330);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_CENTRE)
            .appendField("Behavior Name :")
            .appendField(new Blockly.FieldTextInput("behavior"), "behavior_name")
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
        this.setPreviousStatement(true, "behavior_sleek");
        this.setNextStatement(true, "behavior_sleek");
        this.setTooltip('');
    }
};

Blockly.Blocks['behavior'] = {
    init: function() {
        this.setHelpUrl('http://www.example.com/');
        this.setColour(300);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField(new Blockly.FieldTextInput("behavior"), "NAME");
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
        this.setPreviousStatement(true, "behavior");
        this.setNextStatement(true, "behavior");
        this.setTooltip('Block to design the behavior of a robot');
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