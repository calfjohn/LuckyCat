
require("../../system/Log");

module.exports = function(req, res, next) {
    var name = req.body.name;
    var password = req.body.password;
    console.log("/login:" + req.body);
    req.session.user = name;
    res.redirect("/");
};