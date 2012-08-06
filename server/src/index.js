
// add root exception handler
require("./system/Log");

var globalLog = new Log("global");
process.on("uncaughtException", function(err) {
    globalLog.e(err);
});

// start user server
if (1) {
    var userServer = require("./user/UserServer").initInstance(function(err) {
        if (err) {
            console.log(err);
            return;
        }
        console.log("user server begin listen...");
        userServer.listen(11111);
    });
};

// start game server
if (1) {
    var gameServer = require("./game/GameServer").initInstance(function(err) {
        if (err) {
           console.log(err);
           return;
        }
        console.log("game server begin listen...");
        gameServer.listen(22222);
    });
};

console.log("create ok");
