var lc = lc = lc || {};

lc.TAG_BUTTON_BOOK = 1;
lc.TAG_BUTTON_MAGIC = 2;
lc.TAG_BUTTON_DAGGER = 3;
lc.TAG_BUTTON_OPTION = 4;

lc.Page = cc.Layer.extend({
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
    },
    registerWithTouchDispatcher:function()
    {
        cc.Director.getInstance().getTouchDispatcher().addTargetedDelegate(this,0 , false);
    }
});

lc.PageLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return lc.Page.create();
    }
});

lc.PageLoader.loader = function () {
    return new lc.PageLoader();
};

lc.Page.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary.registerCCNodeLoader("Page", lc.PageLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("","../Resources/ccb/page.ccbi");

    return pNode;
};
lc.Page.create = function (pOwner) {
    var ret = new lc.Page();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.PageLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return lc.Page.create();
    }
});

lc.PageLoader.loader = function () {
    return new lc.PageLoader();
};

lc.Page.create = function ()
{
    var ret = new lc.Page();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.Page.scene = function ()
{
    var tScene = cc.Scene.create();
    var tPageLayer = lc.Page.createLoader(tScene);

    tScene.addChild(tPageLayer);

    return tScene;
};

lc.Page.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary.registerCCNodeLoader("BasicInfoLayer", lc.BasicInfoLayerLoader.loader());

    ccNodeLoaderLibrary.registerCCNodeLoader("Page", lc.PageLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("../Resources/","../Resources/ccb/Page.ccbi");

    return pNode;
};