/**
 * Created with JetBrains WebStorm.
 * User: lihex
 * Date: 12-8-20
 * Time: 下午5:14
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


describe("============================================================================\n" +
    "    Test Actor GetSkillInfo", function() {

    it("GetSkillInfo", function(done) {
        var info = {};
        var header = {
            token: "2", //til now we use uuid instead
            index : 0
        };
        var meta = {
            mod : "actor",
            do: "getSkillInfo",
            in:{},
            out:{}
        };

        info.header = header;
        info.meta = meta;
        postDataTo("/game/actor/getSkillInfo", info, function(res) {
            res.on("data", function(chunk) {
                console.log(chunk.toString());
                done();
            });
        });
    });
});