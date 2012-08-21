/**
 * Created with JetBrains WebStorm.
 * User: marucs
 * Date: 12-8-9
 * Time: 上午9:53
 * To change this template use File | Settings | File Templates.
 */

require("../../system/Log");

module.exports.handler = function (req, res, next) {
    var log = new Log("getEventList");

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
            var header = info.header;
            var meta = info.meta;
            respData.heard = header;
            respData.meta = meta;

            if ( ret == null )
            {
                //failed. the box id is not exit.
                var out = new Object();
                out.result = 1;
                out.eventList = ret;
                respData.meta.out = out;
            }
            else
            {
                //open box success.
                var out = new Object();
                out.result = 0;
                out.eventList = ret;
                respData.meta.out = out;
            }
            log.d("responseResult", respData);
            res.write(JSON.stringify(respData));
            res.end();
        };

        var getEventList = function() {
            var argIn = info.meta.in;
            var ary = require("../Events").getASeriesOfEvent(argIn.eventId);

            responseResult(ary);
        };

        if (info) {
            getEventList(info);
        } else {
            next();
        }


    });
};