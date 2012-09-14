var lc = lc = lc || {};

lc.BasicInfoLayer = cc.Layer.extend({});

lc.BasicInfoLayerLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return lc.BasicInfoLayer.create();
    }
});

lc.BasicInfoLayerLoader.loader = function () {
    return new lc.BasicInfoLayerLoader();
};

lc.BasicInfoLayer.create = function ()
{
    var ret = new lc.BasicInfoLayer();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.BasicInfoLayer.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary.registerCCNodeLoader("BasicInfoLayer", lc.BasicInfoLayerLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("../Resources/","/ccb/basic.ccbi");

    return pNode;
};
