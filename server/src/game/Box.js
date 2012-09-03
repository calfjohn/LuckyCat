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

//宝箱的结构
stBox = function (id, rewardMin, rewardMax, range) {
    var that = new Object();
    that.id = id;                   //宝箱id
    that.rewardMin = rewardMin;     //宝箱的开出物品至少有几个
    that.rewardMax = rewardMax;     //宝箱的开出物品至多有几个
    that.range = range;             //奖励物品的范围, 值为BoxReward中的id组成的数组

    return that;
};

//宝箱所奖励的物品
stBoxReward = function (id, rewardType, rewardId, rewardNum, probability)
{
    var that = new Object();
    that.id = id;                       //这一个奖励的id,要在stBox.range中用到
    that.rewardType = rewardType;       //奖励的类型, 金钱,经验,物品 之类的
    that.rewardId = rewardId;           //奖励的物品在设计中约定的id
    that.rewardNum = rewardNum;         //奖励的物品的数量
    that.probability = probability;     //这个奖励出现的概率, 值越小,出现的可能性越小

    return that;
};

//Box用于处理,宝箱相关的具体工作
//1. 读数据库 dict_box, dict_box_reward
//2. 取数据
//3. 开宝箱过程处理
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

        that.queryDBBox(function () {
            that.queryDBBoxReward(callback);
        });
    },
    //从数据库读取 dict_box 表, 把数据存在 _mMapBox 中
    queryDBBox:function (callback)
    {
        var that = this;
        that._dbAgent.query("SELECT * FROM `dict_box`",function (err,rows)
        {
            if (! err)
            {
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
                callback(err);
            }
        });
    },
    //从数据库中读取 dict_box_reward ,存在 _mMapBoxReward 中
    queryDBBoxReward:function (callback)
    {
        var that = this;
        that._dbAgent.query("SELECT * FROM `dict_box_reward`",function (err,rows)
        {
            if (! err)
            {
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
                callback(err);
            }
        });
    },
    // 根据宝箱id, 从 _mMapBox 中 ,获取一个stBox
    getBox:function (boxId)
    {
        if ( this._mMapBox != null )
        {
            var t = this._mMapBox[boxId];
            if ( t != null )
            {
                return t;
            }
            return null;
        }

        return null;
    },
    //根据一个奖励id, 从_mMapBoxReward中获取一个奖励stBoxReward
    getBoxRewardById:function (tRewardId)
    {
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
    //开宝箱的业务流程
    openBox:function (tBoxId)
    {
        //先获取一个宝箱
        //如果,这个宝箱不存在,直接返回,null
        var tStBox = this.getBox(tBoxId);
        if ( tStBox == null )
        {
            //the box is no exit.
            return null;
        }
        var rewardRange = new Array();  //奖励的范围,可能出现的奖励放在这个数组中
        var rewardArray = new Array();  //奖励的数组,宝箱开出来的奖励出现在这个数组中, 以上两个组组中的元素不可重复

        //获取 宝箱的奖励范围 rewardRange
        for ( var i = 0; i < tStBox.range.length; i++)
        {
            var tRId = tStBox.range[i];
            var tmp = this.getBoxRewardById(tRId);
            rewardRange.push(tmp);
        }

        var rewardCount;
        //计算要给几个奖励
        if (tStBox.rewardMax != tStBox.rewardMin)
        {
            rewardCount = parseInt((Math.random() * 100)) % (tStBox.rewardMax - tStBox.rewardMin + 1) + tStBox.rewardMin;
        }
        else
        {
            rewardCount = tStBox.rewardMin;
        }

        if (rewardCount < 0)
        {
            rewardCount = 1;
        }
        if ( rewardCount > rewardRange.length )
        {
            rewardCount = rewardRange.length();
        }
        var curRewwardCount = 0;
        //下面要在 rewardRange 中获取范围
        while ( curRewwardCount < rewardCount && rewardRange.length > 0)
        {
            //从 rewardRange 中随机获取一个奖励
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
            //刷一下是否满足概率
            //满足 把奖励放入 rewardArray表中,并从rewardRange中移除
            if (Math.random() < tReward.probability)
            {
                rewardArray.push(tReward);
                rewardRange.splice(index,1);
                curRewwardCount++;
            }
        }

        var ret = new Array();

        //最后把, rewardArray 中的物品转存一下,并返回给调用者
        for ( var i = 0; i < rewardArray.length; i++ )
        {
            var tBox = rewardArray[i];

            var obj = new Object();
            obj.id = tBox.rewardId;
            obj.type = tBox.rewardType;
            obj.count = tBox.rewardNum;

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