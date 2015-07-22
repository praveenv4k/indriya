define(['app', 'backbone', 'marionette', 'models/robot', 'models/testjointvalues', 'models/JointValues', 'collections/drawables', 'collections/skeletons', 'marionette_threejs', 'poller',
    'views/programSelectModal',
    'views/saveDialog',
    'collections/programs', 'jsonview'],
    function (app, backbone, marionette, robot,testJointVals,jointVals, drawables,skeletons, m3Js,poller,openDialog,saveDialog,programs) {
        return backbone.Marionette.Controller.extend({
            initialize: function(options) {
                var _this = this;
                app.programs = new programs();
                app.Drawables = new drawables();

                app.renderer = new m3Js.ThreeJSRenderer({
                    collection: app.Drawables
                });

                this.listenTo(app.Drawables, "drawable:loaded", function (drawable) {
                    console.log(drawable);
                    console.log('added');
                    var kin = drawable.getKinematics();
                    if (kin != undefined) {
                        app.kinematics = drawable.getKinematics();
                    }
                });

                //app.renderer.disableTransformControl();
                app.loader = new THREE.ColladaLoader();
                app.loader.options.convertUpAxis = true;

                var globalCh = Backbone.Wreqr.radio.channel('global');

                globalCh.vent.on("loadProgram", function(model) {
                    $.ajax({
                        url: model.get('path'),
                        dataType: "text",
                        success: function(data) {
                            _this.clearWorkspace();
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

                globalCh.vent.on("saveProgram", function(name) {
                    app.codeXmlDom = Blockly.Xml.workspaceToDom(app.workspace);
                    var xmlText = Blockly.Xml.domToPrettyText(app.codeXmlDom);
                    app.code = _this.generateCSharpCode(); // C# code generation
                    var csFile = name.replace('xml', 'cs');
                    $.post("/designer/program/save", { "name": name, "value": xmlText }, function(data) {
                        console.log("Program save successful: " + name);
                        var pgmName = $("#program-name").empty();
                        pgmName.append(name);
                    });
                    $.post("/designer/program/savecs", { "name": csFile, "value": app.code }, function(data) {
                        console.log("CS Program save successful: " + name);
                    });
                });

                //app.skeleton.constants =
                //{
                //    circleRadius: 0.03,
                //    leafScale: 2.0
                //};

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

                // Robot Joint values
                app.jointVals = new jointVals();

                app.jointpoller = poller.get(app.jointVals, test_joint_options);
                app.jointpoller.on('error', function(model) {
                    globalCh.vent.trigger("serverCommunication", false);
                    console.error('Error retrieving Robot Status information from server!');
                });
                app.jointpoller.on('success', function(model) {
                    _this.setJointVals(model);
                });
                app.jointpoller.on('complete', function(model) {
                    console.log("Done !!!");
                });
                app.jointpoller.start();


                //initSkeletonPoller();

                // Human poller
                app.initHumanPoll = false;
                app.humanPollError = false;
            },

            initSkeletonPoller: function() {
                if (!app.initSkeletonPoller) {
                    var _this = this;
                    var globalCh = Backbone.Wreqr.radio.channel('global');
                    // Human Skeletons
                    var skeletonPollerOptions = {

                        // default delay is 1000ms
                        delay: 200,

                        // run after a delayed interval. defaults to false
                        // can be a boolean `true` to wait `delay` ms before starting or a number to override the wait period
                        delayed: 3000,

                        // do not stop the poller on error. defaults to false
                        // `error` event is always fired even with this option on.
                        continueOnError: false

                        // condition for keeping polling active (when this stops being true, polling will stop)
                        //condition: function(model) {
                        //    return model.id === -1;
                        //}
                    }

                    app.skeletons = new skeletons();

                    app.skeletonpoller = poller.get(app.skeletons, skeletonPollerOptions);
                    app.skeletonpoller.on('error', function(data) {
                        globalCh.vent.trigger("serverCommunication", false);
                        console.error('Error retrieving skeleton information from server!');
                    });
                    app.skeletonpoller.on('success', function(data) {
                        _this.updateSkeletons(data);
                    });
                    app.skeletonpoller.on('complete', function(data) {
                        console.log("Done !!!");
                    });
                    app.skeletonpoller.start();
                    app.initSkeletonPoller = true;
                }
            },

            setJointVals: function(jointModel) {
                if (jointModel != undefined && app.kinematics != undefined) {
                    for (var i = 0; i < 25; i++) {
                        app.kinematics.setJointValue(i, this.degrees(jointModel.get(i)), false);
                    }
                }
            },

            degrees: function(radians) {
                return radians * 180 / Math.PI;
            },

            getFileAjax: function(url) {
                return $.ajax({
                    type: "GET",
                    url: url,
                    cache: false,
                    async: false
                }).responseText;
            },

            replaceAllInstances: function(find, replace, str) {
                return str.replace(new RegExp(find, 'g'), replace);
            },

            generateCSharpCode: function() {
                var code = Blockly.CSharp.workspaceToCode(app.workspace);
                var template = this.getFileAjax('data/templates/NamespacesTemplate.cs');

                var newCode = this.replaceAllInstances('// MAIN_PROGRAM_HERE', code, template);
                return newCode;
            },

            index: function() {
                var _this = this;
                require(["jquery", "app", "views/designer", "views/monitor"],
                    function($, app, designer, monitor) {
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

                        _this.initSkeletons();

                        if (!app.initHumanPoll) {
                            app.initHumanPoll = true;
                            (function humansPoll() {
                                if (app.humanPollError) {
                                    return;
                                } else {
                                    setTimeout(function() {
                                        $.ajax({
                                            url: "/humans",
                                            success: function(data) {
                                                //sales.setValue(data.value);
                                                $('#humansTree').JSONView(data);
                                            },
                                            error: function() {
                                                console.log('Error receiving humans data from server');
                                                app.humanPollError = true;
                                            },
                                            dataType: "json",
                                            complete: humansPoll
                                        });
                                    }, 200);
                                }
                            })();
                        }
                    });
            },

            checkProgramEmpty: function() {
                app.codeXmlDom = Blockly.Xml.workspaceToDom(app.workspace);
                var hasChildren = $(app.codeXmlDom).children('block').length > 0;
                if (hasChildren === false) {
                    console.log("Empty program");
                    return true;
                }
                return false;
            },

            clearWorkspace:function() {
                //app.codeXmlDom = Blockly.Xml.textToDom('<xml></xml>');
                //Blockly.Xml.domToWorkspace(app.workspace, app.codeXmlDom);

                //TODO Add confirmation dialog
                //if (count < 2) {
                app.workspace.clear();
                app.codeXmlDom = Blockly.Xml.workspaceToDom(app.workspace);
                //}

                var name = $("#program-name").empty();
                name.append("None");
            },

            initCodeMenu: function () {
                var _this = this;
                $("#run").button({
                        text: true,
                        icons: {
                            primary: "ui-icon-play"
                        }
                    })
                    .click(function() {
                        var options;

                        if ($(this).text() === "RUN") {
                            var programEmpty = _this.checkProgramEmpty();
                            if (programEmpty === false) {
                                app.code = _this.generateCSharpCode(); // C# code generation
                                //$.post("/designer/program/start", app.code, function (data) {
                                //    console.log("Program Sent & Started: " + data);
                                //});
                                //console.log(app.code);

                                app.codeXmlDom = Blockly.Xml.workspaceToDom(app.workspace);
                                var xmlText = Blockly.Xml.domToPrettyText(app.codeXmlDom);
                                //$.post("/designer/program/startxml", xmlText, function(data) {
                                //    console.log("Program Sent & Started: " + data);
                                //});
                                $.post("/designer/program/startcs", app.code, function (data) {
                                    console.log("Program Sent & Started: " + data);
                                });

                                options = {
                                    label: "STOP",
                                    icons: {
                                        primary: "ui-icon-stop"
                                    }
                                };
                            }
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
                            var programEmpty = _this.checkProgramEmpty();
                            if (programEmpty === false) {
                                //app.code = Blockly.Python.workspaceToCode(app.workspace);
                                app.code = _this.generateCSharpCode(); // C# code generation
                                $.post("/designer/program/code", app.code, function(data) {
                                    console.log("Sent Program: " + data);
                                });
                                console.log(app.code);

                                //app.codeXmlDom = Blockly.Xml.workspaceToDom(app.workspace);
                                //var xmlText = Blockly.Xml.domToPrettyText(app.codeXmlDom);
                                //console.log(xmlText);
                                //console.log(app.code);
                            }
                        }
                    });
                $("#open").button({
                        text: true,
                        icons: {
                            primary: "ui-icon-document"
                        }
                    })
                    .click(function() {
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
                //ui - icon - trash

                $("#save").button({
                        text: true,
                        icons: {
                            primary: "ui-icon-disk"
                        }
                    })
                    .click(function () {
                        var programEmpty = _this.checkProgramEmpty();
                    if (programEmpty === false) {
                        var programName = $("#program-name").text();
                        var SaveModel = backbone.Model.extend({
                        });
                        var saveModel = new SaveModel();
                        saveModel.set({ name: programName });
                        //console.log(programName);
                        var dialog = new saveDialog({
                            model: saveModel
                        });
                        //console.log(dialog);
                        app.modals.show(dialog);
                    }
                    //app.codeXmlDom = Blockly.Xml.workspaceToDom(app.workspace);
                        //var hasChildren = $(app.codeXmlDom).children('block').length > 0;
                        //if (hasChildren === false) {
                        //    console.log("Empty program");
                        //} else {
                        //    console.log(app.codeXmlDom);
                        //    if (app.codeXmlDom != undefined) {
                        //        var xmlText = Blockly.Xml.domToPrettyText(app.codeXmlDom);
                        //        if (xmlText !== "") {
                        //            var dialog = new saveDialog({
                        //                programName: $("#program-name").text()
                        //            });
                        //            //console.log(dialog);
                        //            app.modals.show(dialog);
                        //        }
                        //    }
                        //}
                    });

                $("#clear").button({
                        text: true,
                        icons: {
                            primary: "ui-icon-trash"
                        }
                    })
                    .click(function () {
                        //app.code = _this.generateCSharpCode(); // C# code generation
                        //console.log(app.code);

                        //var blocks = app.workspace.getAllBlocks();
                        //// Iterate through every block and check the name.
                        //for (var x = 0; x < blocks.length; x++) {
                        //    console.log(blocks[x]);
                        //}

                        _this.clearWorkspace();
                });
            },

            initSkeletons: function () {
                var defaultBody = JSON.parse('{"TrackingId":0,"IsTracked":true,"JointCount":25,"Joints":[{"Type":0,"State":2,"Position":{"x":0.1249847337603569,"y":-0.11825757473707199,"z":2.0625252723693848},"Orientation":{"x":-0.0074656009674072266,"y":0.994424045085907,"z":-0.097892805933952332,"w":-0.038496285676956177},"Angle":-1000.0},{"Type":1,"State":2,"Position":{"x":0.11765184998512268,"y":0.203008234500885,"z":1.9989355802536011},"Orientation":{"x":-0.00657985545694828,"y":0.99403524398803711,"z":-0.0979563295841217,"w":-0.047489270567893982},"Angle":-1000.0},{"Type":2,"State":2,"Position":{"x":0.10996883362531662,"y":0.51213032007217407,"z":1.9208577871322632},"Orientation":{"x":-0.0050320285372436047,"y":0.988418698310852,"z":-0.14094266295433044,"w":-0.05602056160569191},"Angle":-1000.0},{"Type":3,"State":2,"Position":{"x":0.11100767552852631,"y":0.65268588066101074,"z":1.8685903549194336},"Orientation":{"x":0.0,"y":0.0,"z":0.0,"w":0.0},"Angle":-1000.0},{"Type":4,"State":2,"Position":{"x":-0.072081379592418671,"y":0.4020199179649353,"z":1.9540755748748779},"Orientation":{"x":0.7670518159866333,"y":-0.632301926612854,"z":0.061224404722452164,"w":0.089873649179935455},"Angle":-1000.0},{"Type":5,"State":2,"Position":{"x":-0.12330306321382523,"y":0.11945255100727081,"z":2.05051851272583},"Orientation":{"x":0.73542362451553345,"y":-0.17178833484649658,"z":-0.65233117341995239,"w":0.064069680869579315},"Angle":-1000.0},{"Type":6,"State":2,"Position":{"x":-0.15616711974143982,"y":-0.12857961654663086,"z":2.0507967472076416},"Orientation":{"x":0.92765551805496216,"y":-0.060984104871749878,"z":0.36759054660797119,"w":0.024764804169535637},"Angle":-1000.0},{"Type":7,"State":2,"Position":{"x":-0.1523086279630661,"y":-0.21819016337394714,"z":2.0551552772521973},"Orientation":{"x":0.92823714017868042,"y":0.028965773060917854,"z":0.37057283520698547,"w":0.014580557122826576},"Angle":-1000.0},{"Type":8,"State":2,"Position":{"x":0.27921488881111145,"y":0.37990257143974304,"z":1.9194412231445313},"Orientation":{"x":0.79949504137039185,"y":0.58344054222106934,"z":-0.14125023782253265,"w":0.021289864555001259},"Angle":-1000.0},{"Type":9,"State":2,"Position":{"x":0.3518061637878418,"y":0.11258499324321747,"z":1.994931697845459},"Orientation":{"x":0.90514588356018066,"y":0.17058581113815308,"z":0.38243570923805237,"w":0.073172867298126221},"Angle":-1000.0},{"Type":10,"State":2,"Position":{"x":0.38414722681045532,"y":-0.14147576689720154,"z":2.028949499130249},"Orientation":{"x":0.82764512300491333,"y":0.015472088009119034,"z":-0.55378943681716919,"w":0.089896410703659058},"Angle":-1000.0},{"Type":11,"State":2,"Position":{"x":0.39050894975662231,"y":-0.23987813293933868,"z":2.0402326583862305},"Orientation":{"x":0.82969772815704346,"y":-0.00494163203984499,"z":-0.55436939001083374,"w":0.06520678848028183},"Angle":-1000.0},{"Type":12,"State":2,"Position":{"x":0.042388316243886948,"y":-0.11569768190383911,"z":2.0310888290405273},"Orientation":{"x":-0.67155742645263672,"y":0.71412324905395508,"z":-0.18583275377750397,"w":0.0671171322464943},"Angle":-1000.0},{"Type":13,"State":2,"Position":{"x":0.016902543604373932,"y":-0.54638540744781494,"z":2.1400647163391113},"Orientation":{"x":-0.67750316858291626,"y":0.10988163203001022,"z":0.72451204061508179,"w":-0.063227236270904541},"Angle":-1000.0},{"Type":14,"State":2,"Position":{"x":0.019744889810681343,"y":-0.94153130054473877,"z":2.2733347415924072},"Orientation":{"x":-0.47902095317840576,"y":0.13989044725894928,"z":0.86273252964019775,"w":-0.081622451543807983},"Angle":-1000.0},{"Type":15,"State":2,"Position":{"x":-0.030965633690357208,"y":-1.002164363861084,"z":2.2072350978851318},"Orientation":{"x":0.0,"y":0.0,"z":0.0,"w":0.0},"Angle":-1000.0},{"Type":16,"State":2,"Position":{"x":0.20302265882492065,"y":-0.11659203469753265,"z":2.0189299583435059},"Orientation":{"x":0.65893334150314331,"y":0.704171359539032,"z":-0.23768116533756256,"w":-0.11600561439990997},"Angle":-1000.0},{"Type":17,"State":2,"Position":{"x":0.23478332161903381,"y":-0.54882222414016724,"z":2.1385741233825684},"Orientation":{"x":0.72868585586547852,"y":0.11722782999277115,"z":0.67059111595153809,"w":0.074712879955768585},"Angle":-1000.0},{"Type":18,"State":2,"Position":{"x":0.24888120591640472,"y":-0.9450414776802063,"z":2.2931602001190186},"Orientation":{"x":0.6585991382598877,"y":0.14848074316978455,"z":0.72924256324768066,"w":0.11138219386339188},"Angle":-1000.0},{"Type":19,"State":2,"Position":{"x":0.26045051217079163,"y":-1.0068831443786621,"z":2.2119810581207275},"Orientation":{"x":0.0,"y":0.0,"z":0.0,"w":0.0},"Angle":-1000.0},{"Type":20,"State":2,"Position":{"x":0.11199373751878738,"y":0.436588853597641,"z":1.9427328109741211},"Orientation":{"x":-0.0051533849909901619,"y":0.9913705587387085,"z":-0.11824706941843033,"w":-0.056351780891418457},"Angle":-1000.0},{"Type":21,"State":2,"Position":{"x":-0.15046697854995728,"y":-0.31152123212814331,"z":2.0728788375854492},"Orientation":{"x":0.0,"y":0.0,"z":0.0,"w":0.0},"Angle":-1000.0},{"Type":22,"State":2,"Position":{"x":-0.11904703080654144,"y":-0.25189891457557678,"z":2.0134797096252441},"Orientation":{"x":0.0,"y":0.0,"z":0.0,"w":0.0},"Angle":-1000.0},{"Type":23,"State":2,"Position":{"x":0.3890744149684906,"y":-0.32848110795021057,"z":2.0569159984588623},"Orientation":{"x":0.0,"y":0.0,"z":0.0,"w":0.0},"Angle":-1000.0},{"Type":24,"State":2,"Position":{"x":0.35649600625038147,"y":-0.27371099591255188,"z":2.019277811050415},"Orientation":{"x":0.0,"y":0.0,"z":0.0,"w":0.0},"Angle":-1000.0}],"ClippedEdges":0,"HandLeftConfidence":0,"HandLeftState":0,"HandRightConfidence":0,"HandRightState":0,"IsRestricted":false,"Lean":null,"LeanTrackingState":0}');
                for (var i = 0; i < 6; i++) {
                    defaultBody.TrackingId = i;
                    var body1 = this.createNewDrawable({
                        hasSkeleton: true,
                        skeleton: defaultBody
                    });
                    body1._mesh.position.x = -0.8;
                    app.Drawables.trigger('drawable:loaded', body1);
                    break;//Test
                }
            },

            createNewDrawable: function(options) {
                var newDrawable = new m3Js.Drawable(options);
                app.Drawables.add(newDrawable);
                return newDrawable;
                //console.log(app.renderer.scene);
                //console.log(app.Drawables);
            },

            updateSkeletons: function(skeletonsJsonObject) {
                if (skeletonsJsonObject != undefined && skeletonsJsonObject.length > 0) {
                    console.log(skeletonsJsonObject);
                } else {
                    var existingSkeletons = app.Drawables.where({ skeleton: true });
                    if (existingSkeletons.length > 0) {
                        app.Drawables.remove(existingSkeletons);
                    }
                }
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