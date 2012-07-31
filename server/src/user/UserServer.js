/**
 * Account Authentication Server.
 * Responsibility:
 *  -   login:  authorize valid user, create new account for new user
 */
require("../system/Log");

var express = require("express")
    ,app = express.createServer()
    ,log = new Log("UserServer");

app.configure(function() {
    app.use(express.bodyParser());
    app.use(express.methodOverride());
    app.use(app.router);

    app.set("views", __dirname + "/");
    app.set("view engine", "jade");
});

app.configure('development', function(){
    app.use(express.errorHandler({ dumpExceptions: true, showStack: true }));
});

app.configure("production", function() {
    app.use(express.errorHandler());
});

require("../system/DBAgent");

// init server, connect database here
app.initInstance = function (srvConfig, callback) {
    var cfg = require("../config/user.UserServer");
    var cb = function() {log.d(arguments);};
    for (var i = 0; i < arguments.length; ++i) {
        var arg = arguments[i];
        switch (typeof arg) {
            case "function":    cb = arg; break;
            case "object":      cfg = arg; break;
            default: throw new Error("Invalid argument");
        }
    }

    var db = new DBAgent(cfg.dbConfig);
    db.connect().createDatabase(cfg["reCreateDB"] || false, function(err) {
        if (err) {
            cb(err);
            return;
        }
        db.query(
            "CREATE TABLE IF NOT EXISTS users (" +
                "uuid       bigint(8)       PRIMARY KEY AUTO_INCREMENT COMMENT '自增长ID'," +
                "udid       varchar(127)," +
                "91id       varchar(127)" +
                ") DEFAULT CHARSET=utf8 COMMENT='用户表' AUTO_INCREMENT=10000",
            function(err) {
                if (err) {
                    cb(err);
                    return;
                } else {
                    app.initHandlers(app);
                    var users = require("./Users");
                    users.initInstance(cfg.dbConfig);
                    cb(err);
                    db.close();
                    db = undefined;
                }
            }
        );
    });
    return this;
};

app.initHandlers = function (aExpress) {
    aExpress.post("/user/login", require("./handler/login"));
};

module.exports = app;