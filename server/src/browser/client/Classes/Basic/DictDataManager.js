/**
 * Created with JetBrains WebStorm.
 * User: zhuxiaozhong
 * Date: 12-9-6
 * Time: 下午4:33
 * To change this template use File | Settings | File Templates.
 */


lc.g_SharedDictDataManager = null;

lc.DictDataManager = cc.Class.extend({
    _mapMonster : [],
    _mapImage : [],
    _mapEuipment : [],
    _mapEvent : [],
    _mapNpcDialog : [],

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
        this._initNpcDialog();
    },
    getMonsterImageId:function (monsterId)
    {
        return this._mapMonster["" + monsterId];
    },
    getImage:function (imageId)
    {
        return this._mapImage["" + imageId];
    },
    getEquipment:function (equipId)
    {
        return this._mapEuipment["" + equipId];
    },
    getEvent:function (eventId)
    {
        return this._mapEvent["" + eventId];
    },
    getNpcDialog:function (dialogId)
    {
        return this._mapNpcDialog["" + dialogId];
    },
    _initMonster:function ()
    {
        this._mapMonster = JSON.parse(cc.SAXParser.shareParser().getList(s_dictMonster));
    },
    _initImage:function ()
    {
        this._mapImage = JSON.parse(cc.SAXParser.shareParser().getList(s_dictImage));
    },
    _initEquipment:function()
    {
        this._mapEuipment = JSON.parse(cc.SAXParser.shareParser().getList(s_dictEquipment));
    },
    _initEvent:function()
    {
        this._mapEvent = JSON.parse(cc.SAXParser.shareParser().getList(s_dictEvent));
    },
    _initNpcDialog:function()
    {
        this._mapNpcDialog = JSON.parse(cc.SAXParser.shareParser().getList(s_dictNpcDialog));
    }
});

lc.DictDataManager.getInstance = function () {
    if (!lc.g_SharedDictDataManager){
        lc.g_SharedDictDataManager = new lc.DictDataManager();
        lc.g_SharedDictDataManager._init();
    }
    return lc.g_SharedDictDataManager;
};