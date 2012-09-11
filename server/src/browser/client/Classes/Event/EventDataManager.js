/**
 * Created with JetBrains WebStorm.
 * User: zhuxiaozhong
 * Date: 12-9-4
 * Time: 上午11:35
 * To change this template use File | Settings | File Templates.
 */

var lc = lc = lc || {};

//事件类型 LEventType
lc.kLEventTypeGeneralBattle         =   0;          //普通战斗
lc.kLEventTypeDialogue              =   1;          //对话
lc.kLEventTypeSpecialBattle         =   2;          //特殊战斗
lc.kLEventTypeOneEventWasFinished   =   3;          //一个事件结束
lc.kLEventTypeFinishedEvent         =   4;          //事件结束了
lc.kLEventTypeNode                  =   5;          //没有事件

//战斗结果 BattleResult
lc.kBattleResultWin                 =   1;          //战斗胜利
lc.kBattleResultLost                =   0;          //战斗失败

lc.stTalk = function (){
    var obj = new Object();
    obj.id = 0;
    obj.dialogList = null;
    obj.npcId = 0;
    obj.eventId = 0;
    obj.npcName = null;

    return obj;
};

lc.randNumber = function ( begin, end )
{
    if ( begin > end )
    {
        return 0;
    }
    else
    {
        var ret1 = ( Math.random() * (end - begin) + begin ) | 0;
        return ret1;
    }
}

lc.sortTalkById = function ( value1 , value2 )
{
    if ( !value1 || !value2 )
    {
        return 0;
    }
    if ( value1.id > value2.id )
    {
        return -1;
    }
    else if ( value1.id < value2.id )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

lc.LEventData = function () {
    var obj = {};

    obj.id = 0;                                 //事件id
    obj.type = lc.kLEventTypeGeneralBattle;     //事件类型
    obj.targetId = 0;                           //目标,怪物id

    obj.bonus = null;                           //事件奖励

    obj.awardArray = null;                      //战斗奖励
    obj.batleProcess = null;                    //战斗数据
    obj.m_bBattleResultIsShowed = false;        //战斗结果是否已经显示


    obj.box_id = null;                          //宝箱id
    obj.boxAward = null;                        //宝箱开出来的奖励
    obj.m_bBoxIsOpened = false;                 //宝箱是不已经打开

    return obj;
}

lc.BattleProcess = function ()
{
    var obj = {};

    obj.m_battleResult = null;

    return obj;
}

lc.EventDataManager = cc.Class.extend({
    _mTalkMap : null,
    _mNpcMap : null,
    ctor:function () {
        this._super();
    },
    init:function () {
        this._super();
        return true;
    },
    //获取一个事件相关的所有对话
    getAllTalk : function (tEvent_Id) {
        var tRetTalk = new Array();

        for ( var i = 0; i < tRetTalk.length ; i ++ )
        {
            var tStTalk = this._mTalkMap[i];
            if ( tStTalk && tStTalk.eventId == tEvent_Id )
            {
                tRetTalk.push(tStTalk);
            }
        }
        //根据对话id的从小到大排序
        if (tRetTalk.length > 0)
        {
            tRetTalk.sort(lc.sortTalkById);
        }

        return tRetTalk;
    },
    //从获取一个对话
    getDialogFromTalk : function ( tTalk ) {
        var strDialog = null;
        if ( !tTalk || tTalk.dialogList || tTalk.dialogList.length == 0 )
        {
            strDialog = "";
        }
        else if ( tTalk.dialogList.length == 1 )
        {
            strDialog = tTalk.dialogList[0];
        }
        else{
            var pos = lc.randNumber(0,tTalk.dialogList.length);
            strDialog = tTalk.dialogList[pos];
        }
        return strDialog;
    },
    //根据id获取一个对话
    getTalk : function ( tTalk_Id ) {
        for (var i = 0; i < this._mTalkMap.length ; i++)
        {
            var tStTalk = this._mTalkMap[i];
            if ( tStTalk.id == tTalk_Id )
            {
                return tStTalk;
            }
        }
        return null;
    },
    //读取数据库
    readDB : function () {
        //
        var str = "A 1||B 2||C 3||D 4";
        var strArray = str.split("||");
    }
});

lc.fristEventDataManager = true;
lc.s_SharedEventDataManager = null;

lc.EventDataManager.getShareInstance = function (pOwner) {
    if (lc.fristEventDataManager) {
        lc.fristEventDataManager = false;
        lc.s_SharedEventDataManager = new lc.EventDataManager();
        lc.s_SharedEventDataManager.init();
    }
    return cc.s_SharedDirector;
};