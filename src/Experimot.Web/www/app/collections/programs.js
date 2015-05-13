// Model.js
// --------
define(["jquery", "backbone","models/program"],

    function ($, backbone,model) {

        // Creates a new Backbone Model class object
        var programs = backbone.Collection.extend({

            model: model,
            url: '/designer/program/list',

        });

        // Returns the Model class
        return programs;

    }

);