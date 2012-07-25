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

app.get("/user/login", require("./handler/login"));
app.get("/user/login", require("./handler/createUser"));

require("../system/DBAgent");
var dbCfg = require("../config/user.UserServer");
var db = new DBAgent(dbCfg.dbConfig);

// init server, connect database here
app.initServer = function (cb) {
    db.connect();
    process.nextTick(function() {
        // emulate the async initialize operation
        cb(null);
    });
/*
    var doCreateTable = function() {
        log.d("doCreateTable");
        db.query(
            "CREATE TABLE IF NOT EXISTS users (" +
                "uuid       bigint(8)       PRIMARY KEY AUTO_INCREMENT COMMENT '自增长ID'," +
                "udid       varchar(127)," +
                "91id       varchar(127)," +
                ") DEFAULT CHARSET=utf8 COMMENT='用户表' AUTO_INCREMENT=10000",
            function(err) {
                cb (err);
            }
        )
    }
    if (null == dbCfg.dbConfig["database"]) {
        // config havn't set database, use code to create it.
        log.d("doCreateDatabase");
        db.createDatabase("db_luckycat", dbCfg.dbReCreate || false, function(err) {
            if (err) {
                cb (err);
                return;
            }
            doCreateTable();
        }).on("connect", function() { client.query("use db_luckycat")});
    }*/
    return this;
}
module.exports = app;