/**
 * Created with JetBrains WebStorm.
 * User: zhuxiaozhong
 * Date: 12-8-13
 * Time: 下午5:08
 * To change this template use File | Settings | File Templates.
 */
if (global.Box) {
    module.exports = Box;
    return;
}
require("../system/DBAgent");
require("../system/Log");

require("../system/Class");

stBox = function (id, rewardMin, rewardMax, range) {
    var that = new Object();
    that.id = id;
    that.rewardMin = rewardMin;
    that.rewardMax = rewardMax;
    that.range = range;

    return that;
};

stBoxReward = function (id, rewardType, rewardId, rewardNum, probability)
{
    var that = new Object();
    that.id = id;
    that.rewardType = rewardType;
    that.rewardId = rewardId;
    that.rewardNum = rewardNum;
    that.probability = probability;

    return that;
};

Box = {
    _dbAgent : null,
    _mMapBox : null,
    _mMapBoxReward : null,
    ctor:function () {

    },
    init: function () {

    },
    initInstance : function(dbConfig, callback) {
        var that = this;
        that._dbAgent = new DBAgent(dbConfig);
        that._dbAgent.connect(true);

        that.queryDBBox(callback);
        that.queryDBBoxReward(callback);
    },
    queryDBBox:function (callback)
    {
        var that = this;
        that._dbAgent.query("SELECT * FROM `dict_box`",function (err,rows)
        {
            if (err)
            {
                throw err;
                return;
            }

            if ( that._mMapBox )
            {
                that._mMapBox.length = 0;
            }
            else
            {
                that._mMapBox = new Array();
            }

            for ( var i = 0; i < rows.length; i++)
            {
                var tmpData = rows[i];

                var tBoxId = tmpData.id;
                tBoxId = parseInt(tBoxId);
                var tMin = tmpData.reward_min;
                tMin = parseInt(tMin);
                var tMax = tmpData.reward_max;
                tMax = parseInt(tMax);
                var tStrRange = tmpData.range;
                var tStrArray = tStrRange.split(",");

                var tRange = new Array();
                for (var j = 0; j < tStrArray.length; j++)
                {
                    var t = tStrArray[j];
                    t = parseInt(t);
                    tRange.push(t);
                }

                var tmpBox = stBox(tBoxId,tMin,tMax,tRange);

                //that._mMapBox.push(tmpBox);
                that._mMapBox[tBoxId] = tmpBox;
            }
            process.nextTick(function() {
                callback(null);
            });
        });
    },
    queryDBBoxReward:function (callback)
    {
        var that = this;
        that._dbAgent.query("SELECT * FROM `dict_box_reward`",function (err,rows)
        {
            if (err)
            {
                throw err;
                return;
            }
            if ( that._mMapBoxReward )
            {
                that._mMapBoxReward.length = 0;
            }
            else
            {
                that._mMapBoxReward = new Array();
            }


            for ( var i = 0; i < rows.length; i++)
            {
                var tmpData = rows[i];

                var tId = tmpData.id;
                tId = parseInt(tId);
                var tType = tmpData.reward_type;
                tType = parseInt(tType);
                var tRewardId = tmpData.reward_id;
                tId = parseInt(tId);
                var tNum = tmpData.reward_num;
                tNum = parseInt(tNum);
                var tProbability = tmpData.probability;
                tProbability = parseFloat(tProbability);

                var tmpBoxReward = stBoxReward(tId,tType,tRewardId,tNum,tProbability);

                //that._mMapBoxReward.push(tmpBoxReward);
                that._mMapBoxReward[tId] = tmpBoxReward;
            }
            process.nextTick(function() {
                callback(null);
            });
        });
    },
    getBox:function (boxId)
    {
        if ( this._mMapBox != null )
        {
            /*
            for ( var i = 0; i < this._mMapBox.length ; i++ )
            {
                var tmp = this._mMapBox[i];
                if ( tmp && tmp.id == boxId )
                {
                    return tmp;
                }
            }
             */
            var t = this._mMapBox[boxId];
            if ( t != null )
            {
                return t;
            }
            return null;
        }

        return null;
    },
    getBoxRewardById:function (tRewardId)
    {
        /*
        for ( var i = 0; i < this._mMapBoxReward.length; i++ )
        {
            var tmp = this._mMapBoxReward[i];
            if ( tmp && tmp.id == tRewardId )
            {
                return tmp;
            }
        }
        return null;
        */
        if ( this._mMapBoxReward != null )
        {
            var t = this._mMapBoxReward[tRewardId];
            if ( t != null )
            {
                return t;
            }
            return null;
        }
        else return null;
    },
    openBox:function (tBoxId)
    {
        var tStBox = this.getBox(tBoxId);
        var rewardRange = new Array();
        var rewardArray = new Array();

        if ( tStBox == null )return;

        for ( var i = 0; i < tStBox.range.length; i++)
        {
            var tRId = tStBox.range[i];
            var tmp = this.getBoxRewardById(tRId);
            rewardRange.push(tmp);
        }

        var rewardCount = Math.round(tStBox.rewardMax - tStBox.rewardMin);
        if (rewardCount < 0)
        {
            rewardCount = 1;
        }
        if ( rewardCount > rewardRange.length )
        {
            rewardCount = rewardRange.length();
        }
        var curRewwardCount = 0;
        while ( curRewwardCount < rewardCount && rewardRange.length > 0)
        {
            var index = (Math.random() * 100) % (rewardRange.length) | 0;

            if (index >= rewardRange.length)
            {
                index = rewardRange.length -1;
            }
            if (index < 0)
            {
                index = 0;
            }

            var tReward = rewardRange[index];
            if (Math.random() > tReward.probability)
            {
                rewardArray.push(tReward);
                rewardRange.slice(index,1);
                curRewwardCount++;
            }
        }

        var ret = new Array();

        for ( var i = 0; i < rewardArray.length; i++ )
        {
            var tBox = rewardArray[i];

            var obj = new Object();
            obj.id = tBox.rewardId;
            obj.type = tBox.rewardType;
            obj.num = tBox.rewardNum;

            ret.push(obj);
        }

        return ret;
    },
    readBoxDB : function (callback) {
        var that = this;

        that.queryDBBox(callback);
        that.queryDBBoxReward(callback);
    }
};

module.exports = Box;