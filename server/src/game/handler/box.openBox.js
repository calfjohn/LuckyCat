/**
 * Created with JetBrains WebStorm.
 * User: marucs
 * Date: 12-8-9
 * Time: 上午9:53
 * To change this template use File | Settings | File Templates.
 */

require("../../system/Log");

module.exports = function (req, res, next) {
    var log = new Log("openBox");

    //DictBox.initDictData();



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
            respData.heard = header;
            respData.meta = meta;
            respData.meta.out = out;
            log.d("responseResult", respData);
            res.write(JSON.stringify(respData));
            res.end();
        };

        var getOpenBoxGetAward = function() {
            var argIn = info.meta.in;
            var ary = require("../Box").openBox(argIn.boxId);

            log.d("OpenBox ary" ,ary);
            responseResult(ary);
        };

        if (info) {
            getOpenBoxGetAward(info);
        } else {
            next();
        }


    });
};