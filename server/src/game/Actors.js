/**
 * Actors controller for cache、 sync with database.
 */

if (global.Actors) {
    module.exports = Actors;
    return;
}

require("../system/DBAgent");
require("../system/Log");
require("./Actor");

var log = new Log("Actors")
    , util = require("util");

Actors = {
    _dbAgent : null,
    initInstance : function(dbConfig, callback) {
        Actors._dbAgent = new DBAgent(dbConfig);
        Actors._dbAgent.connect(true);
        process.nextTick(function() {
           callback(null);
        });
    },

    getActor: function(uuid, callback) {
        Actors._dbAgent.query("SELECT * FROM `actor` WHERE `id` = ?", [uuid], function (err, rows) {
            if (err) {
                throw err;
                return;
            }
            var len = rows.length;
            var data = (rows.length) ? rows[0]: null;
            callback(new Actor(data));
        });
    }
};


module.exports = Actors;