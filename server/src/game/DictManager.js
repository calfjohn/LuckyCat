/**
 * Created with JetBrains WebStorm.
 * User: lihex
 * Date: 12-8-16
 * Time: 下午12:07
 * To change this template use File | Settings | File Templates.
 */

if (global.DictManager) {
    module.exports = DictManager;
    return;
}

require("../system/DBAgent");
require("../system/Log");
require("./Actor");

var log = new Log("DictManager");
var util = require("util");

DictManager = {
    _dbAgent : null,
    _cacheDictEquipment: null,
    _cacheDictMonster: null,
    initInstance:function (dbConfig, callback) {
        DictManager._dbAgent = new DBAgent(dbConfig);
        DictManager._dbAgent.connect(true);

        DictManager.queryDictEquipment(function(){
            DictManager.queryDictMonster(callback);
        })
    },
    queryDictEquipment: function ( callback )
    {
        // Cache all equipment data on server start
        DictManager._dbAgent.query("SELECT * FROM `dict_equipment`", function (err, rows) {
            if (! err) {
                /**
                 *   DictManager._cacheDictEquipment struct:
                 *     |--id:key
                 *          |--data:value
                 */
                DictManager._cacheDictEquipment = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id= "" + data.id;
                    DictManager._cacheDictEquipment[id] = data;
                }
            }
            callback(err);
        });
    },
    queryDictMonster: function(callback)
    {
        DictManager._dbAgent.query("SELECT * FROM `dict_monster`", function (err, rows) {
            if (! err) {
                /**
                 *   DictManager._cacheDictEquipment struct:
                 *     |--id:key
                 *          |--data:value
                 */
                DictManager._cacheDictMonster = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id= "" + data.id;
                    DictManager._cacheDictMonster[id] = data;
                }
            }
            callback(err);
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
    }


};

module.exports = DictManager;