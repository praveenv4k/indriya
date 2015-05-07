Blockly.Blocks['behavior'] = {
    init: function() {
        this.setHelpUrl('http://www.example.com/');
        this.setColour(300);
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
            .appendField(new Blockly.FieldDropdown([["WaveLeft", "wave_left"], ["WaveRight", "wave_right"], ["Bow", "bow"]]), "triggers");
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
    init: function () {
        this.setHelpUrl('http://www.example.com/');
        this.setColour(225);
        this.appendDummyInput()
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendField(new Blockly.FieldDropdown([["Greet", "greet"], ["Crouch", "crouch"], ["Stand", "stand"]]), "actions");
        this.setPreviousStatement(true);
        this.setNextStatement(true, "robot_action");
        this.setTooltip('Robot Action response');
    }
};