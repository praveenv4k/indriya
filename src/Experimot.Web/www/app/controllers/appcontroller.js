define(['app', 'backbone', 'marionette', 'collections/drawables'],
    function (app, backbone, marionette, drawables) {
        return backbone.Marionette.Controller.extend({
            initialize: function (options) {
                // BIJ Data screen items
                app.Drawables = new drawables();

                //var globalCh = Backbone.Wreqr.radio.channel('global');
                //App.StatusPoller = Poller.get(App.MachineStatus, this.pollerOptions());
                //App.StatusPoller.on('error', function (model) {
                //    globalCh.vent.trigger("serverCommunication", false);
                //    console.error('Error retrieving machine Status information from server!');
                //});
                //App.StatusPoller.start();
            },
            //gets mapped to in AppRouter's appRoutes
            //index: function () {
            //    app.mainRegion.show(new main());
            //}
            index: function () {
                require(["jquery","app", "views/designer", "views/monitor", "views/viewport"],
                    function ($, app, designer, monitor, viewport) {
                        $("#main").tabs();
                        app.tab1.show(new designer());
                        app.tab2.show(new monitor());
                        app.tab3.show(new viewport());
                    });
            }
        });
    });