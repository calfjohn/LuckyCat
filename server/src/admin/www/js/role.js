//定义获取数据消息key
var ROLE_LOGIN = "login";
var ROLE_LOGOUT = "logout";

role = {
    //WebSockets引用
    _socket: null,

    init: function() {
        //创建WebSockets
        var socket = io.connect(adminServer, { port: 80 });
        //响应ws消息
        socket.on(ROLE_LOGIN, this.onLogin);
        socket.on(ROLE_LOGOUT, this.onLogout);
        socket.on("error", function(err) {
            alert(err);
        })
        this._socket = socket;
    },

    login: function() {
        var name = document.getElementById("role_name");
        var pwd  = document.getElementById("role_password");

        this._socket.emit(ROLE_LOGIN, "aName", "aPwd");
    },

    onLogin: function(data) {
        var greeting = document.getElementById("greeting");
        greeting.innerHTML = "欢迎!" + data;

        document.getElementById("login").style.display="none";
        document.getElementById("logout").style.display="";
    },

    logout: function() {
        this._socket.emit(ROLE_LOGOUT);
    },

    onLogout: function() {
        var greeting = document.getElementById("greeting");
        greeting.innerHTML = "请登陆:";
        document.getElementById("logout").style.display="none";
        document.getElementById("login").style.display="";
    }
};
