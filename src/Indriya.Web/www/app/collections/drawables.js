// drawables.js
// Praveenkumar VASUDEVAN
define(['jquery', 'underscore', 'backbone', 'marionette', 'marionette_threejs'],
    function($, _, Backbone, Marionette, m3Js) {
        var drawables = Backbone.Collection.extend({
            model: m3Js.Drawable
        });
        return drawables;
    });

