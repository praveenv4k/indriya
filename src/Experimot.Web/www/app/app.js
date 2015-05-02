define(['jquery', 'backbone', 'marionette', 'underscore'],
    function($, Backbone, Marionette, _) {
        var app = new Backbone.Marionette.Application();

        function isMobile() {
            var userAgent = navigator.userAgent || navigator.vendor || window.opera;
            return ((/iPhone|iPod|iPad|Android|BlackBerry|Opera Mini|IEMobile/).test(userAgent));
        }

        //Organize Application into regions corresponding to DOM elements
        //Regions can contain views, Layouts, or subregions nested as necessary
        app.addRegions({
            tab1: "#tabs-1",
            tab2: "#tabs-2",
            viewport: "#viewport-anchor"
        });

        app.addInitializer(function() {
            Backbone.history.start();
        });

        app.mobile = isMobile();

        return app;
    });