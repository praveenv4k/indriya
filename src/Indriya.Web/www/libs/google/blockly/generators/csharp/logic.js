'use strict';

//Blockly.CSharp.logic = {};

goog.provide('Blockly.CSharp.logic');

goog.require('Blockly.CSharp');

Blockly.CSharp['controls_if'] = function (block) {
  // If/elseif/else condition.
  var n = 0;
  var argument = Blockly.CSharp.valueToCode(block, 'IF' + n,
      Blockly.CSharp.ORDER_NONE) || 'false';
  var branch = Blockly.CSharp.statementToCode(block, 'DO' + n);
  var code = 'if (' + argument + ') {\n' + branch + '}';
  for (n = 1; n <= block.elseifCount_; n++) {
    argument = Blockly.CSharp.valueToCode(block, 'IF' + n,
        Blockly.CSharp.ORDER_NONE) || 'false';
    branch = Blockly.CSharp.statementToCode(block, 'DO' + n);
    code += ' else if (' + argument + ') {\n' + branch + '}\n';
  }
  if (block.elseCount_) {
    branch = Blockly.CSharp.statementToCode(block, 'ELSE');
    code += ' else {\n' + branch + '}\n';
  }
  return code + '\n';
};

  Blockly.CSharp['logic_compare'] = function(block) {
      // Comparison operator.
      // Comparison operator.
      var OPERATORS = {
          'EQ': '==',
          'NEQ': '!=',
          'LT': '<',
          'LTE': '<=',
          'GT': '>',
          'GTE': '>='
      };
      var mode = block.getFieldValue('OP');
      //var operator = Blockly.CSharp.logic_compare.OPERATORS[mode];
      var operator = OPERATORS[mode];
      var order = (operator == '==' || operator == '!=') ?
          Blockly.CSharp.ORDER_EQUALITY : Blockly.CSharp.ORDER_RELATIONAL;
      var argument0 = Blockly.CSharp.valueToCode(block, 'A', order) || 'null';
      var argument1 = Blockly.CSharp.valueToCode(block, 'B', order) || 'null';
      var code = argument0 + ' ' + operator + ' ' + argument1;
      return [code, order];
  };

//Blockly.CSharp.logic_compare.OPERATORS = {
//  EQ: '==',
//  NEQ: '!=',
//  LT: '<',
//  LTE: '<=',
//  GT: '>',
//  GTE: '>='
//};

Blockly.CSharp['logic_operation'] = function (block) {
  // Operations 'and', 'or'.
  var operator = (block.getFieldValue('OP') == 'AND') ? '&&' : '||';
  var order = (operator == '&&') ? Blockly.CSharp.ORDER_LOGICAL_AND :
      Blockly.CSharp.ORDER_LOGICAL_OR;
  var argument0 = Blockly.CSharp.valueToCode(block, 'A', order) || 'false';
  var argument1 = Blockly.CSharp.valueToCode(block, 'B', order) || 'false';
  var code = argument0 + ' ' + operator + ' ' + argument1;
  return [code, order];
};

  Blockly.CSharp['logic_negate'] = function (block) {
  // Negation.
  var order = Blockly.CSharp.ORDER_LOGICAL_NOT;
  var argument0 = Blockly.CSharp.valueToCode(block, 'BOOL', order) ||
      'false';
  var code = '!' + argument0;
  return [code, order];
};

  Blockly.CSharp['logic_boolean'] = function (block) {
  // Boolean values true and false.
  var code = (block.getFieldValue('BOOL') == 'TRUE') ? 'true' : 'false';
  return [code, Blockly.CSharp.ORDER_ATOMIC];
};

  Blockly.CSharp['logic_null'] = function (block) {
  // Null data type.
  return ['null', Blockly.CSharp.ORDER_ATOMIC];
};

Blockly.CSharp['logic_ternary'] = function (block) {
  // Ternary operator.
  var value_if = Blockly.CSharp.valueToCode(block, 'IF',
      Blockly.CSharp.ORDER_CONDITIONAL) || 'false';
  var value_then = Blockly.CSharp.valueToCode(block, 'THEN',
      Blockly.CSharp.ORDER_CONDITIONAL) || 'null';
  var value_else = Blockly.CSharp.valueToCode(block, 'ELSE',
      Blockly.CSharp.ORDER_CONDITIONAL) || 'null';
  var code = value_if + ' ? ' + value_then + ' : ' + value_else
  return [code, Blockly.CSharp.ORDER_CONDITIONAL];
};
