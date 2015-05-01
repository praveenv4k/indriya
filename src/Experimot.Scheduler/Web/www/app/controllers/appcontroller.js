define(['app', 'backbone', 'marionette', 'views/main'],
    function (app, backbone, marionette, main) {
        return backbone.Marionette.Controller.extend({
            initialize: function (options) {
                console.log(options);
                //App.headerRegion.show(new DesktopHeaderView());
            },
            //gets mapped to in AppRouter's appRoutes
            index: function () {
                app.mainRegion.show(new main());
            }
        });
    });