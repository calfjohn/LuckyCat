/**
 *  Test game server function via http query, need run GameServer first.
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
    req.write(JSON.stringify(vData));
    req.end();
    return req;
};

describe("=================================================================================\n" +
    "    Test GameServer", function() {

    it("Combat", function(done) {
        var info = {};
        info.uuid = 10000;
        info.monster_id = 0;
        postDataTo("/game/combat", info, function(res) {
            res.on("data", function(chunk) {
                console.log(chunk.toString());
                done();
            });
        });
    });
});

