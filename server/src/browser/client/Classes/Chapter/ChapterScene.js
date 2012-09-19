var lc = lc = lc || {};

lc.TAG_BUTTON_BOOK = 1;
lc.TAG_BUTTON_MAGIC = 2;
lc.TAG_BUTTON_DAGGER = 3;
lc.TAG_BUTTON_OPTION = 4;

lc.Chapter = cc.Layer.extend({
    _m_nbibleId : 0,
    ctor:function () {
        this._super();
    },
    init:function () {
        this._super();

        return true;
    },
    initData:function (tBibleId)
    {
        this._m_nbibleId = tBibleId;

        var tBible = lc.LevelDataManager.getInstance().getBible();

    },
    onResolveCCBCCMenuItemSelector:function ( pTarget, pSelectorName)
    {
        if (pSelectorName == "onMenuItemClicked")
        {
            return this.onMenuItemClicked;
        }
        return null;
    },
    onResolveCCBCCControlSelector:function( pTarget, pSelectorName)
    {
        if (pSelectorName == "onCCControlButtonClicked")
        {
            return this.onCCControlButtonClicked;
        }
        return null;
    },
    onAssignCCBMemberVariable:function(pTarget, pMemberVariableName, pNode)
    {
        return false;
    },
    onMenuItemClicked:function(pTarget)
    {
        cc.log("tag " + pTarget.getTag());

        var tChapterId = pTarget.getTag();
        var pScene = lc.PageMap.scene(tChapterId);

        cc.Director.getInstance().replaceScene(pScene);
    },
    onCCControlButtonClicked:function(pSender, pCCControlEvent)
    {
        cc.log("tag " + pSender.getTag());
    },
    registerWithTouchDispatcher:function()
    {
        cc.Director.getInstance().getTouchDispatcher().addTargetedDelegate(this,0 , false);
    }
});

lc.ChapterLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return lc.Chapter.create();
    }
});

lc.ChapterLoader.loader = function () {
    return new lc.ChapterLoader();
};

lc.Chapter.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary.registerCCNodeLoader("Chapter", lc.ChapterLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("",s_ccbiOpenBox);

    return pNode;
};
lc.Chapter.create = function (pOwner) {
    var ret = new lc.Chapter();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.ChapterLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return lc.Chapter.create();
    }
});

lc.ChapterLoader.loader = function () {
    return new lc.ChapterLoader();
};

lc.Chapter.create = function ()
{
    var ret = new lc.Chapter();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.Chapter.scene = function ()
{
    var tScene = cc.Scene.create();
    var tChapterLayer = lc.Chapter.createLoader(tScene);

    tScene.addChild(tChapterLayer);

    return tScene;
};

lc.Chapter.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary.registerCCNodeLoader("BasicInfoLayer", lc.BasicInfoLayerLoader.loader());

    ccNodeLoaderLibrary.registerCCNodeLoader("Chapter", lc.ChapterLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("../Resources/","../Resources/ccb/chapter.ccbi");

    return pNode;
};