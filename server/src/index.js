require("./system/HttpServer");
require("./system/Log");

var util = require("util");

var log = new Log("HttpServer.test");

var testServerPort = 5127;

HttpTestServer = HttpServer.extend({
    init: function() {
        this.register("GET", "/", this.onGetRequest);
        this.register("POST", "/", this.onPostRequest);
    },

    onGetRequest: function(request, response) {
        response.writeHead(200, {'Content-Type': "text/plain"});
        response.end(util.format("onGetRequest(%s) at %s\n", request.url, new Date().toUTCString()));
    },

    onPostRequest: function(request, response) {
        var data = "1234567890";
        response.writeHead(200, {
            'Content-Type': "application/x-www-form-urlencoded",
            'Content-Length': data.length
        });
        response.write(data, "utf8");
        response.end(util.format("onPostRequest(%s) at %s\n", request.url, new Date().toUTCString()));
    },

    onConnection: function (socket) {
        log.d("onConnection");
    },
    onClose: function () {
        log.d("onClose");
    },
    onCheckContinue : function (request, response) {
        log.d("onCheckContinue");
    },
    onConnect: function (request, socket, head) {
        log.d("onConnect");
    },
    onUpgrade: function (request, socket, head) {
        log.d("onUpgrade");
    },
    onClientError: function (exception) {
        log.d("onClientError");
    }
});

var httpServer = new HttpTestServer();

httpServer.start(testServerPort);