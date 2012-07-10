/*  Base class for service handling.
    A URL is a service. (http://host:port/servicepath)
 */

require("./Class");
require("./Log");

var util = require("util");
var log = new Log("HttpServer");

HttpServer = Class.extend({
    _service : null,                    getService: function() { return _service; },
    _handle: {},
    _port: 0,                           getPort: function() { return _port; },

    // Register handler for appointed url path.
    register: function(method, pathname, callback) {
        var methodHandle = this._handle[method];
        if (undefined == methodHandle) {
            methodHandle = {};
            this._handle[method] = methodHandle;
        }
        if (typeof methodHandle[pathname] === "function") {
            if (methodHandle[pathname] == callback) {
                log.w("Handler has registered yet.");
            } else {
                log.w("Handler conflict with another which registered before.");
            }
        } else {
            methodHandle[pathname] = callback;
        }
    },

    // Server start to listen special port.
    start: function() {
        if (arguments.length <= 0) throw new("function HttpServer.start() mast has arguments.");
        var that = this;
        this._service = require("http").createServer(function (request, response) {
                that.onRequest(request, response);
        });

        if (typeof this.onConnection == "function") {
            this._service.on("connection", this.onConnection);
        }
        if (typeof this.onClose == "function") {
            this._service.on("close", this.onClose);
        }
        if (typeof this.onCheckContinue == "function") {
            this._service.on("checkContinue", this.onCheckContinue);
        }
        if (typeof this.onConnect == "function") {
            this._service.on("connect", this.onConnect);
        }
        if (typeof this.onUpgrade == "function") {
            this._service.on("upgrade", this.onUpgrade);
        }
        if (typeof this.onClientError == "function") {
            this._service.on("clientError", this.onClientError);
        }
        this._port = arguments[0];
        this._service.listen.apply(this._service, arguments);
        return this;
    },

    // Route request by _handle.
    route: function(request, response) {
        var parsedUrl = require("url").parse(request.url, true);
        var methodHandle = this._handle[request.method];
        if (methodHandle && typeof methodHandle[parsedUrl.pathname] === "function") {
            methodHandle[parsedUrl.pathname](request, response);
        } else {
            log.d("No request handler found for " + request.url);
        }
    },

    // Close all connections.
    close: function(callback) {
        if (this._service != null) {
            this._service.close.apply(callback);
        }
    },

    onRequest: function(request, response) {
        this.route(request, response);
    },
    onConnection: null,                 // function (socket) { }
    onClose: null,                      // function () { }
    onCheckContinue : null,             // function (request, response) { }
    onConnect: null,                    // function (request, socket, head) { }
    onUpgrade: null,                    // function (request, socket, head) { }
    onClientError: null                 // function (exception) { }

});