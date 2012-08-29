/**
 * Created with JetBrains WebStorm.
 * User: lihex
 * Date: 12-8-29
 * Time: 上午11:35
 * To change this template use File | Settings | File Templates.
 */

require("../../system/Log");

module.exports.handler = function (req, res, next) {
    var log = new Log("getBasicInfo");

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
            var uuid = parseInt(info.header.token);
            var me = require("../Actors").getActor(uuid)._dbBasic;
            var actors = require("../Actors")._cacheActors;
            var ret = [];
            for (var key in actors) {
                if((me.uuid+"") == key) continue;
                var _actor = {};
                _actor.uuid = actors[key].uuid;
                _actor.nickname = actors[key].nickname;
                _actor.image_id = actors[key].image_id;
                _actor.level = actors[key].level;
                _actor.career_id = actors[key].career_id;
                ret.push(_actor);
            }
            responseResult(ret);

        } else {
            next();
        }

    });
};