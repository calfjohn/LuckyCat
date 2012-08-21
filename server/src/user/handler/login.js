/**
 * Authorize user.
 */

require("../../system/Log");

module.exports.handler = function(req, res, next) {
    var log = new Log("login");

    var chunks = [];
    req.on("data", function(chunk) {
        chunks.push(chunk);
    });
    req.on("end", function () {
        var info = JSON.parse(Buffer.concat(chunks));
        chunks = undefined;
        log.d("request:", info);

        var users = require("../users");
        var responseUUID = function (res, uuid) {
            var resInfo = {};
            resInfo.uuid=uuid;
            var data = JSON.stringify(resInfo);
            log.d("responseUUID:", data);
            res.header('Content-Type', 'text/plain');
            res.write(data);
            res.end();
        };

        var fCreateUser = function() {
            users.createUser(info, function(uuidNew) {
                if (uuidNew) {
                    responseUUID(res, uuidNew);
                    return;
                }
                log.d("can't create new uuid!");
                next();
            })
        };

        var fFindUser = function () {
            users.findUser(info, function(uuid) {
                if (uuid) {
                    responseUUID(res, uuid);
                    return;
                }
                fCreateUser();
            });
        };

        if (info) {
            fFindUser();
        } else {
            next();
        }
    });
}