/**
 * Admin server.
 * Responsibility:
 *  -   gm:  game master
 */

var wsBrowserHandlers = [
    "./socket/RoleAgent"
];

var wsUserServerHandlers = [
    "./socket/AdminServerAgent"
];

var wsGameServerHandlers = [
    "./socket/AdminServerAgent"
];

require("../system/Log");

var express = require("express")
    ,adminServerCfg = require("../config/admin.AdminServer")
    ,sessionStore = new express.session.MemoryStore
    ,sessionSecret = "LuckyCatAdmin"
    ,parseCookie = express.cookieParser(sessionSecret)
    ,app = express()
    ,server = require("http").createServer(app)
    ,utils = require("util")
    ,log = new Log("AdminServer");

app.configure(function() {
    app.use(express.bodyParser());    // This cause handler' on data function doesn't be called.
    app.use(parseCookie);
    app.use(express.session({store: sessionStore, secret:sessionSecret, key:"express.sid"}));
    app.use(express.methodOverride());
    app.use(app.router);
    app.use(express.static(__dirname + "/www"));  //设定静态网页服务目录
    // app.set("views", __dirname + "/views");    // 决定不使用动态模板生成页面，使用www下的静态页面+websocket的服务模式
    // app.set("view engine", "jade");

    app.use(function(err, req, res, next) {
        // if an error occurs Connect will pass it down
        // through these "error-handling" middleware
        // allowing you to respond however you like
        log.e(err);
        res.send(500, { error: 'Sorry something bad happened!' });
    });
});

// init server, init modules here
app.initInstance = function (srvConfig, done) {
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
        app.initSockets();
        app.initHandlers();
        cb(null);
    });
    /*/ init modules
    require("./Roles").initInstance(cfg.db_roles, function(err) {
        if (! err) app.initHandlers(app);
        cb(err);
    });*/
    return this;
};

app.initSockets = function() {
    // init socket handlers
    var socket = require("socket.io").listen(server, {log:false});
    socket.set("authorization", app.checkSocketAuthorization);

    // for browser
    var browserSocket = socket.of("/browsers");
    for (var i = 0; i < wsBrowserHandlers.length; ++i) {
        browserSocket.on("connection", require(wsBrowserHandlers[i]).handler);
    }

    // for user server
    var userServerSocket = socket.of("/user_servers");
    for (var i = 0; i < wsUserServerHandlers.length; ++i) {
        userServerSocket.on("connection", require(wsUserServerHandlers[i]).handler);
    }

    // for game server
    var gameServerSocket = socket.of("/game_servers");
    for (var i = 0; i < wsGameServerHandlers.length; ++i) {
        gameServerSocket.on("connection", require(wsGameServerHandlers[i]).handler);
    }
};

app.initHandlers = function () {
    app.post("/login", require("./handler/login").handler);
    app.get("/js/adminServer", function(req, res, next) {
        res.setHeader("Content-Type", "text/javascript");
        res.end(utils.format("var adminServer='%s/browsers';", req.headers.host));
    });
    app.get("/*", app.checkHttpAuthorization);
};

// 检查网页连接的授权，否则转到login.html页面
app.checkHttpAuthorization = function (req, res, next) {
    if (req.path == "/login.html") {
        next();
        return;
    }
    //log.d("checkHttpAuthorization(path=", req._parsedUrl.pathname, ",sessionID=", req.session.id, "):", req.session.token);
    //使用request.session来判断是否登录
    if( req.session.token && req.session.token!==''){
        //需要判断token是否合法，合法证明已登录

        next();
    }else{
        //读取登录页面，要求登录
        //var realpath = __dirname + '/views/' + url.parse('login.html').pathname;
        //var txt = fs.readFileSync(realpath);
        //res.end(txt);
        res.redirect("/login.html");
    }
};

// 检查socket连接是否有授权，授权数据保存在cookie中
app.checkSocketAuthorization = function (req, accept) {
    var cookies = null;
    parseCookie(req, null, function(err) {
        if (! err) {
            cookies = req.signedCookies;
        }
    });
    log.d("checkSocketAuthorization(referer=", req.headers.referer, ",cookies=", cookies, ")");

    // check if there's a cookie header
    if (cookies && cookies['express.sid']) {
        // 使用sid从sessionStore中获取session
        sessionStore.load(cookies['express.sid'], function (err, session) {
            // 如果获取失败，取消连接
            if (err) {
                accept(err.message, false);
            } else {
                // 把session挂到req上，以便在下面的事件中访问
                req.session = session;
                accept(null, true);
            }
        });
    } else if (req.query.server_secret && (req.query.server_secret == adminServerCfg.server_secret)) {
        // 从别的服务器连接过来的
        accept(null, true);
    } else {
        // 连接失败
        accept(null, false);
    }
};

// start server, begin listening
app.start = function() {
    server.listen(require("../config/admin.AdminServer").service.port);
};

module.exports = app;