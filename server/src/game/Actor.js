/**
 * Actor model.
 */

require("../system/Class");
require("../system/Log");


Actor = Class.extend({
    _dbBasic: {},                // basic data from table actor
    _dbEquipment: {},           // equipment data from table actor_equipment
    _tdb: {},               // actor temporary database, will not sync to database
    _log: new Log("getBasicInfo"),

    init: function(basicDB, equipDB) {
        if (basicDB && equipDB) {
            this._dbBasic = basicDB;
            this._dbEquipment = equipDB;
        } else {
            this.initDefaultData();
        }
    },

    initDefaultData: function(){
        var db = this._dbBasic;
        db._dbBasic.exp = 0;
    },

    getBasicInfo:function () {
        var db = this._dbBasic;
        var ret = {};
        ret.id = db.id;
        ret.nickname = db.nickname;
        ret.image_id = db.image_id;
        ret.level = db.level;
        ret.exp = db.exp;
        ret.hp = db.hp;
        ret.career_id = db.career_id;
        ret.chapter_id = db.chapter_id;
        ret.page_id = db.page_id;
        return ret;
    },

    getAllEquipments: function(){
        var db = this._dbEquipment;
        var ret = [];
        for(var key in db){
            var equipment = {};
            var value = db[key];
            equipment.equip_id = value.equip_id;
            equipment.level = value.level;
            equipment.rank = value.rank;
            equipment.color = value.color;
            equipment.item1_id = value.item1_id;
            equipment.item2_id = value.item2_id;
            equipment.item3_id = value.item3_id;
            equipment.item4_id = value.item4_id;
            equipment.item5_id = value.item5_id;
            ret.push(equipment);
        }
        return ret;
    },

    getEquippedEquipment: function(){
        var basicDB = this._dbBasic;
        var equipDB = this._dbEquipment;
        var ret = {};
        ret.eq_head_id = basicDB.eq_head_id
        ret.eq_body_id = basicDB.eq_body_id
        ret.eq_hand_id = basicDB.eq_hand_id
        ret.eq_foot_id = basicDB.eq_foot_id
        return ret;
    },

    changeEquipment: function(part, equipID, callback){
        var basicDB = this._dbBasic;
        var equipDB = this._dbEquipment;

        var ret = {};
        // check equipID is valid
        if(undefined != equipDB[equipID]){
            if(0 == part){
                basicDB.eq_hand_id = equipID;
            }
            else if( 1 == part){ // body
                basicDB.eq_body_id = equipID;
            }
            else if( 2 == part){ // hand
                basicDB.eq_hand_id = equipID;
            }
            else if( 3 == part){ // foot
                basicDB.eq_foot_id = equipID;
            }

        }else{
            _log.d("invalid equipID, this actor don't have this quipment %d.",equipID);
        }

        callback(ret);
    }

});
