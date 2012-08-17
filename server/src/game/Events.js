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

stEvent = function (id, type, target, next_event_id, bonus, bonusRepeat,box_id) {
    var that = new Object();
    that.id = id;
    that.type = type;
    that.target = target;
    that.nextEventId = next_event_id;
    that.bonus = bonus;
    that.bonusRepeat = bonusRepeat;
    that.box_id;

    return that;
};

stGood = function ( type , id , num )
{
    var that = new Object();
    that.type = type;
    that.id = id;
    that.num = num;

    return that;
}

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
                for( var item in targetStrAry )
                {
                    var targetId = parseInt(item);
                    target.push(targetId);
                }

                var tNextEventId = tmpData.next_event_id;
                tNextEventId = parseInt(tNextEventId);
                var strBonus = tmpData.bonus;
                var intList = strBonus.split(",");
                var bonusAry = new Array();

                if ( intList.length > 0 && intList[0] != 0 )
                {
                    for ( var g = 1; g+1 < intList.length; g+=2 )
                    {
                        var goodId = intList[g];
                        var goodNum = intList[g+1];
                        var goodType = 0;

                        var tmpGood = stGood(goodType,goodId,goodNum);
                        bonusAry.push(tmpGood);
                    }
                }

                var tRepeat = tmpData.bonus_repeat;
                tRepeat = parseInt(tRepeat);
                var tBoxId = tmpData.box_id;
                tBoxId = parseInt(tBoxId);

                var tEvent = stEvent(tId,tType,target,tNextEventId,bonusAry,tBoxId);

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
        return tEventList;
    },
    getTargetByEvent :function (tEvent)
    {
        if ( tEvent )
        {
            if ( tEvent.target.length == 1 )
            {
                tEvent.target[0];
            }
        }
    }
};

module.exports = Events;