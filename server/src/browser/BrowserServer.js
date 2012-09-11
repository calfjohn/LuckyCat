/**
 * Game logic server.
 * Responsibility:
 *  -   combat:  actor combat with
 */


require("../system/Log");

var express = require("express")
    ,app = express()
    ,server = require("http").createServer(app)
    ,reference = require("../system/ApiReference")
    ,log = new Log("BrowserServer");

app.configure(function() {
    //app.use(express.bodyParser());    // This cause handler' on data function doesn't be called.
    app.use(express.methodOverride());
    app.use(app.router);
    app.use(express.static(__dirname + "/client"));  //设定静态网页服务目录
});

// init server, init modules here
app.initInstance = function (srvConfig, callback) {
    var cfg = require("../config/browser.BrowserServer");
    var done = function() {log.d(arguments);};
    for (var i = 0; i < arguments.length; ++i) {
        var arg = arguments[i];
        switch (typeof arg) {
            case "function":    done = arg; break;
            case "object":      cfg = arg; break;
            default: throw new Error("Invalid argument");
        }
    }

    process.nextTick(done);

    return this;
};

// start server, begin listening
app.start = function() {
    server.listen(require("../config/browser.BrowserServer").service.port);
};

module.exports = app;
