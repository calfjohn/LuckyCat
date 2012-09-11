
// add root exception handler
require("./system/Log");

var globalLog = new Log("global");
process.on("uncaughtException", function(err) {
    globalLog.e(err);
});

// start admin server
if (1) {
    var adminServer = require("./admin/AdminServer").initInstance(function() {
        console.log("admin server begin listen...");
        adminServer.start();
    });
};

// start user server
if (1) {
    var userServer = require("./user/UserServer").initInstance(function() {
        console.log("user server begin listen...");
        userServer.start();
    });
};

// start game server
if (1) {
    var gameServer = require("./game/GameServer").initInstance(function() {
        console.log("game server begin listen...");
        gameServer.start();
    });
};

// start browser server
if (1) {
    var browserServer = require("./browser/BrowserServer").initInstance(function() {
        console.log("browser server begin listen...");
        browserServer.start();
    });
};

console.log("create ok");
