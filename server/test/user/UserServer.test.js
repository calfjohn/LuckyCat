/**
 *  Test user server function via http query, need run UserServer first.
 */

var http = require("http");

var postDataTo = function (sPath, vData, fCallback) {
    var opts = {
        host: "localhost",
        port: 11111,
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
    "    Test UserServer", function() {

    it("Login", function(done) {
        var info = {};
        info.udid = "2234567890";
        postDataTo("/user/login", info, function(res) {
            res.on("data", function(chunk) {
                console.log(chunk.toString());
                done();
            });
        });
    });
});