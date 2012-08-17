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
    initInstance:function (dbConfig, callback) {
        Actors._dbAgent = new DBAgent(dbConfig);
        Actors._dbAgent.connect(true);
        // Cache all actors data on server start
        Actors._dbAgent.query("SELECT * FROM `actor`", function (err, rows) {
            if (err) {
                throw err;
                return;
            }
            Actors._cache = {};
            for (var i = 0; i < rows.length; ++i) {
                var data = rows[i];
                var strUUID = "" + data.uuid;
                Actors._cache[strUUID] = data;
            }
        });
        process.nextTick(function () {
            callback(null);
        });
    },

    getActor: function(uuid, callback) {
        var data = Actors._cache[""+uuid];
        if(undefined == data){
            data = null;
        }
        callback(new Actor(data));
    },

    getActorFromCache: function(uuid) {
        return Actors._cache[""+uuid];
    },

    updateProgress: function(uuid, chapterId, pageId){
        var strUUID = "" + uuid;
        if(chapterId < Actors._cache[strUUID].chapter_id ||
            (chapterId  == Actors._cache[strUUID].chapter_id && pageId <= Actors._cache[strUUID].page_id)){
            return;
        }

        Actors._cache[strUUID].chapter_id = chapterId;
        Actors._cache[strUUID].page_id = pageId;
    }
};


module.exports = Actors;