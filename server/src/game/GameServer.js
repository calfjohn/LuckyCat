/**
 * Game logic server.
 * Responsibility:
 *  -   combat:  actor combat with
 */

require("../system/Log");

var http = require("http")
    ,express = require("express")
    ,app = express()
    ,server = http.createServer(app)
    ,log = new Log("GameServer");

app.configure(function() {
    //app.use(express.bodyParser());    // This cause handler' on data function doesn't be called.
    app.use(express.methodOverride());
    app.use(app.router);


    app.set("views", __dirname + "/");
    app.set("view engine", "jade");

    app.use(function(err, req, res, next) {
        // if an error occurs Connect will pass it down
        // through these "error-handling" middleware
        // allowing you to respond however you like
        log.e(err);
        res.send(500, { error: 'Sorry something bad happened!' });
    });
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

    require("./Level").initInstance(cfg.db_actors, function(err) {
        cb(err);
    });
    // init modules
    require("./Actors").initInstance(cfg.db_actors, function(err) {
        if (! err) app.initHandlers(app);
        cb(err);
    });

    require("./ActorEquipments").initInstance(cfg.db_actors, function(err) {
        if (! err) app.initHandlers(app);
        cb(err);
    });
    return this;
};

// start server, begin listening
app.start = function() {
    server.listen(require("../config/game.GameServer").service.port);
};

app.initHandlers = function (aExpress) {
    aExpress.post("/game/combat", require("./handler/combat"));
    aExpress.post("/game/actor/getBasicInfo", require("./handler/actor.getBasicInfo.js"));
    aExpress.post("/game/actor/getEquipmentInfo", require("./handler/actor.getEquipmentInfo.js"));
    aExpress.post("/game/task/openBox", require("./handler/task.openBox"));
    aExpress.post("/game/battle/fight1", require("./handler/battle.fight1"));
    aExpress.post("/game/battle/fight2", require("./handler/battle.fight2"));
};
module.exports = app;