
require("../../system/Log");

var msg = require("../../config/ws.Messages")
    ,log = new Log("AdminServerAgent");

module.exports.handler = function(client) {
    console.log('A socket from server connected!');

    client.on(msg.server.STATUS, function(data) {
        log.d("on Message:", msg.server.STATUS, ", data:", data);
    });
};
