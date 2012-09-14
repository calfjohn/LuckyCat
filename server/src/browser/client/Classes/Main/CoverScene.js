var lc = lc = lc || {};

lc.TAG_BUTTON_BOOK = 1;
lc.TAG_BUTTON_MAGIC = 2;
lc.TAG_BUTTON_DAGGER = 3;
lc.TAG_BUTTON_OPTION = 4;

lc.Cover = cc.Layer.extend({
    ctor:function () {
        this._super();
    },
    init:function () {
        this._super();

        return true;
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
    },
    onCCControlButtonClicked:function(pSender, pCCControlEvent)
    {
        cc.log("tag " + pSender.getTag());

        switch (pSender.getTag())
        {
            case lc.TAG_BUTTON_BOOK:
                this.menuBookCallback(pSender);
                break;
            case lc.TAG_BUTTON_MAGIC:
                this.menuMagicCallback(pSender);
                break;
            case lc.TAG_BUTTON_DAGGER:{
                //menuDaggerCallback(pSender);
//                PKListView *pkView = PKListView::create(this);
//                this->addChild(pkView,99);
            }
                break;
            case lc.TAG_BUTTON_OPTION:
                this.menuOptionCallback(pSender);
                break;
            default:
                break;
        }
    },
    registerWithTouchDispatcher:function()
    {
        cc.Director.getInstance().getTouchDispatcher().addTargetedDelegate(this,0 , false);
    },
    menuDaggerCallback:function(pSender)
    {

    },
    menuMagicCallback:function(pSender)
    {
    },
    menuBookCallback:function(pSender)
    {
        //NetManager::shareNetManager()->setToken("3");

        var pScene = lc.Chapter.scene();

        //CCTransitionPageTurn *pTp = CCTransitionPageTurn::create(TRANSITION_PAGE_INTERVAL_TIME, pScene, false);

        cc.Director.getInstance().replaceScene(pScene);
    },
    menuCardCallback:function(pSender)
    {

    },
    menuOptionCallback:function(pSender)
    {

    }
});

lc.CoverLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return lc.Cover.create();
    }
});

lc.CoverLoader.loader = function () {
    return new lc.CoverLoader();
};

lc.Cover.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary.registerCCNodeLoader("Cover", lc.CoverLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("",s_ccbiOpenBox);

    return pNode;
};
lc.Cover.create = function (pOwner) {
    var ret = new lc.Cover();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.CoverLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return lc.Cover.create();
    }
});

lc.CoverLoader.loader = function () {
    return new lc.CoverLoader();
};

lc.Cover.create = function ()
{
    var ret = new lc.Cover();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.Cover.scene = function ()
{
    var tScene = cc.Scene.create();
    var tCoverLayer = lc.Cover.createLoader(tScene);

    tScene.addChild(tCoverLayer);

    return tScene;
};

lc.Cover.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    //ccNodeLoaderLibrary.registerCCNodeLoader("FuzzyBgLayer", lc.FuzzyBgLayerLoader.loader());

    ccNodeLoaderLibrary.registerCCNodeLoader("Cover", lc.CoverLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("../Resources/","../Resources/ccb/desk.ccbi");

    return pNode;
};