/**
 * Created with JetBrains WebStorm.
 * User: lihex
 * Date: 12-8-14
 * Time: 上午11:26
 * To change this template use File | Settings | File Templates.
 */


if (global.ActorEquipments) {
    module.exports = ActorEquipments;
    return;
}

require("../system/DBAgent");
require("../system/Log");
require("./ActorEquipment");

var log = new Log("ActorEquipments")
    , util = require("util");

ActorEquipments = {
    _dbAgent : null,
    _cache: null,
    initInstance : function(dbConfig, callback) {
        ActorEquipments._dbAgent = new DBAgent(dbConfig);
        ActorEquipments._dbAgent.connect(true);
        // Cache all actor_equipment data on server start
        ActorEquipments._dbAgent.query("SELECT * FROM `actor_equipment`", function (err, rows) {
            if (err) {
                throw err;
                return;
            }
            ActorEquipments._cache = {};
            for(var i = 0; i < rows.length; ++i){
                var data = rows[i];
                var strActorID= "" + data.actor_id;
                var datas = ActorEquipments._cache[strActorID];
                if(undefined == datas) {
                    datas = [];
                }
                datas[datas.length] = data;
                ActorEquipments._cache[strActorID] = datas;
            }
        });
        process.nextTick(function() {
            callback(null);
        });
    },

    getEquipment: function(actorID, callback) {
        var rows = ActorEquipments._cache[""+actorID];
        var data = (rows.length) ? rows[0]: null;
        callback(new ActorEquipment(data));
    }
};


module.exports = ActorEquipments;