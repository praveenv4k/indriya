// testjointvalues.js
// Praveenkumar VASUDEVAN
define(['jquery', 'underscore', 'backbone'],
    function($, _, backbone) {
        var testJointVals = backbone.Model.extend({
            urlRoot: '/testjointvals/',
            id: 0,
            url: function() {
                return this.urlRoot + this.id;
            }
        });
        return testJointVals;
    });