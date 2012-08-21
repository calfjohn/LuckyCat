/**
 * Created with JetBrains WebStorm.
 * User: lihex
 * Date: 12-8-20
 * Time: 下午4:39
 * To change this template use File | Settings | File Templates.
 */

require("../../system/Log");
var partAll = 0;
var partEquipped = 1;

module.exports.handler = function (req, res, next) {
    var log = new Log("actor.getSkillInfo");

    var chunks = [];
    req.on("data", function (chunk) {
        chunks.push(chunk);
    });
    req.on("end", function () {
        var info = JSON.parse(Buffer.concat(chunks));
        chunks = undefined;
        log.d("request:", info);

        var responseResult = function (ret) {
            var respData = {};
            var out = ret;
            var header = info.header;
            var meta = info.meta;
            respData.heard = header;
            respData.meta = meta;
            respData.meta.out = out;
            respData.meta.result = 0;
            log.d("responseResult", respData);
            res.write(JSON.stringify(respData));
            res.end();
        };

        if (info) {
            var uuid = info.header.token;
            require("../Actors").getActor(uuid, function (actor) {
                if (actor != null) {
                    //remove actor id
                    var skills = actor.getSkills();;
                    for (var i=0; i< skills.length; i++){
                         var skill = skills[i];
                        delete skill["actor_id"];
                    }
                    responseResult(skills);
                }
            });
        } else {
            next();
        }


    });
};