define(['app', 'jquery', 'underscore', 'backbone', 'marionette', 'marionette_threejs', 'text!templates/viewport.html'],
    function (app, $, _, Backbone, Marionette, m3Js, template) {


        var renderer = new m3Js.ThreeJSRenderer({
            collection: app.Drawables
        });

        return renderer;


        ////ItemView provides some default rendering logic
        //return backbone.Marionette.ItemView.extend({
        //    template: _.template(template),
        //    // View Event Handlers
        //    events: {

        //    },
        //    //tagName: "li",
        //    render: function () {
        //        console.log("Rendering viewport");
        //        // サムネイルのサイズを指定。
        //        // Three.jsのcanvasサイズになります。
        //        width = 400;
        //        height = 200;
        //        // ここからは普通のThree.jsの処理を書いただけですね。
        //        // もっとうまくBackbone.jsでラップしたいです。
        //        var scene = new THREE.Scene();
        //        var camera = new THREE.PerspectiveCamera(45, width / height, 0.1, 100000);
        //        camera.position.set(10, 8, -10);

        //        controls = new THREE.OrbitControls(camera);

        //        // Grid

        //        var size = 14, step = 1;

        //        var geometry = new THREE.Geometry();
        //        var material = new THREE.LineBasicMaterial({ color: 0x303030 });

        //        for (var i = -size; i <= size; i += step) {

        //            geometry.vertices.push(new THREE.Vector3(-size, -0.04, i));
        //            geometry.vertices.push(new THREE.Vector3(size, -0.04, i));

        //            geometry.vertices.push(new THREE.Vector3(i, -0.04, -size));
        //            geometry.vertices.push(new THREE.Vector3(i, -0.04, size));

        //        }

        //        var line = new THREE.Line(geometry, material, THREE.LinePieces);
        //        scene.add(line);

        //        var renderer = new THREE.WebGLRenderer();
        //        renderer.setClearColor(0xEEEEEE);
        //        renderer.setSize(width, height);

        //        //var container = document.getElementById('viewport');
        //        this.$el.append(renderer.domElement);
        //        //scene.add(this.model.mesh());
        //        camera.position.x = -15;
        //        camera.position.y = 20;
        //        camera.position.z = 20;
        //        camera.lookAt(scene.position);
        //        renderer.render(scene, camera);
        //        return this;
        //    }
        //});
    });