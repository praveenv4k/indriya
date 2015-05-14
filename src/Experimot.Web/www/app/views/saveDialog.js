define(['app', 'underscore', 'backbone', 'marionette', 'jquery', 'text!templates/saveDialog.html', 'backboneMarionetteModals'],
    function(app, _, Backbone, Marionette, $, template) {
        //ItemView provides some default rendering logic
        return Backbone.Modal.extend({
            template: _.template(template),
            // View Event Handlers
            events: {
                'click .save-button': 'onSave'
            },
            onSave: function() {
                console.log("Save clicked " + $("#program-save-text").text());
                var globalCh = Backbone.Wreqr.radio.channel('global');
                globalCh.vent.trigger("saveProgram", $("#program-save-text").val());
            },
            onShow: function () {
                var name = "";
                if (this.programName != undefined) {
                    if (this.programName !== "none") {
                        name = this.programName;
                    }                       
                }
                //result = $("#program-save-text").empty();
                if (name === "") {
                    var d = new Date($.now());
                    name = d.getFullYear() + d.getMonth() + d.getDay() + "_" + d.getHours() + d.getMinutes() + d.getSeconds();
                }
                $("#program-save-text").val(name);
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