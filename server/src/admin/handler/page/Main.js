require("../../../system/Log");

module.exports = function(req, res, next) {
    if (req.session.user) {
        res.render("index");
    } else {
        res.redirect("/login");
    }
};