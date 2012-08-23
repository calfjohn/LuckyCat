/**
 * Created with JetBrains WebStorm.
 * User: lihex
 * Date: 8/23/12
 * Time: 4:59 PM
 * To change this template use File | Settings | File Templates.
 */

require("../../system/Log");

var reference_1 = {
    desc: "获得玩家已穿上的装备信息",
    in:{
        desc: "",
        type: "",
        fields: {}
    },

    out:{
        desc: "",
        type: "",
        fields: {
        }
    }

    },
    result:{
        0:"操作成功",
        1:"非法id"
    }
};

module.exports.initReference = function (ref) {
    // 当前是版本1 所以填写文档到ref[1]
    ref[1] = reference_1;
};


var partAll = 0;
var partEquipped = 1;

module.exports.handler = function (req, res, next) {
    var log = new Log("actor.getEquippedEquipment");

    var chunks = [];
    req.on("data", function (chunk) {
        chunks.push(chunk);
    });
    req.on("end", function () {
        var info = JSON.parse(Buffer.concat(chunks));
        chunks = undefined;
        log.d("request:", info);

        var responseResult = function (ret) {
            var respData = {};
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
            require("../Actors").getActor(uuid, function (actor) {
                if (actor != null) {
                    responseResult(actor.getEquippedEquipment());
                }
            });
        } else {
            next();
        }


    });
};