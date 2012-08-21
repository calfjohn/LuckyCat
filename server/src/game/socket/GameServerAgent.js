
require("../../system/Log");

var msg = require("../../config/ws.Messages")
    ,log = new Log("GameServerAgent");

module.exports.handler = function() {
    var socket = module.exports.socket;
    socket.emit(msg.server.STATUS, "from GameServerAgent");
};
