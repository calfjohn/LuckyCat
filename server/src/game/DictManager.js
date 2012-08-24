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
    _cacheDictEquipment: null,
    _cacheDictCareer:null,
    _cacheDictMonster:null,
    _cacheDictLevel:null,
    initInstance:function (dbConfig, callback) {
        DictManager._dbAgent = new DBAgent(dbConfig);
        DictManager._dbAgent.connect(true);

        var getEquipData = function(err, rows){
            if (! err) {
                DictManager._cacheDictEquipment = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id= "" + data.id;
                    DictManager._cacheDictEquipment[id] = data;
                }
            }
        };

        var getCareerData = function(err, rows){
            if (! err) {
                DictManager._cacheDictCareer = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id= "" + data.id;
                    DictManager._cacheDictCareer[id] = data;
                }
            }
        };

        var getMonsterData = function(err, rows){
            if (! err) {
                DictManager._cacheDictMonster = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id= "" + data.id;
                    DictManager._cacheDictMonster[id] = data;
                }
            }
        };

        var getLevelData = function(err, rows){
            if (!err) {
                DictManager._cacheDictLevel = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var strID = "" + data.id + "-" + data.chapter_id;
                    DictManager._cacheDictLevel[strID] = data;
                }
            }
        };

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
                        // all data cached, call callback
                        callback(err);
                        });
                  });
            });
    },

    getEquipmentByID: function(id, callback) {
        //get a actor basic info by uuid
        var equipment = DictManager._cacheDictEquipment[""+id];
        if(undefined == equipment){
            equipment = null;
        }
        callback(equipment);
    },

    getMonsterById: function(id) {
        var monster = DictManager._cacheDictMonster["" + id];
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
        //get a actor basic info by uuid
        var career = DictManager._cacheDictCareer[""+id];
        if(undefined == career){
            career = null;
        }

        return career;
    },

    getLevel: function(chapterId, pageId) {
        var strID = "" + pageId + "-" + chapterId;
        var level =  DictManager._cacheDictLevel[strID];
        if(undefined == level){
            level = null;
        }

        return level;
    }
};

module.exports = DictManager;
})();
