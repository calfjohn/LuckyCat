
var userServer = require("./user/UserServer").initInstance(function(err) {
    if (err) {
        console.log(err);
        return;
    }
    console.log("begin listen...");
    userServer.listen(11111);
});
console.log("create ok");
