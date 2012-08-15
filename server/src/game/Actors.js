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
    _cache: null,
    initInstance : function(dbConfig, callback) {
        Actors._dbAgent = new DBAgent(dbConfig);
        Actors._dbAgent.connect(true);
        // Cache all actors data on server start
        Actors._dbAgent.query("SELECT * FROM `actor`", function (err, rows) {
            if (err) {
                throw err;
                return;
            }
            Actors._cache = {};
            for(var i = 0; i < rows.length; ++i){
                var data = rows[i];
                var strUUID = "" + data.uuid;
                var datas = Actors._cache[strUUID];
                if(undefined == datas) {
                    datas = [];
                }
                datas[datas.length] = data;
                //log.d("datas:",datas);
                Actors._cache[strUUID] = datas;
                //log.d("cache:", Actors._cache);
            }
        });
        process.nextTick(function() {
           callback(null);
        });
    },

    getActor: function(uuid, callback) {
        var rows = Actors._cache[""+uuid];
        var data = (rows.length) ? rows[0]: null;
        callback(new Actor(data));
    },

    updateProgress: function(id, chapterId, pageId){
        var strUUID = "" + id;
        if(chapterId < Actors._cache[strUUID][0].chapter_id ||
            (chapterId  == Actors._cache[strUUID][0].chapter_id && pageId <= Actors._cache[strUUID][0].page_id)){
            return;
        }

        Actors._cache[strUUID][0].chapter_id = chapterId;
        Actors._cache[strUUID][0].page_id = pageId;
    }
};


module.exports = Actors;