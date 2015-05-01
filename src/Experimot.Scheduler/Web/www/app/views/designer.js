﻿define(['app', 'underscore', 'backbone', 'marionette', 'jquery', 'text!templates/designer.html'],
    function (app, _, backbone, marionette, $, template) {
        //ItemView provides some default rendering logic
        return backbone.Marionette.ItemView.extend({
            template: _.template(template),
            // View Event Handlers
            events: {

            }
        });
    });