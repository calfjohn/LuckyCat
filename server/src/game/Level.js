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
        process.nextTick(function() {
            callback(null);
        });
    },

    getLevel: function(chapterId, pageId) {
        Level._dbAgent.query("SELECT * FROM `dict_page` WHERE `chapter_id` = ? AND `id` = ?", [chapterId, pageId], function (err, rows) {
                var data;
                if (err) {
                    throw err;
                }
                else{
                    var len = rows.length;
                    data = (rows.length) ? rows[0]: null;
                }

                return data;
        });
     }
};

module.exports = Level;