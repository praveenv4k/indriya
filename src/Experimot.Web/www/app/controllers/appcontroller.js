define(['app', 'backbone', 'marionette', 'models/robot', 'collections/drawables', 'marionette_threejs', 'poller'],
    function (app, backbone, marionette, robot, drawables, m3Js,poller) {
        return backbone.Marionette.Controller.extend({
            initialize: function (options) {
                app.Drawables = new drawables();
                app.renderer = new m3Js.ThreeJSRenderer({
                    collection: app.Drawables
                });
                app.loader = new THREE.ColladaLoader();
                app.loader.options.convertUpAxis = true;

                var globalCh = Backbone.Wreqr.radio.channel('global');

                app.robot = new robot();

                app.robotpoller = poller.get(app.robot, this.pollerOptions());
                app.robotpoller.on('error', function (model) {
                    globalCh.vent.trigger("serverCommunication", false);
                    console.error('Error retrieving machine Status information from server!');
                });
                app.robotpoller.start();
            },

            index: function () {
                var _this = this;
                require(["jquery", "app", "views/designer", "views/monitor"],
                    function ($, app, designer, monitor) {
                        _this.initCodeMenu();
                        //app.designer.show(new designer());
                        app.monitor.show(new monitor());
                        //app.viewport.show(app.renderer);
                        app.viewport.show(app.renderer);
                        app.workspace = Blockly.inject('blocklyDiv', {
                            grid:
                            {
                                spacing: 25,
                                length: 3,
                                colour: '#ccc',
                                snap: true
                            },
                            media: '../libs/google/blockly/media/',
                            toolbox: document.getElementById('toolbox')
                        });

                        $("#tabs").tabs();

                        _this.createNewDrawable({
                            colladaUrl: "models/collada/nao.dae"
                        });
                    });
            },

            initCodeMenu: function() {
                $("#play").button({
                        text: true,
                        icons: {
                            primary: "ui-icon-play"
                        }
                    })
                    .click(function() {
                        var options;
                        if ($(this).text() === "PLAY") {
                            $.post("/designer/program/start", function (data) {
                                console.log("Program Started: " + data);
                            });

                            options = {
                                label: "PAUSE",
                                icons: {
                                    primary: "ui-icon-pause"
                                }
                            };
                        } else {
                            options = {
                                label: "PLAY",
                                icons: {
                                    primary: "ui-icon-play"
                                }
                            };
                        }
                        $(this).button("option", options);
                    });
                //ui-icon-document
                $("#code").button({
                    text: true,
                    icons: {
                        primary: "ui-icon-document"
                    }
                })
                .click(function() {
                    if (app.workspace != undefined) {
                        app.code = Blockly.Python.workspaceToCode(app.workspace);
                        //app.code = Blockly.CSharp.workspaceToCode(app.workspace); // C# code generation
                        $.post("/designer/program/code", app.code, function (data) {
                            console.log("Program Started: " + data);
                        });
                        console.log(app.code);
                    }
                });
                $("#stop").button({
                        text: true,
                        icons: {
                            primary: "ui-icon-stop"
                        }
                    })
                    .click(function () {
                        $.post("/designer/program/stop", function (data) {
                            console.log("Program Stopped: " + data);
                        });
                        $("#play").button("option", {
                            label: "PLAY",
                            icons: {
                                primary: "ui-icon-play"
                            }
                        });
                    });
            },


            createNewDrawable: function(options) {

                var newDrawable = new m3Js.Drawable(options);
                app.Drawables.add(newDrawable);
            },

            pollerOptions: function () {
                var options = {

                    // default delay is 1000ms
                    delay: 100,

                    // run after a delayed interval. defaults to false
                    // can be a boolean `true` to wait `delay` ms before starting or a number to override the wait period
                    delayed: 1000,

                    // do not stop the poller on error. defaults to false
                    // `error` event is always fired even with this option on.
                    continueOnError: false,

                    // condition for keeping polling active (when this stops being true, polling will stop)
                    //condition: function (model) {
                    //    return model.get('active') === true;
                    //},

                    // We can pass data to a fetch request
                    //data: { fields: "*", sort: "name asc" }
                }
            }
        });
    });