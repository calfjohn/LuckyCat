/**
 * Account Authentication Server.
 * Responsibility:
 *  -   login:  authorize valid user, create new account for new user
 */

var httpHandlers = {
    "/user/login": "./handler/login"
};

var wsHandlers = [
    "./socket/UserServerAgent"
];

require("../system/Log");

var http = require("http")
    ,express = require("express")
    ,app = express()
    ,server = http.createServer(app)
    ,io = require("socket.io-client")
    ,log = new Log("UserServer");

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

// init server, connect database here
app.initInstance = function (srvConfig, callback) {
    var cfg = require("../config/user.UserServer");
    var done = function() {log.d(arguments);};
    for (var i = 0; i < arguments.length; ++i) {
        var arg = arguments[i];
        switch (typeof arg) {
            case "function":    done = arg; break;
            case "object":      cfg = arg; break;
            default: throw new Error("Invalid argument");
        }
    }

    app.initUsers(cfg.db_users, function() {
        app.initSockets(cfg.ws_admin_server);
        app.initHandlers();
        done();
    });
    return this;
};

app.initUsers = function (db_users, done) {
    require("./Users").initInstance(db_users, function(err) {
        if (err) throw err;
        done();
    });
};

app.initSockets = function (ws_admin_server) {
    var wsToAS = io.connect(ws_admin_server.host, ws_admin_server.options);
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
    for (var key in httpHandlers) {
        var value = httpHandlers[key];
        var handler = require(value);

        app.post(key, handler.handler);
    }
};

// start server, begin listening
app.start = function() {
    server.listen(require("../config/user.UserServer").service.port);
};

module.exports = app;