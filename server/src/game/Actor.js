/**
 * Actor model.
 */

require("../system/Class");
require("../system/Log");
var sysUtils = require("../system/utils");


var util = require("util");
var log = new Log("Actor.changeEquipment");
var PartType = {
    partHead:1,
    partHand:2,
    partBody:3,
    partFoot:4
};
var PartEmpty = -1;


Actor = Class.extend({
    _dbBasic:{}, // basic data from table actor
    _dbEquipment:{}, // equipment data from table actor_equipment
    _dbSkill:{},
    _tdb:{}, // actor temporary database, will not sync to database

    init:function (basicDB, equipDB, skillDB) {
        if (basicDB && equipDB) {
            this._dbBasic = basicDB;
            this._dbEquipment = equipDB;
            this._dbSkill = skillDB;
        } else {
            this.initDefaultData();
        }
    },

    initDefaultData:function () {
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
        // 计算玩家累加属性
        var eqBuff = this.calculateCapability();
        ret.attack = eqBuff.attack;
        ret.defence = eqBuff.defence;
        ret.speed = eqBuff.speed;
        ret.max_hp = eqBuff.life;

        return ret;
    },

    getAllEquipments:function () {
        var db = this._dbEquipment;
        var ret = [];
        for (var key in db) {
            var equipment = {};
            var value = db[key];
            equipment = sysUtils.clone(value);
            delete equipment["actor_id"];
            ret.push(equipment);
        }
        return ret;
    },

    getEquippedEquipment:function () {
        var basicDB = this._dbBasic;
        var equipDB = this._dbEquipment;
        var ret = {};
        var equipment = {};
        equipment.eq_head_id = basicDB.eq_head_id;
        equipment.eq_body_id = basicDB.eq_body_id;
        equipment.eq_hand_id = basicDB.eq_hand_id;
        equipment.eq_foot_id = basicDB.eq_foot_id;
        for (var key in equipment) {
            // 处理此部位无装备的情况
            if (PartEmpty == equipment[key]) {
                var value = {};
                value.id = PartEmpty
                value.equip_id = 0;
                value.level = 0;
                value.rank = 0;
                value.color = 0;
                value.item1_id = 0;
                value.item2_id = 0;
                value.item3_id = 0;
                value.item4_id = 0;
                value.item5_id = 0;
                ret[key] = value;
            } else {
                // 返回这件装备
                ret[key] = sysUtils.clone(equipDB["" + equipment[key]]);
                // 客户端不需要actor_id
                delete  (ret[key])["actor_id"];
            }
        }
        return ret;
    },

    changeEquipment:function (part, id, callback) {
        var basicDB = this._dbBasic;
        var equipDB = this._dbEquipment;
        // 计算基本属性
        var oldCapability = this.calculateCapability();

        var ret = {
            result:0,
            out:{}
        };
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
            require("./Actors").writeBackActorById(this._dbBasic.uuid, null);
            var nowCapability = this.calculateCapability();
            nowCapability.max_hp = 0;
            nowCapability.max_hp = nowCapability.life;
            delete nowCapability.life;
            ret.out.now = {};
            ret.out.now = nowCapability;

            // 计算差异
            ret.out.delta = {};
            ret.out.delta.attack = nowCapability.attack - oldCapability.attack;
            ret.out.delta.defence = nowCapability.defence - oldCapability.defence;
            ret.out.delta.max_hp = nowCapability.life - oldCapability.life;
            ret.out.delta.speed = nowCapability.speed - oldCapability.speed;
            callback(ret);
            return;
        }

        // 更换装备
        // 检查ACTOR是否拥有这件装备
        if (undefined == equipDB[id]) {
            log.d(util.format("This actor don't have this equipment!"));
            ret.result = 3;
            ret.out.msg = "This actor don't have this equipment!";
            callback(ret);
            return;
        }

        // 获得这件装备的字典表ID
        var equip_dict_id = (equipDB[id]).equip_id;

        // 取到这件装备的字典信息
        var eq = require("./DictManager").getEquipmentByID(equip_dict_id);
        if (null == eq) {
            log.d(util.format("No this equipment in dict_equipment!"));
            ret.result = 1;
            ret.out.msg = "No this equipment in dict_equipment!";
            callback(ret);
            return;
        }

        // 开始尝试更换装备
        var equipType = eq.class;
        //戴错位置了
        if (equipType != part) {
            log.d(util.format("Put equipment on wrong position!"));
            ret.result = 2;
            ret.out.msg = "Put equipment on wrong position!";
            callback(ret);
            return;
        }

        // 更换装备
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
        require("./Actors").writeBackActorById(this._dbBasic.uuid, null);
        var nowCapability = this.calculateCapability();
        nowCapability.max_hp = 0;
        nowCapability.max_hp = nowCapability.life;
        delete nowCapability.life;
        ret.out.now = {};
        ret.out.now = nowCapability;

        // 计算差异
        ret.out.delta = {};
        ret.out.delta.attack = nowCapability.attack - oldCapability.attack;
        ret.out.delta.defence = nowCapability.defence - oldCapability.defence;
        ret.out.delta.max_hp = nowCapability.life - oldCapability.life;
        ret.out.delta.speed = nowCapability.speed - oldCapability.speed;
        callback(ret);

    },

    getSkills:function () {
        return this._dbSkill;
    },

    // 计算装备基本属性
    calculateCapability:function () {
        var ret = {
            attack: 0,
            defence: 0,
            speed: 0,
            hp: 0
        };

        //玩家基本属性
        var me = this._dbBasic;
        var career = DictManager.getCareerByID(me.career_id);
        ret.attack = career.attack*Math.pow(1 + career.attack_growth, me.level);
        ret.defence = career.defence*Math.pow(1 + career.defence_growth, me.level);
        ret.hp = career.life*Math.pow(1 + career.life_growth, me.level);
        ret.speed = career.speed*Math.pow(1 + career.speed_growth, me.level);

        //装备基本属性
        var actor_equipped = this.getEquippedEquipment();
        for(var key in actor_equipped){
            var eq = actor_equipped[key];
            if(PartEmpty !=  eq.id){
                var eq_dict_info = require("./DictManager").getEquipmentByID(eq.equip_id);
                var level_growth = require("./DictManager").getEquipLevelGrowthByLevel(eq.level);
                var rank_growth = require("./DictManager").getEquipRankGrowthByRank(eq.rank);

                // calculate attk
                var atk = eq_dict_info.attack;
                ret.attack += atk * (1 + level_growth.growth);
                ret.attack += atk * (1 + rank_growth.growth);

                // calculate speed
                var speed = eq_dict_info.speed;
                ret.speed += speed * (1 + level_growth.growth);
                ret.speed += speed * (1 + rank_growth.growth);

                // calculate defence
                var defence = eq_dict_info.defence;
                ret.defence += defence * (1 + level_growth.growth);
                ret.defence += defence * (1 + rank_growth.growth);

                // calculate life
                var life = eq_dict_info.life;
                ret.hp += life * (1 + level_growth.growth);
                ret.hp += life * (1 + rank_growth.growth);

            }
        }


        // 结果只保留整数
        ret.attack = ret.attack | 0;
        ret.speed = ret.speed | 0;
        ret.defence = ret.defence | 0;
        ret.hp = ret.hp | 0;

        //技能基本属性
        return ret;
    },

    gainExp: function (exp){
        if (exp <=0) return;
        var actor  = this._dbBasic;
        actor.exp += exp;
        while(1){
            //经验不累计，到升级标准后重置
            var upgrade_table = require("./DictManager").getActorLevelUpgradeByLevel(actor.level);
            if(actor.exp < upgrade_table.xp){
                break;
            }
            // 玩家升级了
            actor.level++;
            actor.exp -= upgrade_table.xp;
        }

    },


    gainEquipment: function (equipment){
        //equipment需已设置这些字段信息 {equip_id, level, rank, color};
        equipment.actor_id = this._dbBasic.id;
        var that = this;
        require("./Actors").insertEquipmentToActor(this._dbBasic.uuid,equipment,function(result){
            equipment.id = result.insertId;
            that._dbEquipment[""+equipment.id] = equipment;
        });
    },

    /**
     * 按概率使用某个技能
     * @param acfg 概率配置表，格式，[概率，对应值]
     * example:
     * var cfg = [
     * [10, 1],
     * [20, 2],
     * [30, 3],
     * [20, 4],
     * [10, 5],
     * [10, 6]
     * ];
     * @return {Object} 某个技能
     */
    useSkill:function (acfg) {
        var ret = {};
        var cfg = [
            [10, 1],
            [20, 2],
            [30, 3],
            [20, 4],
            [10, 5],
            [10, 6]
        ];

        var skill_id = sysUtils.randomPick(cfg);
        var skill_info = require("./DictManager").getSkillByID(skill_id);
        ret.name = skill_info.name;
        ret.icon_id = skill_info.icon_id;

        return ret;
    }

});
