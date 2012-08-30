/**
 * Created with JetBrains WebStorm.
 * User: lihex
 * Date: 12-8-16
 * Time: 下午12:07
 * To change this template use File | Settings | File Templates.
 */
(function(){
if (global.DictManager) {
    module.exports = DictManager;
    return 0;
}
require("../system/DBAgent");
require("../system/Log");
require("./Actor");

var log = new Log("DictManager");
var util = require("util");

DictManager = {
    _dbAgent : null,
    _cacheEquipment: null,
    _cacheCareer:null,
    _cacheMonster:null,
    _cacheLevel:null,
    _cacheEquipmentLevelGrowth: null,
    _cacheEquipmentRankGrowth: null,
    _cacheActorLevelUpgrade: null,
    _cacheSkill: null,
    initInstance:function (dbConfig, callback) {
        DictManager._dbAgent = new DBAgent(dbConfig);
        DictManager._dbAgent.connect(true);

        var getEquipData = function(err, rows){
            if (! err) {
                DictManager._cacheEquipment = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id= "" + data.id;
                    DictManager._cacheEquipment[id] = data;
                }
            }
        };

        var getCareerData = function(err, rows){
            if (! err) {
                DictManager._cacheCareer = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id= "" + data.id;
                    DictManager._cacheCareer[id] = data;
                }
            }
        };

        var getMonsterData = function(err, rows){
            if (! err) {
                DictManager._cacheMonster = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id= "" + data.id;
                    DictManager._cacheMonster[id] = data;
                }
            }
        };

        var getLevelData = function(err, rows){
            if (!err) {
                DictManager._cacheLevel = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var strID = "" + data.id + "-" + data.chapter_id;
                    DictManager._cacheLevel[strID] = data;
                }
            }
        };


        var getEquipmentLevelGrowth = function(err, rows){
            if (! err) {
                DictManager._cacheEquipmentLevelGrowth = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var level= "" + data.level;
                    DictManager._cacheEquipmentLevelGrowth[level] = data;
                }
            }
        };

        var getEquipmentRankGrowth = function(err, rows){
            if (! err) {
                DictManager._cacheEquipmentRankGrowth = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var rank = "" + data.rank;
                    DictManager._cacheEquipmentRankGrowth[rank] = data;
                }
            }
        };

        var getActorLevelUpgrade = function(err, rows){
            if (! err) {
                DictManager._cacheActorLevelUpgrade = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var level = "" + data.level;
                    DictManager._cacheActorLevelUpgrade[level] = data;
                }
            }
        };

        var getSkill = function(err, rows){
            if(!err){
                DictManager._cacheSkill = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id = "" + data.id;
                    DictManager._cacheSkill[id] = data;
                }
            }
        }

        // Cache all equipment data on server start
        // second, do query operation for get data from db, thus cache all actors data on server start
        // step 1, query actor data
        DictManager._dbAgent.query("SELECT * FROM `dict_equipment`", function (err, rows) {
            // step 1 done, cache actor data
            getEquipData(err, rows);
            // step 2, query actor_equipment data
            DictManager._dbAgent.query("SELECT * FROM `dict_career`", function (err, rows) {
                // step 2 done, cache actor_equipment data
                getCareerData(err, rows);
                DictManager._dbAgent.query("SELECT * FROM `dict_monster`", function (err, rows) {
                    getMonsterData(err, rows);
                    DictManager._dbAgent.query("SELECT * FROM `dict_equipment_level_growth`", function (err, rows) {
                        getEquipmentLevelGrowth(err, rows);
                        DictManager._dbAgent.query("SELECT * FROM `dict_equipment_rank_growth`", function (err, rows) {
                            getEquipmentRankGrowth(err, rows);
                            DictManager._dbAgent.query("SELECT * FROM `dict_page`", function (err, rows) {
                                getLevelData(err, rows);
                                DictManager._dbAgent.query("SELECT * FROM `dict_actor_level_upgrade`", function (err, rows) {
                                    getActorLevelUpgrade(err, rows);
                                    DictManager._dbAgent.query("SELECT * FROM `dict_skill`", function (err, rows) {
                                        getSkill(err, rows);
                                        // all data cached, call callback
                                         callback(err);
                                    });
                                });
                            });

                        });

                    });

                });
            });
        });
    },

    getEquipmentByID: function(id) {
        //get a actor basic info by uuid
        var equipment = DictManager._cacheEquipment[""+id];
        if(undefined == equipment){
            equipment = null;
        }
        return equipment;
    },

    getMonsterById: function(id) {
        var monster = DictManager._cacheMonster["" + id];
        if (monster)
        {
            return monster;
        }
        else
        {
            return null;
        }
    },


    getCareerByID: function(id) {
        //get a Creer basic info by id
        var career = DictManager._cacheCareer[""+id];
        if(undefined == career){
            career = null;
        }

        return career;
    },

    getLevel: function(chapterId, pageId) {
        var strID = "" + pageId + "-" + chapterId;
        var level =  DictManager._cacheLevel[strID];
        if(undefined == level){
            level = null;
        }

        return level;
    },

    getEquipLevelGrowthByLevel: function(level){
        //get a Growth  by level
        var growth = DictManager._cacheEquipmentLevelGrowth[""+level];
        if(undefined == growth){
            growth = null;
        }

        return growth;
    },

    getEquipRankGrowthByRank: function(rank){
        //get a Growth by rank
        var growth = DictManager._cacheEquipmentRankGrowth[""+rank];
        if(undefined == growth){
            growth = null;
        }

        return growth;
    },

    getActorLevelUpgradeByLevel: function(level){
        //get actor level upgrade by level
        var ret = DictManager._cacheActorLevelUpgrade[""+level];
        if(undefined == ret){
            ret = null;
        }
        return ret;
    },

    getSkillByID: function(id){
        var ret = DictManager._cacheSkill["" + id];
        if(undefined == ret){
            ret = null;
        }
        return ret;
    }


};

module.exports = DictManager;
})();
