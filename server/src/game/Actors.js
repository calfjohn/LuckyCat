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

var log = new Log("Actors")
    , util = require("util");

Actors = {
    _dbAgent : null,
    initInstance : function(dbConfig, callback) {
        Actors._dbAgent = new DBAgent(dbConfig);
        Actors._dbAgent.connect(true);
        process.nextTick(function() {
           callback(null);
        });
    },

    getActor: function(uuid, callback) {
        Actors._dbAgent.query("SELECT * FROM `actor` WHERE `id` = ?", [uuid], function (err, rows) {
            if (err) {
                throw err;
                return;
            }
            var len = rows.length;
            var data = (rows.length) ? rows[0]: null;
            callback(new Actor(data));
        });
    },

    //根据输入的章节、页面号更新进度状态
    //章节号默认递增、页面号默认递增，且都不重复
    updateProgress: function(uuid, chapter_id, page_id) {
        Actors._dbAgent.query("UPDATE `actor` SET `chapter_id` = ? AND `page_id` = ? WHERE `id` = ? AND (`chapter_id` > ? OR (`chapter_id` = ? AND `page_id` < ?))",
                [chapter_id, page_id, uuid, chapter_id, chapter_id, page_id], function (err) {
            if (err) {
                throw err;
            }

            return true;
        });
    }
};


module.exports = Actors;