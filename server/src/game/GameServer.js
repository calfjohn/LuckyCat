/**
 * Game logic server.
 * Responsibility:
 *  -   combat:  actor combat with
 */

require("../system/Log");

var express = require("express")
    ,app = express.createServer()
    ,log = new Log("GameServer");

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

// init server, init modules here
app.initInstance = function (srvConfig, callback) {
    var cfg = require("../config/game.GameServer");
    var cb = function() {log.d(arguments);};
    for (var i = 0; i < arguments.length; ++i) {
        var arg = arguments[i];
        switch (typeof arg) {
            case "function":    cb = arg; break;
            case "object":      cfg = arg; break;
            default: throw new Error("Invalid argument");
        }
    }

    // init modules
    require("./Actors").initInstance(cfg.db_actors, function(err) {
        if (! err) app.initHandlers(app);
        cb(err);
    });
    return this;
};

app.initHandlers = function (aExpress) {
    aExpress.post("/game/combat", require("./handler/combat"));
    aExpress.post("/game/actor/getActorInfo", require("./handler/actor.getActorInfo"));
    aExpress.post("/game/task/openBox", require("./handler/task.openBox"));
};

module.exports = app;