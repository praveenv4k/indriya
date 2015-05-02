define(['app', 'backbone', 'marionette', 'collections/drawables', 'marionette_threejs'],
    function (app, backbone, marionette, drawables, m3Js) {
        return backbone.Marionette.Controller.extend({
            initialize: function (options) {
                app.Drawables = new drawables();
                app.renderer = new m3Js.ThreeJSRenderer({
                    collection: app.Drawables
                });

                
                app.loader = new THREE.ColladaLoader();
                app.loader.options.convertUpAxis = true;
                //var globalCh = Backbone.Wreqr.radio.channel('global');
                //App.StatusPoller = Poller.get(App.MachineStatus, this.pollerOptions());
                //App.StatusPoller.on('error', function (model) {
                //    globalCh.vent.trigger("serverCommunication", false);
                //    console.error('Error retrieving machine Status information from server!');
                //});
                //App.StatusPoller.start();
            },
            index: function () {
                require(["jquery", "app", "views/designer", "views/monitor"],
                    function ($, app, designer, monitor) {
                        $("#tabs").tabs();
                        //app.designer.show(new designer());
                        app.monitor.show(new monitor());
                        //app.viewport.show(app.renderer);
                        app.viewport.show(app.renderer);
                        app.workspace = Blockly.inject('blocklyDiv',
                        { toolbox: document.getElementById('toolbox') });
                        app.loader.load("models/collada/nao.dae", function (collada) {

                            app.dae = collada.scene;

                            app.dae.traverse(function (child) {

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
            }
        });
    });