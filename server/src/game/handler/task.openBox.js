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

        var getOpenBoxGetAward = function(taskId,boxId) {
            if (! actor) next();
            if("basic" == info.meta.in.category){
                var ret_1={"id":1,"num":101};
                responseResult(actor.getBasicInfo());
            }else{
                var ret_2={"id":2,"num":202};
                responseResult(ret_2);
            }
        };

        if (info) {
//            var uuid = parseInt(info.header.token);
//            require("../Actors").getActor(uuid, getBasicInfo);
            getOpenBoxGetAward(1,1);
        } else {
            next();
        }


    });
};