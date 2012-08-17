/**
 * Created with JetBrains WebStorm.
 * User: calf
 * Date: 12-8-10
 * Time: 上午9:53
 * To change this template use File | Settings | File Templates.
 */

require("../../system/Log");

module.exports = function (req, res, next) {
    var log = new Log("battle.fight1");

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

        var getBattelResult = function(uuid, data) {
            var ret={};
            ret.result = {};

            if(data == undefined)
            {
                ret.result.state = 0;
                ret.result.type = 1;
                return ret;
            }

            //更新玩家进度
            require("../Actors").updateProgress(uuid, data.chapter_id, data.id);

            ret.award = {};
            ret.award.item = [];
            //不发放重复奖励
            if(data.bonuse_repeat)
            {
                ret.award.gold = 10;
                ret.award.exp = 100;
                ret.award.item.push({itemId:1, count:1});
                ret.award.item.push({itemId:2, count:3});
            }

            ret.result.type = 1;
            ret.result.state = 1;

            responseResult(ret);
        };

        if (info) {
            //receive input parameter
            var chapterId = parseInt(info.meta.in.chapterId);
            var pageId = parseInt(info.meta.in.pageId);
            var uuid = parseInt(info.header.token);

            var data = require("../Level").getLevel(chapterId, pageId);
            getBattelResult(uuid, data);
        } else {
            next();
        }

    });
};