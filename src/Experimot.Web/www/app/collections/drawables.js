define(['jquery', 'underscore', 'backbone', 'marionette', 'marionette_threejs'],
    function ($,_, Backbone, Marionette, m3Js) {
        //ItemView provides some default rendering logic
        var drawables = Backbone.Collection.extend({
            model: m3Js.Drawable
        });
        return drawables;
    });

