define(['app', 'backbone', 'marionette', 'views/main'],
    function (app, backbone, marionette, main) {
        return backbone.Marionette.Controller.extend({
            initialize: function (options) {
                console.log(options);
                //App.headerRegion.show(new DesktopHeaderView());
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