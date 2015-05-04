Blockly.Blocks['behavior'] = {
    init: function () {
        this.setHelpUrl('http://www.example.com/');
        this.setColour(300);
        this.appendValueInput("when")
            .setCheck("trigger")
            .appendField("when");
        this.appendStatementInput("do")
            .appendField("do");
        this.setPreviousStatement(true);
        this.setNextStatement(true);
        this.setTooltip('');
    }
};