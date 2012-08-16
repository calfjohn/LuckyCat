/**
 * Created with JetBrains WebStorm.
 * User: cocos2d
 * Date: 12-8-16
 * Time: 上午9:47
 * To change this template use File | Settings | File Templates.
 */

require("../../system/Log");

module.exports = function (req, res, next) {
    var log = new Log("battle.fight2");

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
            var chapterId = parseInt(info.meta.in.monster_id);
            var uuid = parseInt(info.header.token);

            //to do something
        } else {
            next();
        }

    });
};