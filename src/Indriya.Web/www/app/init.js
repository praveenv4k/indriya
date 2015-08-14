require.config({
    paths: {
        jquery: "../libs/jquery/jquery-2.1.3.min",
        jqueryui: "../libs/jquery-ui/jquery-ui.min",
        underscore: "../libs/underscore/underscore-min",
        backbone: "../libs/backbone/backbone-min",
        marionette: "../libs/marionette/backbone.marionette",
        'backbone.marionette': "../libs/marionette/backbone.marionette", //alias
        poller: "../libs/backbone.poller/backbone.poller.min",
        text: "../libs/requirejs/text",
        jsonview: "../libs/jquery-jsonview/jquery.jsonview",
        blockly: "../libs/google/blockly/blockly_compressed",
        blocks: "../libs/google/blockly/blocks_compressed",
        blockly_msg_en: "../libs/google/blockly/msg/js/en",
        blockly_python: "../libs/google/blockly/python_compressed",
        blockly_csharp: "../libs/google/blockly/csharp_compressed"
        // r68
        //, threejs: "../libs/threejs/r68/three"
        //, colladaloader: "../libs/threejs/r68/ColladaLoader"
        // r71
        ,
        threejs: "../libs/threejs/three",
        orbitcontrols: "../js/controls/OrbitControls",
        projector: "../js/renderers/Projector",
        colladaloader: "../js/loaders/ColladaLoader",
        marionette_threejs: "../libs/marionette-threejs/marionette-threejs"
        // Backbone Marionette modal
        ,
        backboneModal: "../libs/backbone.modal/backbone.modal-min",
        backboneMarionetteModals: "../libs/backbone.modal/backbone.marionette.modals"
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
            exports: "Marionette"
        },
        "backbone.marionette": {
            "deps": ["underscore", "backbone", "jquery"],
            exports: "Marionette"
        },
        // Underscore
        "underscore": {
            exports: "_"
        },
        // Backbone Modal
        "backboneModal": {
            "deps": ["underscore", "backbone", "jquery"]
        },
        // Backbone Marionette Modal
        "backboneMarionetteModals": {
            "deps": ["marionette", "backboneModal"]
        },
        // Json-view
        "jsonview": {
            "deps": ["jquery"]
        },
        // Blockly - Blocks
        "blocks": {
            "deps": ["blockly"]
        },
        // Blockly - Msgs
        "blockly_msg_en": {
            "deps": ["blocks"]
        },
        // Python code generation
        "blockly_python": {
            "deps": ["blockly", "blocks"]
        },
        // Python code generation
        "blockly_csharp": {
            "deps": ["blockly", "blocks"]
        },
        // Marionette Three JS
        "threejs": {
            exports: "THREE"
        },
        // Marionette Three JS
        "marionette_threejs": {
            "deps": ["threejs"]
        },
        "colladaloader": {
            "deps": ["threejs"]
        },
        "projector": {
            "deps": ["threejs"]
        }
    }
});

require([
        "app", "jquery", "routers/approuter", "controllers/appcontroller", "backbone", "marionette", "jqueryui",
        "blocks", "blockly_msg_en", "colladaloader", "projector", "blockly_python", "blockly_csharp", "backboneModal", "backboneMarionetteModals"
    ],
    function(app, $, router, controller) {
        app.appRouter = new router({
            controller: new controller()
        });
        app.start();
    });