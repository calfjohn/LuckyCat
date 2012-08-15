/**
 * Created with JetBrains WebStorm.
 * User: cocos2d
 * Date: 12-8-10
 * Time: 下午4:16
 * To change this template use File | Settings | File Templates.
 */
/**
 * Level controller for cache、 sync with database.
 */

if (global.Level) {
    module.exports = Level;
    return;
}

require("../system/DBAgent");
require("../system/Log");

var log = new Log("Level")
    , util = require("util");

Level = {
    _dbAgent : null,
    initInstance : function(dbConfig, callback) {
        Level._dbAgent = new DBAgent(dbConfig);
        Level._dbAgent.connect(true);
        // Cache all dict_page data on server start
//        Level._dbAgent.query("SELECT * FROM `dict_page`", function (err, rows) {
//            if (err) {
//                throw err;
//                return;
//            }
//            Level._cache = {};
//            for(var i = 0; i < rows.length; ++i){
//                var data = rows[i];
//                var strID = "" + data.id;
//                var datas = Level._cache[strID];
//                if(undefined == datas) {
//                    datas = [];
//                }
//                datas[datas.length] = data;
//                //log.d("datas:",datas);
//                Level._cache[strID] = datas;
//                //log.d("cache:", Level._cache);
//            }
//        });
//        process.nextTick(function() {
//            callback(null);
//        });
    },

    getLevel: function(uuid, chapterId, pageId, callback) {
        Level._dbAgent.query("SELECT 'bonus_repeat' FROM `dict_page` WHERE `chapter_id` = ? AND `id` = ?", [chapterId, pageId], function (err, rows) {
                if (err) {
                    throw err;
                }
                else{
                    var len = rows.length;
                    var data = (rows.length) ? rows[0]: null;
                    callback(uuid, chapterId, pageId, data);
                }
        });
     }
};

module.exports = Level;