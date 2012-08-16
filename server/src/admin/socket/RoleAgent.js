
//定义获取数据消息key
var ROLE_LOGIN = "login";
var ROLE_LOGOUT = "logout";

module.exports = function(client) {

    client.on(ROLE_LOGIN, function() {
        client.emit(ROLE_LOGIN, "some data as result." + new Date().toLocaleString());
    });

    client.on(ROLE_LOGOUT, function() {
        client.emit(ROLE_LOGOUT);
    });
};
