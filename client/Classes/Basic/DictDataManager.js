/**
 * Created with JetBrains WebStorm.
 * User: zhuxiaozhong
 * Date: 12-9-6
 * Time: 下午4:33
 * To change this template use File | Settings | File Templates.
 */
lc.DictDataManager = cc.Class.extend({
    _mapMonster : [],
    _mapImage : [],
    _mapEuipment : [],
    _mapEvent : [],

    //在这里初始化数据,读取数据库
    _init:function () {
        //load battle animation first

        cc.AnimationCache.purgeSharedAnimationCache();
        var cache = cc.AnimationCache.getInstance();
        cache.addAnimationsWithFile(s_plistAnimationsBomb);
        cache.addAnimationsWithFile(s_plistAnimationsDice);

        this._initMonster();
        this._initImage();
        this._initEquipment();
        this._initEvent();
    },
    getMonsterImageId:function (monsterId)
    {
        return this.mapMonster["" + monsterId];
    },
    getImage:function (imageId)
    {
        return this.mapImage["" + imageId];
    },
    getEquipment:function (equipId)
    {
        return this.mapEuipment["" + equipId];
    },
    getEvent:function (eventId)
    {
        return this.mapEvent["" + eventId];
    },
    _initMonster:function ()
    {

    },
    _initImage:function ()
    {

    },
    _initEquipment:function()
    {
        this.mapEuipment = cc.SAXParser.shareParser().getList(s_dictEquipment);
    },
    _initEvent:function()
    {
    }
});

lc.fristDictDataManager = true;
lc.s_SharedDictDataManager = null;

lc.DictDataManager.getInstance = function () {
    if (lc.fristDictDataManager) {
        lc.fristDictDataManager = false;
        lc.s_SharedDictDataManager = new lc.DictDataManager();
        lc.s_SharedDictDataManager._init();
    }
    return cc.s_SharedDictDataManager;
};