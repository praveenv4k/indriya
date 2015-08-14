// robot.js
// Praveenkumar VASUDEVAN
define(['jquery', 'underscore', 'backbone'],
    function($, _, backbone) {
        var robot = backbone.Model.extend({
            url: '/robot'
        });
        return robot;
    });