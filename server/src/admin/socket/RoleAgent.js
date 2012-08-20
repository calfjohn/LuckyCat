
require("../../system/Log");

var msg = require("../../config/ws.Messages")
    ,log = new Log("RoleAgent");


module.exports.handler = function(client) {
    console.log('A socket with session id(' + client.handshake.session.id + ') connected!');

    client.on(msg.role.LOGIN, function() {
        client.emit(msg.role.LOGIN, "some data as result." + new Date().toLocaleString());
    });

    client.on(msg.role.LOGOUT, function() {
        client.emit(msg.role.LOGOUT);
    });
};
