define(['app', 'backbone', 'marionette', 'models/robot', 'models/testjointvalues', 'models/JointValues', 'collections/drawables', 'marionette_threejs', 'poller','views/programSelectModal','collections/programs'],
    function (app, backbone, marionette, robot,testJointVals,jointVals, drawables, m3Js,poller,openDialog,programs) {
        return backbone.Marionette.Controller.extend({
            initialize: function (options) {
                app.programs = new programs();
                app.Drawables = new drawables();

                this.listenTo(app.Drawables, "drawable:loaded", function(drawable) {
                    app.kinematics = drawable.getKinematics();
                });

                app.renderer = new m3Js.ThreeJSRenderer({
                    collection: app.Drawables
                });
                app.loader = new THREE.ColladaLoader();
                app.loader.options.convertUpAxis = true;

                var globalCh = Backbone.Wreqr.radio.channel('global');

                globalCh.vent.on("loadProgram", function(model) {
                    $.ajax({
                        url: model.get('path'),
                        dataType: "text",
                        success: function (data) {
                            console.log(data);
                            //console.log(app.workspace);
                            app.codeXmlDom = Blockly.Xml.textToDom(data);
                            Blockly.Xml.domToWorkspace(app.workspace, app.codeXmlDom);
                            var name = $("#program-name").empty();
                            name.append(model.get('name'));
                            //program - name
                            //console.log(app.workspace);
                            //app.codeXmlDom = data;
                            //Blockly.Xml.domToWorkspace(app.workspace, app.codeXmlDom);
                        }
                    });
                });

                app.robot = new robot();

                app.robotpoller = poller.get(app.robot, this.pollerOptions());
                app.robotpoller.on('error', function(model) {
                    globalCh.vent.trigger("serverCommunication", false);
                    console.error('Error retrieving Robot Status information from server!');
                });
                app.robotpoller.start();


                // Test Joint values poller
                var test_joint_options = {

                    // default delay is 1000ms
                    delay: 200,

                    // run after a delayed interval. defaults to false
                    // can be a boolean `true` to wait `delay` ms before starting or a number to override the wait period
                    delayed: 3000,

                    // do not stop the poller on error. defaults to false
                    // `error` event is always fired even with this option on.
                    continueOnError: false,

                    // condition for keeping polling active (when this stops being true, polling will stop)
                    //condition: function(model) {
                    //    return model.id === -1;
                    //}
                }

                //var _this = this;
                //app.testJointVals = new testJointVals();

                //app.testjointpoller = poller.get(app.testJointVals, test_joint_options);
                //app.testjointpoller.on('error', function (model) {
                //    globalCh.vent.trigger("serverCommunication", false);
                //    console.error('Error retrieving Robot Status information from server!');
                //});
                //app.testjointpoller.on('success', function(model) {
                //    _this.setJointVals(model);
                //    app.testJointVals.id = app.testJointVals.id + 1;
                //});
                //app.testjointpoller.on('complete', function (model) {
                //    console.log("Done !!!");
                //    //app.testJointVals.id = app.testJointVals.id + 1;
                //});
                //app.testjointpoller.start();

                var _this = this;
                app.jointVals = new jointVals();

                app.jointpoller = poller.get(app.jointVals, test_joint_options);
                app.jointpoller.on('error', function (model) {
                    globalCh.vent.trigger("serverCommunication", false);
                    console.error('Error retrieving Robot Status information from server!');
                });
                app.jointpoller.on('success', function (model) {
                    _this.setJointVals(model);
                });
                app.jointpoller.on('complete', function (model) {
                    console.log("Done !!!");
                });
                app.jointpoller.start();
            },

            setJointVals: function(jointModel) {
                if (jointModel != undefined && app.kinematics != undefined) {
                    for (var i = 0; i < 25; i++) {
                        app.kinematics.setJointValue(i, this.degrees(jointModel.get(i)),false);
                    }
                }
            },

            degrees: function(radians) {
                return radians * 180 / Math.PI;        
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
                $("#run").button({
                        text: true,
                        icons: {
                            primary: "ui-icon-play"
                        }
                    })
                    .click(function() {
                        var options;

                        if ($(this).text() === "RUN") {

                            app.code = Blockly.CSharp.workspaceToCode(app.workspace); // C# code generation
                            //$.post("/designer/program/start", app.code, function (data) {
                            //    console.log("Program Sent & Started: " + data);
                            //});
                            console.log(app.code);

                            app.codeXmlDom = Blockly.Xml.workspaceToDom(app.workspace);
                            var xmlText = Blockly.Xml.domToPrettyText(app.codeXmlDom);
                            $.post("/designer/program/startxml", xmlText, function(data) {
                                console.log("Program Sent & Started: " + data);
                            });

                            options = {
                                label: "STOP",
                                icons: {
                                    primary: "ui-icon-stop"
                                }
                            };
                        } else {

                            $.post("/designer/program/stop", function(data) {
                                console.log("Program Stopped: " + data);
                            });

                            options = {
                                label: "RUN",
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
                            //app.code = Blockly.Python.workspaceToCode(app.workspace);
                            app.code = Blockly.CSharp.workspaceToCode(app.workspace); // C# code generation
                            $.post("/designer/program/code", app.code, function(data) {
                                console.log("Sent Program: " + data);
                            });
                            console.log(app.code);

                            app.codeXmlDom = Blockly.Xml.workspaceToDom(app.workspace);
                            var xmlText = Blockly.Xml.domToPrettyText(app.codeXmlDom);
                            console.log(xmlText);
                            console.log(app.code);
                        }
                    });
                $("#open").button({
                        text: true,
                        icons: {
                            primary: "ui-icon-document"
                        }
                    })
                    .click(function () {
                        app.programs.fetch({
                            success: function() {
                                var dialog = new openDialog({
                                    collection: app.programs
                                });
                                //console.log(dialog);
                                app.modals.show(dialog);
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