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


        var getBattelResult = function(uuid, chapter_id, page_id) {
            var ret={};

            //关卡是否存在
            var data = require("../Level").getLevel(chapter_id, page_id);
            if(data == undefined)
            {
                return ret;
            }

            ret.result = {};

            //更新进度
            if(require("../Actors").updateProgress(uuid, chapter_id, page_id)){
                ret.award = {};
                ret.award.gold = 10;
                ret.award.exp = 100;
                ret.award.item = [];
                ret.award.item.push({itemId:1, count:1});
                ret.award.item.push({itemId:2, count:3});
                ret.result.state = 0;
                ret.result.type = 1;
            }
            else{
                ret.result.type = 1;
                ret.result.state = 1;
            }

            responseResult(ret);
        };

        if (info) {
            //receive input parameter
            var chapterId = parseInt(info.meta.in.chapterId);
            var pageId = parseInt(info.meta.in.pageId);
            var uuid = parseInt(info.header.token);

            getBattelResult(uuid, chapterId, pageId);
        } else {
            next();
        }


    });
};