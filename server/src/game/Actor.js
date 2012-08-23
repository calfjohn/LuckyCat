/**
 * Actor model.
 */

require("../system/Class");
require("../system/Log");

var util = require("util");
var log = new Log("Actor.changeEquipment");
var PartType = {
    partHead : 1,
    partBody : 2,
    partHand : 3,
    partFoot : 4
};
var PartEmpty = -1;


Actor = Class.extend({
    _dbBasic: {},                // basic data from table actor
    _dbEquipment: {},           // equipment data from table actor_equipment
    _dbSkill: {},
    _tdb: {},               // actor temporary database, will not sync to database

    init: function(basicDB, equipDB, skillDB) {
        if (basicDB && equipDB) {
            this._dbBasic = basicDB;
            this._dbEquipment = equipDB;
            this._dbSkill = skillDB;
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
            equipment.id = value.id;
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
        ret.eq_head_id = basicDB.eq_head_id;
        ret.eq_body_id = basicDB.eq_body_id;
        ret.eq_hand_id = basicDB.eq_hand_id;
        ret.eq_foot_id = basicDB.eq_foot_id;
        return ret;
    },

    changeEquipment: function(part, id, callback){
        var basicDB = this._dbBasic;
        var equipDB = this._dbEquipment;

        var ret = {
            result: 0,
            out: {}
        };
        do {
            //卸下装备
            if (PartEmpty == id) {
                if (PartType.partHead == part) {
                    basicDB.eq_head_id = PartEmpty;
                }
                else if (PartType.partBody == part) { // body
                    basicDB.eq_body_id = PartEmpty;
                }
                else if (PartType.partHand == part) { // hand
                    basicDB.eq_hand_id = PartEmpty;
                }
                else if (PartType.partFoot == part) { // foot
                    basicDB.eq_foot_id = PartEmpty;
                }
                break;
            }

            // 更换装备
            // check equipID is valid
            require("./DictManager").getEquipmentByID(id, function (eq) {
                var equipType = eq.class;
                if ((equipType == part) && (undefined != equipDB[id])) {
                    if (PartType.partHead == part) {
                        basicDB.eq_head_id = id;
                    }
                    else if (PartType.partBody == part) { // body
                        basicDB.eq_body_id = id;
                    }
                    else if (PartType.partHand == part) { // hand
                        basicDB.eq_hand_id = id;
                    }
                    else if (PartType.partFoot == part) { // foot
                        basicDB.eq_foot_id = id;
                    }
                } else {
                    ret.result = 1;
                    ret.out.msg = "invalid equipID, this actor don't have this quipment";
                    log.d(util.format("invalid equipID, this actor don't have this quipment %d.", equipID));
                }

            });
        } while (0);
        callback(ret);
    },

    getSkills: function(){
        return this._dbSkill;
    }

});
