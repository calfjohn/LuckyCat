//定义获取数据消息key
var GET_DATA = 'login';
var UPDATE_DATA = 'logout';

//WebSockets引用
var socket;

function init() {
    //创建WebSockets
    socket = io.connect(adminServer, { port: 80 });
    document.getElementById('main').innerHTML = "init()";
    //响应getData消息请求
    socket.on(GET_DATA, onGetData);
    //发送getData消息请求
    socket.emit(GET_DATA);
}

//getData消息处理方法
function onGetData(data) {
    console.log(data);
    document.getElementById('main').innerHTML = (data);
}

// update数据
function update() {
    socket.on(UPDATE_DATA, onGetData);
    socket.emit(UPDATE_DATA);
}
