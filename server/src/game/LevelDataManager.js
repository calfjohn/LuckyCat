/**
 * Created with JetBrains WebStorm.
 * User: zhuxiaozhong
 * Date: 12-8-22
 * Time: 下午5:25
 * To change this template use File | Settings | File Templates.
 */
if (global.LevelDataManager) {
    module.exports = LevelDataManager;
    return;
}

require("../system/DBAgent");
require("../system/Log");
require("./Actor");

var log = new Log("DictManager");
var util = require("util");

LevelDataManager = {
    _dbAgent : null,
    _mMapMonster : null,
    initInstance:function (dbConfig, callback) {
        LevelDataManager._dbAgent = new DBAgent(dbConfig);
        LevelDataManager._dbAgent.connect(true);
        // Cache all equipment data on server start
        LevelDataManager._dbAgent.query("SELECT * FROM `dict_monster`", function (err, rows) {
            if (! err) {
                LevelDataManager._mMapMonster = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var id= "" + data.id;
                    LevelDataManager._mMapMonster[id] = data;
                }
            }
            callback(err);
        });
    },

    getEquipmentByID: function(id, callback) {
        //get a actor basic info by uuid
        var equipment = LevelDataManager._mMapMonster[""+id];
        if(undefined == equipment){
            equipment = null;
        }
        callback(equipment);
    },
    getMonsterBy


};

module.exports = LevelDataManager;