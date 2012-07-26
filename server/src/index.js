

var userServer = require("./user/UserServer").initServer(function(err) {
    if (err) {
        console.log(err);
        return;
    }
    console.log("begin listen...");
    userServer.listen(80);
});
console.log("create ok");
