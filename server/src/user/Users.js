/**
 * user controller for create、update、delete、etc...
 */

require("../system/DBAgent");
require("../system/Log");

// user database connection
var db                              // must be initialized at first time
    , log = new Log("Users")
    , util = require("util");

module.exports = {
    initInstance: function(dbConfig) {
        db = new DBAgent(dbConfig);
        db.connect(true);
    },

    createUser: function(info, cb) {
        var udid = info["udid"];
        if ((typeof udid == "string") && udid.length > 0) {
            db.query(util.format("INSERT INTO `users` (udid) VALUES ('%s')", udid), function(err, ret) {
                if (err) {
                    cb(err);
                } else {
                    db.query("SELECT LAST_INSERT_ID()", function(err, ret) {
                        console.log(arguments);
                    });
                }
            });
        } else {
            throw new Error("Invalid arguments");
        }
    }
}