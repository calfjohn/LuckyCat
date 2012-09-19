var lc = lc = lc || {};

lc.PageEx = cc.Layer.extend({});

lc.PageExLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return lc.PageEx.create();
    }
});

lc.PageExLoader.loader = function () {
    return new lc.PageExLoader();
};

lc.PageEx.create = function ()
{
    var ret = new lc.PageEx();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.PageEx.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary.registerCCNodeLoader("PageEx", lc.PageExLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("../Resources/","/ccb/fuzzy.ccbi");

    return pNode;
};
