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
        Actors._dbAgent.connect();

        Actors._dbAgent.createDatabase(dbConfig.recreate || false, function(err) {
            if (err) {
                throw err;
                return;
            }
            Actors._dbAgent.query("CREATE TABLE IF NOT EXISTS `actors`(" +
                "uuid       bigint(8)       PRIMARY KEY COMMENT 'user id'," +
                "data       blob" +
                ") DEFAULT CHARSET=utf8 COMMENT='角色表'",
                function (err) {
                    callback(err);
                });
        });
    },

    getActor: function(uuid, callback) {
        Actors._dbAgent.query("SELECT `data` FROM `actors` WHERE `uuid` = ?", [uuid], function (err, rows) {
            if (err) {
                throw err;
                return;
            }
            var data = (rows.length) ? JSON.parse(rows[0].data) : null;
            callback(new Actor(data));
        });
    }
};

module.exports = Actors;