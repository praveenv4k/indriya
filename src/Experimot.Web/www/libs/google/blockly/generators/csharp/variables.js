'use strict';

//Blockly.CSharp.variables = {};

goog.provide('Blockly.CSharp.variables');

goog.require('Blockly.CSharp');

Blockly.CSharp['variables_get'] = function(block) {
  // Variable getter.
  var code = Blockly.CSharp.variableDB_.getName(block.getFieldValue('VAR'),
      Blockly.Variables.NAME_TYPE);
  return [code, Blockly.CSharp.ORDER_ATOMIC];
};

Blockly.CSharp['variables_set'] = function (block) {
  // Variable setter.
  var argument0 = Blockly.CSharp.valueToCode(block, 'VALUE',
      Blockly.CSharp.ORDER_ASSIGNMENT) || 'null';
  var varName = Blockly.CSharp.variableDB_.getName(
      block.getFieldValue('VAR'), Blockly.Variables.NAME_TYPE);
  return varName + ' = ' + argument0 + ';\n';
};
