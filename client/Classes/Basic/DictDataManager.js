/**
 * Created with JetBrains WebStorm.
 * User: zhuxiaozhong
 * Date: 12-9-6
 * Time: 下午4:33
 * To change this template use File | Settings | File Templates.
 */
lc.DictDataManager = cc.Class.extend({
    m_mapMonster : [],
    m_mapImage : [],
    m_mapEuipment : [],
    m_mapEvent : [],
    //在这里初始化数据,读取数据库
    init:function () {
        //load battle animation first
        var cache = cc.AnimationCache.getInstance();
        cache.addAnimationsWithFile(s_AnimationsBomb);
        cache.addAnimationsWithFile(s_AnimationsDice);

        return true;
    },
    getMonsterImageId:function (monsterId)
    {
        var pRetValue = null;
        for (var i = 0; i < this.m_mapMonster.length; i++)
        {
            var tMonster = this.m_mapMonster[i];
            if (tMonster.id == monsterId)
            {
                pRetValue = tMonster;
                break;
            }
        }

        return pRetValue;
    },
    getImage:function (imageId)
    {
        var pRetValue = null;
        for (var i = 0; i < this.m_mapImage.length; i++)
        {
            var tImage = this.m_mapImage[i];
            if (tImage.id == imageId)
            {
                pRetValue = tImage;
                break;
            }
        }

        return pRetValue;
    },
    getEquipment:function (equipId)
    {
        var pRetValue = null;
        for (var i = 0; i < this.m_mapEuipment.length; i++)
        {
            var tEquip = this.m_mapEuipment[i];
            if (tEquip.equipId == equipId)
            {
                pRetValue = tEquip;
                break;
            }
        }

        return pRetValue;
    },
    getEvent:function (eventId)
    {
        var pRetValue = null;
        for (var i = 0; i < this.m_mapEvent.length; i++)
        {
            var tmp = this.m_mapEvent[i];
            if (tmp.id == eventId)
            {
                pRetValue = tmp;
                break;
            }
        }

        return pRetValue;
    },
    initMonster:function ()
    {

    },
    initImage:function ()
    {

    },
    initEquipment:function()
    {

    },
    initEvent:function()
    {

    }
});

lc.fristDictDataManager = true;
lc.s_SharedDictDataManager = null;

lc.DictDataManager.shareLevelDataManager = function () {
    if (lc.fristDictDataManager) {
        lc.fristDictDataManager = false;
        lc.s_SharedDictDataManager = new lc.DictDataManager();
        lc.s_SharedDictDataManager.init();
    }
    return cc.s_SharedDictDataManager;
};