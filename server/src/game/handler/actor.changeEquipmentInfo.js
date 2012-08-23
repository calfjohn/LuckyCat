/**
 * Created with JetBrains WebStorm.
 * User: lihex
 * Date: 12-8-16
 * Time: 下午5:33
 * To change this template use File | Settings | File Templates.
 */


require("../../system/Log");

var reference_1 = {
    desc:
        "更新玩家装备信息",

    in: {
        part:
            "1 head, 2 hand, 3 body, 4 foot",
        id:
            "装备的ID,从getEquipmentInfo中获得。-1表示卸下该部位装备。"
    },

    out: "",
    result: {
        0:
            "操作成功",
        1:
            "非法id"
    }
};

module.exports.initReference = function(ref) {
    // 当前是版本1 所以填写文档到ref[1]
    ref[1] = reference_1;
};


module.exports.handler = function (req, res, next) {
    var log = new Log("actor.changeEquipmentInfo");

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
            var result = ret.result;
            var out = ret.out;
            var header = info.header;
            var meta = info.meta;
            respData.heard = header;
            respData.meta = meta;
            respData.meta.out = out;
            respData.meta.result = result;
            log.d("responseResult", respData);
            res.write(JSON.stringify(respData));
            res.end();
        };

        if (info) {
            var uuid = info.header.token;
            require("../Actors").getActor(uuid, function(actor){
                if (actor != null){
                    var part = parseInt(info.meta.in.part);
                    var id = parseInt(info.meta.in.id);
                    actor.changeEquipment(part, id, responseResult);
                }
            });
        } else {
            next();
        }



    });
};