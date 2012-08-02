/**
 * An actor combat with other actor.
 */

require("../../system/Log");

module.exports = function (req, res, next) {
    var log = new Log("combat");

    req.on("data", function (chunk) {
        var info = JSON.parse(chunk.toString());
        log.d("request:", info);

        var responseResult = function (ret) {
            var data = JSON.stringify(ret);
            log.d("responseResult", data);
            res.write(data);
            res.end();
        };

        var doCombat = function(actor) {
            if (! actor) next();
            responResult(acotr.combatWithMonster(info.monster_id));
        };

        if (info) {
            require("../Actors").getActor(info.uuid, doCombat);
        } else {
            next();
        }
    });
};
