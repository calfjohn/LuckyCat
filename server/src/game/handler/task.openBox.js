/**
 * Created with JetBrains WebStorm.
 * User: marucs
 * Date: 12-8-9
 * Time: 上午9:53
 * To change this template use File | Settings | File Templates.
 */

require("../../system/Log");
require("../DictDataBox");

module.exports = function (req, res, next) {
    var log = new Log("openBox");

    DictBox.initDictData();



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
            //var ret_2={"id":2,"num":202};
            //var array_ = {{"id":2,"num":202},{"id":2,"num":202},{"id":2,"num":202}};
            var argIn = info.meta.in;
            var ary = new Array();
            for ( var i = 1; i < 4; i++ )
            {
                var obj = new Object();
                obj.id = i*2;
                obj.type = i+1;
                obj.num = 100 + i;

                ary.push(obj);
            }
            responseResult(ary);
        };

        if (info) {
//            var uuid = parseInt(info.header.token);
//            require("../Actors").getActor(uuid, getBasicInfo);
            getOpenBoxGetAward(info);
        } else {
            next();
        }


    });
};