/**
 * Created with JetBrains WebStorm.
 * User: lihex
 * Date: 12-8-14
 * Time: 上午11:42
 * To change this template use File | Settings | File Templates.
 */

require("../../system/Log");

module.exports = function (req, res, next) {
    var log = new Log("actor.getEquipmentInfo");

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
            respData.meta.result = 0;
            log.d("responseResult", respData);
            res.write(JSON.stringify(respData));
            res.end();
        };

        if (info) {
            var uuid = info.header.token;
            require("../Actors").getActor(uuid, function(actor){
                if (actor != null){
                    var part = parseInt(info.meta.in.part);
                    if(0 == part){
                        responseResult(actor.getAllEquipments());
                    }
                    if(1 == part){
                        responseResult(actor.getEquippedEquipment());
                    }
                }
            });
        } else {
            next();
        }



    });
};