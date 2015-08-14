// programSelectModal.js
// Praveenkumar VASUDEVAN
define(['app', 'underscore', 'backbone', 'marionette', 'jquery', 'text!templates/programSelectModal.html', 'backboneMarionetteModals'],
    function(app, _, Backbone, Marionette, $, template) {
        //ItemView provides some default rendering logic
        return Backbone.Modal.extend({
            template: _.template(template),
            // View Event Handlers
            events: {
                'click .open-button' : 'onOpen'
            },
            onOpen: function() {
                console.log("Open clicked " + this.selectedIndex);
                if (this.selectedIndex != undefined) {
                    var model = this.collection.at(this.selectedIndex);
                    console.log("Selected Item : " + model.get("name"));
                    var globalCh = Backbone.Wreqr.radio.channel('global');
                    globalCh.vent.trigger("loadProgram", model);
               }
            },
            selectedIndex : undefined,
            onShow: function () {
                var _this = this;
                console.log(this.collection);
                //$("#header ul").append('<li><a href="/user/messages"><span class="tab">Message Center</span></a></li>');
                //<li class="ui-widget-content">Item 1</li>
                _.each(this.collection.models, function(model) {
                    //console.log(model.get("description"));
                    $("#program-list").append('<li class="ui-widget-content program-list-item">' + model.get('name') + '</li>');
                });
                
                $("#program-list").selectable({
                    stop: function () {
                        var result = $("#select-program").empty();
                        $(".ui-selected", this).each(function () {
                            var index = $("#program-list li").index(this);
                            _this.selectedIndex = index;
                            result.append(" #" + (index + 1));
                        });
                    }
                });
            },
            submitEl: '.bbm-button'

        });
    });