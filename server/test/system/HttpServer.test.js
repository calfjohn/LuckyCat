/* simple test for get and post http method. */

/******************************************************
 *  Copy below code to index.js for running a server.
 */
require("../../src/system/HttpServer");
require("../../src/system/Log");

var assert = require("assert");
var http = require("http");
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
        log.d("onGetRequest");
    },

    onPostRequest: function(request, response) {
        var data = "1234567890";
        response.writeHead(200, {
            'Content-Type': "application/x-www-form-urlencoded",
            'Content-Length': data.length
        });
        response.write(data, "utf8");
        response.end(util.format("onPostRequest(%s) at %s\n", request.url, new Date().toUTCString()));
        //log.d("onPostRequest");
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
/*******************************************************************++*/
//var httpServer = new HttpTestServer().start(testServerPort);

describe("=================================================================================\n" +
    "    Test HttpService:", function(){
    describe("# http get test", function() {
        before(function() {
            console.log("-------------------------------------\n");
        });

        after(function() {
            console.log("-------------------------------------\n");
        });

        it("Get method", function(done) {
            http.request({
                    host:   "localhost",
                    port:   testServerPort,
                    path:   "/",
                    method: "GET"
                },
                function(response) {
                    assert.equal(response.statusCode, 200);

                    response.on("data", function(chunk) {
                        console.log("Get method on data, trunk:\n" + chunk);
                    });

                    response.on("end", function() {
                        console.log("Get method on end\n")
                        done();
                    });

                    console.log("Get method call http.request callback end.\n")
                }
            ).end();
        });
    });

    describe("# http post test", function() {
        before(function() {
            console.log("-------------------------------------\n");
        });

        after(function() {
            console.log("-------------------------------------\n");
        });

        it("Post method test", function(done) {
            var postReq;
            postReq = http.request({
                    host:"localhost",
                    port:testServerPort,
                    path:"/",
                    method:"POST"
                },
                function (response) {
                    assert.equal(response.statusCode, 200);

                    response.on("data", function (chunk) {
                        console.log("Post method on data, trunk:\n" + chunk);
                    });

                    response.on("end", function () {
                        console.log("Post method on end\n")
                        done();
                        console.log("finished!!");
                    });

                    console.log("Post method call http.request callback end.\n")
                }
            );
            postReq.end();
        });
    });
});