/**
 * Actors controller for cache、 sync with database.
 */

if (global.Actors) {
    module.exports = Actors;
    return;
}

require("../system/DBAgent");
require("../system/Log");
require("./Actor");

var log, util;
log = new Log("Actors");
util = require("util");

Actors = {
    _dbAgent:null,
    _cacheActors:null,
    _cacheEquipments:null,
    _cacheSkills: null,
    initInstance:function (dbConfig, callback) {
        Actors._dbAgent = new DBAgent(dbConfig);
        Actors._dbAgent.connect(true);
        // Cache all actors data on server start
        Actors._dbAgent.query("SELECT * FROM `actor`", function (err, rows) {
            if (err) {
                throw err;
                return;
            }
            /**
             *   Actors._cacheActors struct:
             *     |--UUID:key
             *          |--data:value
             */
            Actors._cacheActors = {};
            for (var i = 0; i < rows.length; ++i) {
                var data = rows[i];
                var strUUID = "" + data.uuid;
                Actors._cacheActors[strUUID] = data;
            }
        });

        Actors._dbAgent.query("SELECT * FROM `actor_equipment`", function (err, rows) {
            if (err) {
                throw err;
                return;
            }
            /**
             *   Actors._cacheEquipments struct:
             *     |--actorID:key
             *          |--equipment_id:key
             *             |--data:value
             */
            Actors._cacheEquipments = {};
            for (var i = 0; i < rows.length; ++i) {
                var data = rows[i];
                var strActorID = "" + data.actor_id;
                var datas = Actors._cacheEquipments[strActorID];
                if (undefined == datas) {
                    datas = {};
                }
                datas["" + data.id] = data;
                Actors._cacheEquipments[strActorID] = datas;
            }
        });

        Actors._dbAgent.query("SELECT * FROM `actor_skill`", function (err, rows) {
            if (err) {
                throw err;
                return;
            }
            /**
             *   Actors._cacheSkills struct:
             *     |--actorID:key
             *          |--equipment_id:key
             *             |--data:value
             */
            Actors._cacheSkills = {};
            for (var i = 0; i < rows.length; ++i) {
                var data = rows[i];
                var strActorID = "" + data.actor_id;
                var datas = Actors._cacheSkills[strActorID];
                if (undefined == datas) {
                    datas = [];
                }
                datas.push(data);
                Actors._cacheSkills[strActorID] = datas;
            }
        });

        process.nextTick(function () {
            callback(null);
        });
    },

    getActor:function (uuid, callback) {
        //get a actor basic info by uuid
        var actorDB = Actors._cacheActors["" + uuid];
        var equipDB = null;
        var skillDB = null;
        if (undefined != actorDB) {
            // get the equipmnets by actor's actor_id
            equipDB = Actors._cacheEquipments["" + actorDB.id];
            skillDB = Actors._cacheSkills["" + actorDB.id];
        } else {
            actorDB = null;
        }
        callback(new Actor(actorDB, equipDB, skillDB));
    },

    getActorFromCache: function(uuid) {
        return Actors._cacheActors[""+uuid];
    },

    updateProgress: function(id, chapterId, pageId){
        var strUUID = "" + id;
        if (chapterId < Actors._cacheActors[strUUID].chapter_id ||
            (chapterId == Actors._cacheActors[strUUID].chapter_id && pageId <= Actors._cacheActors[strUUID].page_id)) {
            return;
        }

        Actors._cacheActors[strUUID].chapter_id = chapterId;
        Actors._cacheActors[strUUID].page_id = pageId;
    }
};


module.exports = Actors;
