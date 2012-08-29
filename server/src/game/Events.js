/**
 * Created with JetBrains WebStorm.
 * User: zhuxiaozhong
 * Date: 12-8-13
 * Time: 下午5:08
 * To change this template use File | Settings | File Templates.
 */
(function(){
    if (global.Events) {
    module.exports = Events;
    return;
}
require("../system/DBAgent");
require("../system/Log");
require("../system/Class");

Events = {
    _dbAgent : null,
    _mMapEvent : null,
    ctor:function () {

    },
    init: function () {

    },
    initInstance : function(dbConfig, callback) {
        var that = this;
        that._dbAgent = new DBAgent(dbConfig);
        that._dbAgent.connect(true);

        that.queryDBEvent(callback);
    },
    queryDBEvent:function (callback)
    {
        var that = this;
        that._dbAgent.query("SELECT * FROM `dict_event`",function (err,rows)
        {
            if (err)
            {
                throw err;
                return;
            }

            if ( that._mMapEvent )
            {
                that._mMapEvent.length = 0;
            }
            else
            {
                that._mMapEvent = new Array();
            }

            for ( var i = 0; i < rows.length; i++)
            {
                var tmpData = rows[i];
                var tEvent = {};

                tEvent.id = rows[i].id;
                tEvent.type = rows[i].type;
                tEvent.target = rows[i].target;
                tEvent.nextEventId = rows[i].next_event_id;
                tEvent.bonus = JSON.parse(rows[i].bonus);
                tEvent.box_id = rows[i].box_id;
                tEvent.bonusRepeat = rows[i].bonus_repeat;
                tEvent.awardArray = [];

                that._mMapEvent[tEvent.id] = tEvent;
            }
            process.nextTick(function() {
                callback(null);
            });
        });
    },
    getEvent : function (eventId)
    {
        var tEvent = this._mMapEvent[eventId];
        if ( tEvent != null )
        {
            return tEvent;
        }
        return null;
    },
    processBonusArray: function(bonus, uuid)
    {
        if(!bonus)
        {
            return;
        }

        for(var i = 0; i < bonus.length; i++)
        {
            switch (bonus[i].type)
            {
                case 1://金钱，待开发
                    break;
                case 2://经验
                    require("./Actors").getActor(uuid).gainExp(bonus[i].count);
                    break;
                case 3://物品，待开发
                    break;
                case 4://装备
                    //equipment需已包含 {equip_id:'2001', level:'1', rank:'1', color:'1'};
                    var equipment = {};
                    equipment.equip_id = bonus[i].id;
                    equipment.level = '1';
                    equipment.color = '1';
                    equipment.rank = '1';
                    for(var j = 0; j < bonus[i].count; j++)
                    {
                        require("./Actors").getActor(uuid).gainEquipment(equipment);
                    }
                    break;
            }
        }
    },
    getEventList : function (eventId, uuid)
    {
        var tEventId = eventId;
        var tEventList = new Array();

        while ( tEventId != -1 )
        {
            var tEvent = [];//待扩展为一系列事件，暂时只有一个事件
            tEvent = this.getEvent(tEventId);
            if ( tEvent )
            {
                if (tEvent.type != 1)
                {
                    //获取奖励，与怪物等级相关
                    var monster = require("./DictManager").getMonsterById(tEvent.target);
                    if (monster)
                    {
                        var exp = ((60+monster.level*5)*monster.rank) | 0;
                        var money = ((100+monster.level*6)*monster.rank) | 0;

                        var oExp = {};
                        oExp.type = 2;
                        oExp.id = -1;
                        oExp.count = exp;
                        tEvent.awardArray.push(oExp);

                        var oMoney = {};
                        oMoney.type = 1;
                        oMoney.id = -1;
                        oMoney.count = money;
                        tEvent.awardArray.push(oMoney);
                    }
                }
                if ( tEvent.box_id != -1 )
                {
                    var ary = require("./Box").openBox(tEvent.box_id);
                    tEvent.boxAward = ary;
                }
                else
                {
                    tEvent.boxAward = null;
                }

                tEventList.push(tEvent);
                tEventId = tEvent.nextEventId;
            }
        }
        if (tEventList.length != 0) {
            //处理所有奖励，包括战斗、箱子、事件
            for(var i = 0; i < tEventList.length; i++)
            {
                Events.processBonusArray(tEventList[i].awardArray, uuid);
                Events.processBonusArray(tEventList[i].boxAward, uuid);
                Events.processBonusArray(tEventList[i].bonus, uuid);
            }

            return tEventList;
        }

        return null;
    }
};

module.exports = Events;
})();
