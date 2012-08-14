/**
 * Created with JetBrains WebStorm.
 * User: lihex
 * Date: 12-8-9
 * Time: 上午11:37
 * To change this template use File | Settings | File Templates.
 */

var http = require("http");

var postDataTo = function (sPath, vData, fCallback) {
    var opts = {
        host: "localhost",
        port: 22222,
        method: 'POST',
        path: sPath
    };
    var cb = fCallback ? fCallback : function(res) {console.log(res);};
    var req = require("http").request(opts, cb);
    var data = JSON.stringify(vData);
    req.setHeader('Content-Type', 'application/x-www-form-urlencoded');
    req.setHeader('Content-Length', data.length);
    req.end(data);
    return req;
};


describe("=================================================================================\n" +
    "    Test Actor", function() {

    it("GetActorInfo", function(done) {
        var info = {};
        var header = {
            token: "0",
            index : 0
        };
        var meta = {
            mod : "actor",
            do: "getActorInfo",
            in:{"category": "basic"},
            out:{}
        };

        info.header = header;
        info.meta = meta;
        postDataTo("/game/actor/getActorInfo", info, function(res) {
            res.on("data", function(chunk) {
                console.log(chunk.toString());
                done();
            });
        });
    });
});