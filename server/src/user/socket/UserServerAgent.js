
require("../../system/Log");

var msg = require("../../config/ws.Messages")
    ,log = new Log("UserServerAgent");

module.exports.handler = function() {
    var socket = module.exports.socket;
    socket.emit(msg.server.STATUS, 1);
};
