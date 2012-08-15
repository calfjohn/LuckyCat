/**
 * Created with JetBrains WebStorm.
 * User: lihex
 * Date: 12-8-14
 * Time: 上午11:33
 * To change this template use File | Settings | File Templates.
 */

require("../system/Class");

ActorEquipment = Class.extend({
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
    },

    getAllInfo:function () {
        var db = this._db;
        return db;
    }
});