// programs.js
// Praveenkumar VASUDEVAN
define(["jquery", "backbone", "models/program"],
    function($, backbone, model) {
        var programs = backbone.Collection.extend({
            model: model,
            url: '/designer/program/list',

        });
        return programs;
    });