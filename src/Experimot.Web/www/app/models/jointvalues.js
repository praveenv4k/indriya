define(['jquery', 'underscore', 'backbone'],
    function($, _, backbone) {
        //ItemView provides some default rendering logic
        var jointvals = backbone.Model.extend({
            urlRoot: '/testjointvals/',
            id: 0,
            url: function() {
                return this.urlRoot + this.id;
            }
        });
        return jointvals;
    });