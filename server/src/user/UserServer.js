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
    //app.use(express.bodyParser());    // This cause handler' on data function doesn't be called.
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

    require("./Users").initInstance(cfg.db_users, function(err) {
        if (! err) {
            app.initHandlers(app);
        }
        cb(err);
    });
    return this;
};

app.initHandlers = function (aExpress) {
    aExpress.post("/user/login", require("./handler/login"));
};

module.exports = app;