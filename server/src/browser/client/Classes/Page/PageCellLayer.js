var lc = lc = lc || {};

lc.TAG_BUTTON_BOOK = 1;
lc.TAG_BUTTON_MAGIC = 2;
lc.TAG_BUTTON_DAGGER = 3;
lc.TAG_BUTTON_OPTION = 4;

lc.PageCellLayer = cc.Layer.extend({
    _stPage: null,
    _nChapterId: 0,
    ctor:function () {
        this._super();
    },
    init:function () {
        this._super();
        return true;
    },
    setData:function(tChapterId,tPage)
    {
        this._nChapterId = tChapterId;
        this._stPage = tPage;

        var num = lc.randNumber(1,5);
        var str = "../Resources/image/scene/scene_100" + num + ".png";

        var lab = this.getChildByTag(2);
        lab.setString(tPage.name);

        var sprite = this.getChildByTag(1);
        var spriteFrame = cc.TextureCache.getInstance().addImage(str);
        sprite.setTexture(spriteFrame);

//    var spriteFrame = cc.SpriteFrameCache.getInstance().getSpriteFrame(str);
//    sprite.setDisplayFrame(spriteFrame);
    },
    showPage:function ()
    {
        var tPage = lc.Page.scene(this._nChapterId,this._stPage);
        cc.Director.getInstance().replaceScene(tPage);
    }
//    ,
//    draw:function (ctx) {
//        this._super(ctx);
//    }
});

lc.PageCellLayerLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return lc.PageCellLayer.create();
    }
});

lc.PageCellLayerLoader.loader = function () {
    return new lc.PageCellLayerLoader();
};

lc.PageCellLayer.create = function ()
{
    var ret = new lc.PageCellLayer();
    if (ret && ret.init()) {
        //ret.getChildByTag(2).setString("tableCellAtIndex");
        return ret;
    }
    return null;
};

lc.PageCellLayer.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary.registerCCNodeLoader("PageCellLayer", lc.PageCellLayerLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("../Resources/","../Resources/ccb/pagelist_scroll.ccbi");

    return pNode;
};
