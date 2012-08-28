/**
 * Created with JetBrains WebStorm.
 * User: cocos2d
 * Date: 12-8-27
 * Time: 上午9:47
 * To change this template use File | Settings | File Templates.
 */

require("../../system/Log");
require("../Battle");

module.exports.handler = function (req, res, next) {
    var log = new Log("battle.fight3");

    var chunks = [];
    req.on("data", function(chunk) {
        chunks.push(chunk);
    });

    req.on("end", function () {
        var info = JSON.parse(Buffer.concat(chunks));
        chunks = undefined;
        log.d("request:", info);

        var responseResult = function (ret) {
            var respData={};
            var out = ret;
            var header = info.header;
            var meta = info.meta;
            respData.header = header;
            respData.meta = meta;
            respData.meta.out = out;
            log.d("responseResult", respData);
            res.write(JSON.stringify(respData));
            res.end();
        };

        if (info) {
            //receive input parameter
            var uuid = parseInt(info.header.token);
            var actor1 = require("../Actors").getActorFromCache(uuid);

            var actorId = parseInt(info.meta.in.actorId);
            var actor2 = require("../Actors").getActorFromCache(actorId);

            var team = {};
            team.A = Battle.teamUp(actor1, "A");
            team.B = Battle.teamUp(actor2, "B");
            Battle.fight(team, responseResult, 3);
        } else {
            next();
        }
    });
};