require.config({
    paths: {
        jquery: "../libs/jquery/jquery-2.1.1",
        jquerymobile: "../libs/jquery-ui/jquery-ui.js",
        underscore: "../libs/underscore/underscore",
        backbone: "../libs/backbone/backbone",
        marionette: "../libs/marionette/backbone.marionette",
        poller: "../libs/backbone.poller/backbone.poller",
        text: "../libs/requirejs/text",
        joint: "../libs/joint/joint.nojquerynobackbone",
        slidebars: "../libs/slidebars/slidebars",
        threejs: "../libs/threejs/threejs",
        jsonview: "../libs/jquery-jsonview",
        blockly: "../libs/blockly_compressed",
        blocks: "../libs/blocks_compressed"
    },
    shim: {
        // jQueryUI
        "jqueryui": ["jquery"],
        // Backbone
        "backbone": {
            deps: ["jquery", "underscore"],
            exports: "Backbone"
        },
        //Marionette
        "marionette": {
            "deps": ["underscore", "backbone", "jquery"],
            "exports": "Marionette"
        },
        // Underscore
        "underscore": {
            exports: "_"
        },
        // Joint JS
        "joint": {
            "deps": ["underscore", "backbone", "jquery"],
            "exports": "Joint"
        },
        // Json-view
        "jsonview": {
            "deps": ["jquery"]
        },
        "blocks": {
            "deps": ["blockly"]
        }
    }
});

// Include Desktop Specific JavaScript files here (or inside of your Desktop Controller, or differentiate based off App.mobile === false)
require(["app", "jquery", "routers/approuter", "controllers/appcontroller", "backbone", "marionette", "jqueryui"],
    function(app, $, appRouter, appController) {
        $.mobile.ajaxEnabled = false;
        // Prevents all anchor click handling
        $.mobile.linkBindingEnabled = false;
        // Disabling this will prevent jQuery Mobile from handling hash changes
        $.mobile.hashListeningEnabled = false;
        //        $.mobile.ajaxEnabled = false;
        $.mobile.pushStateEnabled = false;

        app.appRouter = new appRouter({
            controller: new appController()
        });
        app.start();
    });