
require("../../system/Log");

module.exports = function(req, res, next) {
    var name = req.body.role_name;
    var password = req.body.role_password;

    // 验证用户名密码，最后成功的话给一个token
    req.session.token = name;
    res.redirect("/");
};