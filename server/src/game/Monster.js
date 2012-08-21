/**
 * Created with JetBrains WebStorm.
 * User: cocos2d
 * Date: 12-8-10
 * Time: 下午4:16
 * To change this template use File | Settings | File Templates.
 */
/**
 * Monster controller for cache、 sync with database.
 */

if (global.Monster) {
    module.exports = Monster;
    return;
}

require("../system/DBAgent");
require("../system/Log");

var log = new Log("Monster")
    , util = require("util");

Monster = {
    _dbAgent : null,
    initInstance : function(dbConfig, callback) {
        Monster._dbAgent = new DBAgent(dbConfig);
        Monster._dbAgent.connect(true);
        // Cache all dict_page data on server start
        Monster._dbAgent.query("SELECT * FROM `dict_monster`", function (err, rows) {
            if (! err) {
                Monster._cache = {};
                for(var i = 0; i < rows.length; ++i){
                    var data = rows[i];
                    var strID = "" + data.id;
                    //log.d("datas:",data);
                    Monster._cache[strID] = data;
                    //log.d("cache:", Monster._cache);
                }
            }
            callback(err);
        });
    },

    getMonster: function(monsterId) {
        var strID = "" + monsterId;
        return Monster._cache[strID];
    }
};

module.exports = Monster;