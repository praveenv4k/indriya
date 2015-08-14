// saveDialog.js
// Praveenkumar VASUDEVAN
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
                var name = $("#program-save-text").val();
                console.log("Save clicked " + name);
                if (name.indexOf(".xml") >= 0) {

                } else {
                    name = name + ".xml";
                }
                var globalCh = Backbone.Wreqr.radio.channel('global');
                globalCh.vent.trigger("saveProgram", name);
            },
            onShow: function () {
                var name = "";
                console.log(this.model);
                if (this.model != undefined) {
                    name = this.model.get('name');
                }
                if (name === "") {
                    var d = new Date($.now());
                    name = d.getYear() + d.getMonth() + d.getDay() + "_" + d.getHours() + d.getMinutes() + d.getSeconds();
                }
                $("#program-save-text").val(name);
            },
            submitEl: '.bbm-button'

        });
    });