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

            index: function() {
                require(["jquery", "app", "views/designer", "views/monitor"],
                    function($, app, designer, monitor) {
                        //app.designer.show(new designer());
                        app.monitor.show(new monitor());
                        //app.viewport.show(app.renderer);
                        app.viewport.show(app.renderer);
                        app.workspace = Blockly.inject('blocklyDiv',
                        { toolbox: document.getElementById('toolbox') });

                        var newDrawable = new m3Js.Drawable({
                            texture: 'app/crate.gif',
                            geometryType: 'TorusGeometry',
                            geometryParams: [50, 20, 20, 20]
                        });
                        app.Drawables.add(newDrawable);
                        //this.createNewDrawable({
                        //    //texture: 'crate.gif',
                        //    geometryType: 'TorusGeometry',
                        //    geometryParams: [50, 20, 20, 20]
                        //});

                        $("#tabs").tabs();


                        app.loader.load("models/collada/nao.dae", function(collada) {

                            app.dae = collada.scene;

                            app.dae.traverse(function(child) {

                                if (child instanceof THREE.Mesh) {

                                    child.geometry.computeFaceNormals();
                                    child.material.shading = THREE.FlatShading;

                                }

                            });

                            app.dae.scale.x = app.dae.scale.y = app.dae.scale.z = 10.0;
                            app.dae.updateMatrix();

                            app.kinematics = collada.kinematics;

                            var globalCh = Backbone.Wreqr.radio.channel('global');
                            console.log("Triggering request");
                            globalCh.vent.trigger("addMeshRequest", app.dae);
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