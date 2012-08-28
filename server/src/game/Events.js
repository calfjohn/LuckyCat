/**
 * Created with JetBrains WebStorm.
 * User: zhuxiaozhong
 * Date: 12-8-13
 * Time: 下午5:08
 * To change this template use File | Settings | File Templates.
 */
if (global.Events) {
    module.exports = Events;
    return;
}
require("../system/DBAgent");
require("../system/Log");

require("../system/Class");

clone = function (obj) {
    var newObj = (obj instanceof Array) ? [] : {};
    for (var key in obj) {
        var copy = obj[key];
        if (copy instanceof Array) {
            newObj[key] = arguments.callee(copy);
        } else if ((typeof copy) == "object")  {
            newObj[key] = arguments.callee(copy);
        } else {
            newObj[key] = copy;
        }
    }
    return newObj;
};

stEvent = Class.extend({
    id : null,
    type : null,
    targetArray : null,
    nextEventId : null,
    bonusArray : null,
    bonusRepeat : null,
    box_id : null,
    curTarget : null,
    ctor : function ()
    {

    },
    init : function ()
    {

    },
    setData : function (id, type, target, next_event_id, bonus, bonusRepeat,box_id) {
        this.id = id;
        this.type = type;
        this.targetArray = target;
        this.nextEventId = next_event_id;
        this.bonusArray = bonus;
        this.bonusRepeat = bonusRepeat;
        this.box_id = box_id;
    },
    randomTarget : function ()
    {
        if ( this.targetArray )
        {
            if ( this.targetArray.length > 0 )
            {
                var index = parseInt((Math.random() * 100)) % (this.targetArray.length);
                if (index >= 0 && index < this.targetArray.length)
                {
                    this.curTarget = this.targetArray[index];
                    return;
                }
            }
        }
        curTarget = null;
    },
    getTarget : function ()
    {
        return this.curTarget;
    },
    getBonus : function ()
    {
        return this.bonusArray;
    }
});

stGood = Class.extend({
    id : null,
    type : null,
    num : null,
    ctor : function ()
    {

    },
    init : function ()
    {

    },
    setData : function ( type , id , num )
    {
        this.type = type;
        this.id = id;
        this.num = num;
    }
});

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

                var tBoxId = tmpData.id;
                tBoxId = parseInt(tBoxId);

                var tId = tmpData.id;
                tId = parseInt(tId);
                var tType = tmpData.type;
                tType = parseInt(tType);
                var strTarget = tmpData.target;
                var targetStrAry = strTarget.split(",");
                var target = new Array();
                for (var ti = 0; ti < targetStrAry.length; ti++)
                {
                    var item = targetStrAry[ti];
                    var targetId = parseInt(item);
                    target.push(targetId);
                }

                var tNextEventId = tmpData.next_event_id;
                tNextEventId = parseInt(tNextEventId);
                var strBonus = tmpData.bonus;
                var intList = strBonus.split(",");
                var bonusAry = new Array();
                var tBonus_repeat = tmpData.bonus_repeat;
                tBonus_repeat = parseInt(tBonus_repeat);

                if ( intList.length > 0 && intList[0] != 0 )
                {
                    for ( var g = 1; g+1 < intList.length; g+=2 )
                    {
                        var goodId = parseInt(intList[g]);
                        var goodNum = parseInt(intList[g+1]);
                        var goodType = parseInt(3);

                        var tmpGood = new stGood();
                        tmpGood.setData(goodType,goodId,goodNum);

                        bonusAry.push(tmpGood);
                    }
                }

                var tRepeat = tmpData.bonus_repeat;
                tRepeat = parseInt(tRepeat);
                var tBoxId = tmpData.box_id;
                tBoxId = parseInt(tBoxId);

                var tEvent = new stEvent();

                tEvent.id = tId;
                tEvent.type = tType;
                tEvent.targetArray = target;
                tEvent.nextEventId = tNextEventId;
                tEvent.bonusArray = bonusAry;
                tEvent.box_id = tBoxId;
                tEvent.bonusRepeat = tBonus_repeat;

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
    getASeriesOfEvent : function (eventId)
    {
        var tEventId = eventId;
        var tEventList = new Array();

        while ( tEventId != -1 )
        {
            var tEvent = this.getEvent(tEventId);
            if ( tEvent )
            {
                tEventList.push(tEvent);
                tEventId = tEvent.nextEventId;
            }
        }
        if (tEventList.length != 0)return tEventList;

        return null;

    },
    getEventList : function (eventId)
    {
        var tEventId = eventId;
        var tEventList = new Array();

        while ( tEventId != -1 )
        {
            var tmpEvent = this.getEvent(tEventId);
            var tEvent = clone(tmpEvent);
            if ( tEvent )
            {
                if (tEvent.type != 1)
                {
                    var monster = require("./DictManager").getMonsterById(tEvent.targetArray[0]);
                    if (monster)
                    {
                        var exp = ((60+monster.level*5)*monster.rank) | 0;
                        var money = ((100+monster.level*6)*monster.rank) | 0;
                        tEvent.Exp = exp;
                        tEvent.Money = money;
                        var oExp = {};
                        oExp.type = 1;
                        oExp.id = 2;//exp
                        oExp.num = exp;

                        var oMoney = {};
                        oMoney.type = 2;
                        oMoney.id = 1;
                        oMoney.num = money;

                        tEvent.bonusArray.push(oMoney);
                        tEvent.bonusArray.push(oExp);

                        tEvent.bonusArray.reverse();
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
        if (tEventList.length != 0)return tEventList;

        return null;

    }
};

module.exports = Events;