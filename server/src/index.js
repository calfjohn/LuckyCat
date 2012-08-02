if (1) {
var userServer = require("./user/UserServer").initInstance(function(err) {
    if (err) {
        console.log(err);
        return;
    }
    console.log("user server begin listen...");
    userServer.listen(11111);
});
}
var gameServer = require("./game/GameServer").initInstance(function(err) {
    if (err) {
       console.log(err);
       return;
    }
    console.log("game server begin listen...");
    gameServer.listen(22222);
});
console.log("create ok");
