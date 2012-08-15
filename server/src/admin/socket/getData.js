module.exports = function(client) {

    var fGetData = function() {
        client.emit("getData", "some data as result." + new Date().toLocaleString());
    }
    client.on("getData", fGetData);
    client.on("updateData", fGetData);
};
