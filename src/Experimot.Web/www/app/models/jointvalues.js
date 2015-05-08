define(['jquery', 'underscore', 'backbone'],
    function($, _, backbone) {
        //ItemView provides some default rendering logic
        var JointValues = backbone.Model.extend({
            url: '/jointvals',
        });
        return JointValues;
    });