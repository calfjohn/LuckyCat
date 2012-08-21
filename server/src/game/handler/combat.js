/**
 * An actor combat with other actor.
 */

require("../../system/Log");

module.exports.handler = function (req, res, next) {
    var log = new Log("combat");

    var chunks = [];
    req.on("data", function(chunk) {
        chunks.push(chunk);
    });
    req.on("end", function () {
        var info = JSON.parse(Buffer.concat(chunks));
        chunks = undefined;
        log.d("request:", info);

        var responseResult = function (ret) {
            var data = JSON.stringify(ret);
            log.d("responseResult", data);
            res.write(data);
            res.end();
        };

        var doCombat = function(actor) {
            if (! actor) next();
            responseResult(actor.combatWithMonster(info.monster_id));
        };

        if (info) {
            require("../Actors").getActor(info.uuid, doCombat);
        } else {
            next();
        }
    });
};
