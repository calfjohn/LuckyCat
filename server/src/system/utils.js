
if (! global.serverUtils) {
    serverUtils = {
        // callback: fucntion(err, ip)
        getHostIP: function(callback) {
            var socket = require("net").createConnection(80, "www.aRandomWebSite.com");
            socket.on("connect", function() {
                callback(null, socket.address().address);
                socket.end();
            });
            socket.on("error", callback);
        }
    };
}
module.exports = global.serverUtils;