define(['jquery', 'underscore', 'backbone'],
    function ($, _, backbone) {
        //ItemView provides some default rendering logic
        var robot = backbone.Collection.extend({
            url: '/robot'
        });
        return robot;
    });