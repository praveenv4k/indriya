'use strict';

goog.provide('Blockly.CSharp.colour');

goog.require('Blockly.CSharp');

Blockly.CSharp['colour_picker'] = function(block) {
    // Colour picker.
    var code = 'ColorTranslator.FromHtml("' + block.getFieldValue('COLOUR') + '")';
    return [code, Blockly.CSharp.ORDER_ATOMIC];
};

Blockly.CSharp['colour_random'] = function(block) {
  // Generate a random colour.
  if (!Blockly.CSharp.definitions_['colour_random']) {
    var functionName = Blockly.CSharp.variableDB_.getDistinctName(
        'colour_random', Blockly.Generator.NAME_TYPE);
    Blockly.CSharp.colour_random.functionName = functionName;
    var func = [];
    func.push('var ' + functionName + ' = new Func<Color>(() => {');
    func.push('  var random = new Random();');
    func.push('  var res = Color.FromArgb(1, random.Next(256), random.Next(256), random.Next(256));');
    func.push('  return res;');
    func.push('});');
    Blockly.CSharp.definitions_['colour_random'] = func.join('\n');
  }
  var code = Blockly.CSharp.colour_random.functionName + '()';
  return [code, Blockly.CSharp.ORDER_FUNCTION_CALL];
};

Blockly.CSharp['colour_rgb'] = function(block) {
  // Compose a colour from RGB components expressed as percentages.
    var red = Blockly.CSharp.valueToCode(block, 'RED',
      Blockly.CSharp.ORDER_COMMA) || 0;
    var green = Blockly.CSharp.valueToCode(block, 'GREEN',
      Blockly.CSharp.ORDER_COMMA) || 0;
    var blue = Blockly.CSharp.valueToCode(block, 'BLUE',
      Blockly.CSharp.ORDER_COMMA) || 0;

  if (!Blockly.CSharp.definitions_['colour_rgb']) {
    var functionName = Blockly.CSharp.variableDB_.getDistinctName(
        'colour_rgb', Blockly.Generator.NAME_TYPE);
    Blockly.CSharp.colour_rgb.functionName = functionName;
    var func = [];
    func.push('var ' + functionName + ' = new Func<dynamic, dynamic, dynamic, Color>((r, g, b) => {');
    func.push('  r = (int)Math.Round(Math.Max(Math.Min((int)r, 100), 0) * 2.55);');
    func.push('  g = (int)Math.Round(Math.Max(Math.Min((int)g, 100), 0) * 2.55);');
    func.push('  b = (int)Math.Round(Math.Max(Math.Min((int)b, 100), 0) * 2.55);');
    func.push('  var res = Color.FromArgb(1, r, g, b);');
    func.push('  return res;');
    func.push('});');
    Blockly.CSharp.definitions_['colour_rgb'] = func.join('\n');
  }
  var code = Blockly.CSharp.colour_rgb.functionName +
      '(' + red + ', ' + green + ', ' + blue + ')';
  return [code, Blockly.CSharp.ORDER_FUNCTION_CALL];
};

Blockly.CSharp['colour_blend'] = function (block) {
  // Blend two colours together.
    var c1 = Blockly.CSharp.valueToCode(block, 'COLOUR1',
      Blockly.CSharp.ORDER_COMMA) || 'Color.Black';
    var c2 = Blockly.CSharp.valueToCode(block, 'COLOUR2',
      Blockly.CSharp.ORDER_COMMA) || 'Color.Black';
    var ratio = Blockly.CSharp.valueToCode(block, 'RATIO',
      Blockly.CSharp.ORDER_COMMA) || 0.5;

  if (!Blockly.CSharp.definitions_['colour_blend']) {
    var functionName = Blockly.CSharp.variableDB_.getDistinctName(
        'colour_blend', Blockly.Generator.NAME_TYPE);
    Blockly.CSharp.colour_blend.functionName = functionName;
    var func = [];
    func.push('var ' + functionName + ' = new Func<Color, Color, double, Color>((c1, c2, ratio) => {');
    func.push('  ratio = Math.Max(Math.Min((double)ratio, 1), 0);');
    func.push('  var r = (int)Math.Round(c1.R * (1 - ratio) + c2.R * ratio);');
    func.push('  var g = (int)Math.Round(c1.G * (1 - ratio) + c2.G * ratio);');
    func.push('  var b = (int)Math.Round(c1.B * (1 - ratio) + c2.B * ratio);');
    func.push('  var res = Color.FromArgb(1, r, g, b);');
    func.push('  return res;');
    func.push('});');
    Blockly.CSharp.definitions_['colour_blend'] = func.join('\n');
  }
  var code = Blockly.CSharp.colour_blend.functionName +
      '(' + c1 + ', ' + c2 + ', ' + ratio + ')';
  return [code, Blockly.CSharp.ORDER_FUNCTION_CALL];
};
