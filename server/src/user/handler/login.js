/**
 * Authorize user.
 */

module.exports = function(req, res, next) {
    var id = req.param("id");
    if (id) {
        res.header('Content-Type', 'text/plain');
        res.end(id);
    } else {
        next();
    }
}