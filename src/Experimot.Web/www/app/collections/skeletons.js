// Model.js
// --------
define(["jquery", "backbone", "models/skeleton"],
    function($, backbone, model) {

        // Creates a new Backbone Model class object
        var programs = backbone.Collection.extend({
            model: model,
            url: '/visualize/skeleton/list'
        });

        // Returns the Model class
        return programs;

    }
);