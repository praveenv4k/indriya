// viewport.js
// Praveenkumar VASUDEVAN
define(['app', 'jquery', 'underscore', 'backbone', 'marionette', 'marionette_threejs', 'text!templates/viewport.html'],
    function(app, $, _, Backbone, Marionette, m3Js, template) {
        var renderer = new m3Js.ThreeJSRenderer({
            collection: app.Drawables
        });
        return renderer;
    });