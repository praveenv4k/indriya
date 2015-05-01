define(['underscore', 'backbone', 'marionette', 'jquery', 'marionette_threejs'],
    function(_, backbone, marionette, $, m3Js) {
        //ItemView provides some default rendering logic
        var drawables = backbone.Collection.extend({
            model: m3Js.Drawable
        });
        return drawables;
    });

