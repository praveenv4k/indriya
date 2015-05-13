define(['app', 'underscore', 'backbone', 'marionette', 'jquery', 'text!templates/programSelectModal.html', 'backboneMarionetteModals'],
    function(app, _, Backbone, Marionette, $, template) {
        //ItemView provides some default rendering logic
        return Backbone.Modal.extend({
            template: _.template(template),
            // View Event Handlers
            events: {

            },
            submitEl: '.bbm-button'

        });
        //return Marionette.Modals.extend({
        //    template: _.template(template),
        //    // View Event Handlers
        //    events: {

        //    },
        //    submitEl: '.bbm-button'

        //});
    });