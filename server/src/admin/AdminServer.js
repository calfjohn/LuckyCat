/**
 * Admin server.
 * Responsibility:
 *  -   gm:  game master
 */

require("../system/Log");

var http = require("http")
    ,express = require("express")
    ,app = express()
    ,server = http.createServer(app)
    ,io = require("socket.io")
    ,log = new Log("AdminServer");

app.configure(function() {
    app.use(express.bodyParser());    // This cause handler' on data function doesn't be called.
    app.use(express.cookieParser());
    app.use(express.session({secret:"anything", key:"express.sid"}));
    app.use(express.methodOverride());
    app.use(app.router);
    app.use(express.static(__dirname + "/www"));  //设定静态网页服务目录
    app.set("views", __dirname + "/views");
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
    var cfg = require("../config/admin.AdminServer");
    var cb = function() {log.d(arguments);};
    for (var i = 0; i < arguments.length; ++i) {
        var arg = arguments[i];
        switch (typeof arg) {
            case "function":    cb = arg; break;
            case "object":      cfg = arg; break;
            default: throw new Error("Invalid argument");
        }
    }
    process.nextTick(function() {
        app.initHandlers(app);
        cb(null);
    });
    /*/ init modules
    require("./Roles").initInstance(cfg.db_roles, function(err) {
        if (! err) app.initHandlers(app);
        cb(err);
    });*/
    return this;
};

// start server, begin listening
app.start = function() {
    server.listen(80);
};

app.initHandlers = function (aExpress) {
    aExpress.get("/",require("./handler/page/Main"));
    aExpress.get("/login", require("./handler/page/Login"));
    aExpress.post("/login", require("./handler/login"));
    //aExpress.all("/*", require("./handler/page/Main"));

    // init socket handlers
    var socket = io.listen(server, {log:false});
    socket.sockets.on("connection", require("./socket/getData"));

    aExpress.adminSocket = socket;
};

module.exports = app;