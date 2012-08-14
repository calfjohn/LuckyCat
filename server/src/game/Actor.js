/**
 * Actor model.
 */

require("../system/Class");

Actor = Class.extend({
    _db: {},                // actor database
    _tdb: {},               // actor temporary database, will not sync to database

    init: function(dbData) {
        if (dbData) {
            this._db = dbData;
        } else {
            this.initDefaultData();
        }
    },

    initDefaultData: function(){
        var db = this._db;
        db.exp = 0;
    },

    combatWithMonster: function (monster_id) {
        var db = this._db;
        var ret = {};
        // judge combat success or not.
        // if the monster id less than actor's exp, the combat success
        var val = (db.exp - monster_id);

        if (val > 0) {
            // success
            ret.add_exp = 5;
            ret.result = 1;
        } else if (val < 0) {
            // fail
            ret.add_exp = 3;
            ret.result = -1;
        } else {
            // draw
            ret.add_exp = 1;
            ret.result = 0;
        }
        db.exp += ret.add_exp;

        return ret;
    },

    getBasicInfo:function () {
        var db = this._db;
        var ret = {};
        ret.nickname = db.nickname;
        ret.image_id = db.image_id;
        ret.level = db.level;
        ret.exp = db.exp;
        ret.hp = db.hp;
        ret.career_id = db.career_id;
        ret.chapter_id = db.chapter_id;
        ret.page_id = db.page_id;
        return ret;
    }
});
