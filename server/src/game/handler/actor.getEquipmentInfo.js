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
            log.d("responseResult", respData);
            res.write(JSON.stringify(respData));
            res.end();
        };

        var getEquipmentInfo = function(equipment) {
            if (! equipment) next();
            responseResult(equipment.getAllInfo());
        };

        var getEquipment = function(actor) {
            if (! actor) next();
            require("../ActorEquipments").getEquipment(actor.id, getEquipmentInfo);
        };

        if (info) {
            var uuid = info.header.token;
            require("../Actors").getActor(uuid, getEquipment);
        } else {
            next();
        }



    });
};