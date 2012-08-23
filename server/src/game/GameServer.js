/**
 * Game logic server.
 * Responsibility:
 *  -   combat:  actor combat with
 */

var httpHandlers = { "/game/combat":      "./handler/combat"
    , "/game/box/openBox":                "./handler/box.openBox"
    , "/game/actor/getBasicInfo":         "./handler/actor.getBasicInfo"
    , "/game/actor/getAllEquipment":      "./handler/actor.getAllEquipment"
    , "/game/actor/getEquippedEquipment": "./handler/actor.getEquippedEquipment"
    , "/game/actor/changeEquipmentInfo":  "./handler/actor.changeEquipmentInfo"
    , "/game/actor/getSkillInfo":         "./handler/actor.getSkillInfo"
    , "/game/battle/fight1":              "./handler/battle.fight1"
    , "/game/battle/fight2":              "./handler/battle.fight2"
    , "/game/event/getEventList":         "./handler/event.getEventList"
};

var wsHandlers = [
    "./socket/GameServerAgent"
];

require("../system/Log");

var express = require("express")
    ,app = express()
    ,server = require("http").createServer(app)
    ,reference = require("../system/ApiReference")
    ,log = new Log("GameServer");

app.configure(function() {
    //app.use(express.bodyParser());    // This cause handler' on data function doesn't be called.
    app.use(express.methodOverride());
    app.use(app.router);
    app.use(express.static(__dirname + "/www"));  //设定静态网页服务目录
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
    var done = function() {log.d(arguments);};
    for (var i = 0; i < arguments.length; ++i) {
        var arg = arguments[i];
        switch (typeof arg) {
            case "function":    done = arg; break;
            case "object":      cfg = arg; break;
            default: throw new Error("Invalid argument");
        }
    }

    var afterInitModules = function() {
        // init sync part here
        app.initSockets(cfg.ws_admin_server);
        app.initHandlers();
        done();
    };

    // init modules
    // init async part here
    require("./Actors").initInstance(cfg.db_actors, function(err) {
        if (err) throw err;
        require("./Box").initInstance(cfg.db_actors, function(err) {
            if (err) throw err;
            require("./Events").initInstance(cfg.db_actors, function(err) {
                if (err) throw err;
                require("./Level").initInstance(cfg.db_actors, function(err) {
                    if (err) throw err;
                    require("./Monster").initInstance(cfg.db_actors, function(err) {
                        if (err) throw err;
                        require("./DictManager").initInstance(cfg.db_actors, function(err) {
                            if (err) throw err;
                        afterInitModules();
                        });
                    });
                });
            });
        });
    });

    return this;
};

app.initSockets = function (ws_admin_server) {
    var wsToAS = require("socket.io-client").connect(ws_admin_server.host, ws_admin_server.options);
    for(var i = 0; i < wsHandlers.length; ++i) {
        var handler = require(wsHandlers[i]);
        handler.socket = wsToAS;
        wsToAS.on("connect", handler.handler);
    }
    wsToAS.on("error", function(err) {
        throw err;
    });
};

app.initHandlers = function () {
    var handler = require("./handler/game.ApiReference")
    handler.initReference(reference.getReference("/game/api_demo/doAction"));
    app.get("/game/*", handler.handler);
    app.get("/favicon.ico", function(req, res, next) {
        next();
    });
    app.get("/", function(req, res, next) {
        res.redirect("/game/api_demo");
    })

    for (var key in httpHandlers) {
        handler = require(httpHandlers[key]);
        if (handler.initReference) {
            handler.initReference(reference.getReference(key));
        }
        app.post(key, handler.handler);
    }
};

// start server, begin listening
app.start = function() {
    server.listen(require("../config/game.GameServer").service.port);
};

module.exports = app;