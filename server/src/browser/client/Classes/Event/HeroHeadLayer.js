var lc = lc = lc || {};

lc.HeroHeadLayer = cc.Layer.extend({
    ctor:function () {
        this._super();
    },
    init:function () {
        var size = cc.Director.getInstance().getWinSize();
        var helloLabel = cc.LabelTTF.create("Hero Head Layer", "Arial", 22);
        helloLabel.setColor(cc.red());
        helloLabel.setPosition(cc.p(size.width / 2, size.height /2));
        this.addChild(helloLabel, 9);

        return true;
    },
    onMenuItemClicked : function (pTarget)
    {
        cc.log("onMenuItemClicked " + pTarget.getTag());
        if(pTarget.getTag() == 1){
//            var pNode = this.getChildByTag(TAG_PLAYER_INFO);
//            if (!pNode)
//            {
//                var pInfo = lc.PlayerInfoLayer.create(this);
//                this.addChild(pInfo);
//                pInfo.setTag(TAG_PLAYER_INFO);
//            }
//            else {
//                pNode.removeFromParentAndCleanup(true);
//            }
        }
    },
    onResolveCCBCCMenuItemSelector:function ( pTarget, pSelectorName)
    {
        if (pSelectorName == "onMenuItemClicked")
        {
            return this.onMenuItemClicked;
        }
        return null;
    }
});

lc.HeroHeadLayer.create = function (pOwner) {
    var ret = new lc.HeroHeadLayer();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.HeroHeadLayerLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return lc.HeroHeadLayer.create();
    }
});

lc.HeroHeadLayerLoader.loader = function () {
    return new lc.HeroHeadLayerLoader();
};

lc.HeroHeadLayer.create = function ()
{
    var ret = new lc.HeroHeadLayer();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.HeroHeadLayer.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary.registerCCNodeLoader("HeroHeadLayer", lc.HeroHeadLayerLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("../Resources/",s_ccbiHeroHead);

    return pNode;
};