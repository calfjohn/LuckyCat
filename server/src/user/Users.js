/**
 * user controller for create、update、delete、etc...
 *
 * sample code:
     var users = require("./user/Users");
     var info = {};
     var uuid;
     info.udid = "1234567890";
     users.createUser(info, function(uuid1) {
         console.log("createUser:"+uuid1);
         uuid = uuid1;
         users.findUser(info, function(uuid2) {
            console.log("findUser:"+uuid2);
         })
     });
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

    // uuid returned by cb
    createUser: function(info, cb) {
        var udid = info["udid"];
        if ((typeof udid == "string") && udid.length > 0) {
            db.query(util.format("INSERT INTO `users` (udid) VALUES ('%s')", udid), function(err, ret) {
                if (err) {
                    throw (err);
                } else {
                    db.query("SELECT LAST_INSERT_ID()", function(err, ret) {
                        if (err) {
                            throw err;
                        } else {
                            cb(ret[0]["LAST_INSERT_ID()"]);
                        }
                    });
                }
            });
        } else {
            throw new Error("Invalid arguments");
        }
    },

    // belong to uuid map to other id designed as 1 to 1
    // uuid returned by callback
    findUser: function(info, cb) {
        var sqlCmd = "SELECT `uuid` FROM `users` WHERE `%s`='%s'";
        var colKey, colVal;
        if ((typeof info["udid"] == "string") && info["udid"].length > 0) {
            // find user by udid
            colKey = "udid";
            colVal = info["udid"];
        }
        db.query(util.format(sqlCmd, colKey, colVal), function(err, rows) {
            if (err) {
                throw err;
            } else {
                log.d(arguments);
                switch (rows.length) {
                    case 0: cb(null); break;
                    case 1: cb(rows[0]["uuid"]); break;
                    default: throw new Error(util.format("find user by(%s=%s) in database more than one!", colKey, colVal)); break;
                }
            }
        });
    }
}