/**
 * Actors controller for cache、 sync with database.
 */
(function(){
    if (global.Actors) {
    module.exports = Actors;
    return;
}

require("../system/DBAgent");
require("../system/Log");
require("./Actor");
require("./DictManager")

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
        // first, define some helper function to parse data from db results
        var getActorData = function(err, rows) {
            /**
             *   Actors._cacheActors struct:
             *     |--UUID:data
             */
            Actors._cacheActors = {};
            for (var i = 0; i < rows.length; ++i) {
                var data = rows[i];
                var strUUID = "" + data.uuid;
                Actors._cacheActors[strUUID] = data;
            }
        };
        var getActorEquipmentData = function(err, rows) {
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
        };
        var getActorSkillData = function(err, rows) {
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
        };


        // second, do query operation for get data from db, thus cache all actors data on server start
        // step 1, query actor data
        Actors._dbAgent.query("SELECT * FROM `actor`", function (err, rows) {
            // step 1 done, cache actor data
            getActorData(err, rows);
            // step 2, query actor_equipment data
            Actors._dbAgent.query("SELECT * FROM `actor_equipment`", function (err, rows) {
                // step 2 done, cache actor_equipment data
                getActorEquipmentData(err, rows);
                // step 3, query actor_skill data
                Actors._dbAgent.query("SELECT * FROM `actor_skill`", function (err, rows) {
                    // step 3 done, cache actor_skill data
                    getActorSkillData(err, rows);

                    // all data cached, call callback
                    callback(err);
                });
            });
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
        var actor =  Actors._cacheActors[""+uuid];
        if(undefined == actor){
            actor = null;
        }
        else
        {
            Actors.calculateCapablity(actor);
        }

        return actor;
    },

    updateProgress: function(id, chapterId, pageId){
        var strUUID = "" + id;
        if (chapterId < Actors._cacheActors[strUUID].chapter_id ||
            (chapterId == Actors._cacheActors[strUUID].chapter_id && pageId <= Actors._cacheActors[strUUID].page_id)) {
            return;
        }

        Actors._cacheActors[strUUID].chapter_id = chapterId;
        Actors._cacheActors[strUUID].page_id = pageId;
    },

    calculateCapablity: function(actor){
        var career = DictManager.getCareerByID(actor.career_id);

        //玩家基本属性
        actor.attack = career.attack*Math.pow(1 + career.attack_growth, actor.level);
        actor.defence = career.defence*Math.pow(1 + career.defence_growth, actor.level);
        actor.hp = career.life*Math.pow(1 + career.life_growth, actor.level);
        actor.speed = career.speed*Math.pow(1 + career.speed_growth, actor.level);

        //装备基本属性

        //技能基本属性
    },

    writeBackActorById: function(uuid, callback){
        var actor = Actors._cacheActors["" + uuid];
        if(undefined!=actor){
            Actors._dbAgent.query("UPDATE `actor` SET ? WHERE `actor`.`id` = ?", [actor, actor.id], function(err, result){
                if (err) throw err;
                log.d("---++++-------");
                log.d(result);
            });
        }
    }
};


module.exports = Actors;
})();
