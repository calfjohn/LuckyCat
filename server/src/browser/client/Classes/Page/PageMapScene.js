var lc = lc = lc || {};

lc.TAG_BUTTON_BOOK = 1;
lc.TAG_BUTTON_MAGIC = 2;
lc.TAG_BUTTON_DAGGER = 3;
lc.TAG_BUTTON_OPTION = 4;

var CustomTableViewCell = cc.TableViewCell.extend({
    draw:function (ctx) {
        this._super(ctx);
    }
});

lc.PageMap = cc.Layer.extend({
    _tableView: null,
    ctor:function () {
        this._super();
    },
    init:function () {
        this._super();
        this._initTableVie();
        return true;
    },
    _initTableVie:function () {
        var winSize = cc.Director.getInstance().getWinSize();
        this._tableView = cc.TableView.create(this, cc.SizeMake(600, 130*4));
        //tableView.setAnchorpoint(cc.p(0.5,0.5));
        this._tableView.setDirection(cc.TABLEVIEW_FILL_BOTTOMUP);
        this._tableView.setVerticalFillOrder(cc.TABLEVIEW_FILL_TOPDOWN);
        this._tableView.setPosition(cc.p(75 , 275 ));
        this._tableView.setDelegate(this);
        this.addChild(this._tableView,99);
        this._tableView.reloadData();
    },
    scrollViewDidScroll:function (view) {
    },
    scrollViewDidZoom:function (view) {
    },
    tableCellTouched:function (table, cell) {
        cc.log("cell touched at index: " + cell.getIdx());
        var tPageCell = cell.getChildByTag(113);
        tPageCell.setData();
    },
    cellSizeForTable:function (table) {
        return cc.SizeMake(600, 130);
    },
    tableCellAtIndex:function (table, idx) {
        var strValue = idx.toFixed(0);
        var cell = table.dequeueCell();
        var label;
        if (!cell) {
            cell = new CustomTableViewCell();

            var tPageCell = lc.PageCellLayer.createLoader(this._tableView);
            cell.addChild(tPageCell);
            tPageCell.setTag(113);

            //tPageCell.getChildByTag(2).setString("asdfasdfasdf");
        } else {
            var tPageCell = cell.getChildByTag(113);

        }

        return cell;
    },
    numberOfCellsInTableView:function (table) {
        return 25;
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

lc.PageMapLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return lc.PageMap.create();
    }
});

lc.PageMapLoader.loader = function () {
    return new lc.PageMapLoader();
};

lc.PageMap.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary.registerCCNodeLoader("PageCellLayer", lc.PageCellLayer.loader());
    ccNodeLoaderLibrary.registerCCNodeLoader("BasicInfoLayer", lc.BasicInfoLayer.loader());
    ccNodeLoaderLibrary.registerCCNodeLoader("PageMap", lc.PageMapLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("","../Resources/ccb/pagelist.ccbi");

    return pNode;
};
lc.PageMap.create = function (pOwner) {
    var ret = new lc.PageMap();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.PageMapLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return lc.PageMap.create();
    }
});

lc.PageMapLoader.loader = function () {
    return new lc.PageMapLoader();
};

lc.PageMap.create = function ()
{
    var ret = new lc.PageMap();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.PageMap.scene = function ()
{
    var tScene = cc.Scene.create();
    var tPageMapLayer = lc.PageMap.createLoader(tScene);

    tScene.addChild(tPageMapLayer);

    return tScene;
};

lc.PageMap.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary.registerCCNodeLoader("BasicInfoLayer", lc.BasicInfoLayerLoader.loader());

    ccNodeLoaderLibrary.registerCCNodeLoader("PageCellLayer", lc.PageCellLayerLoader.loader());

    ccNodeLoaderLibrary.registerCCNodeLoader("PageMap", lc.PageMapLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("../Resources/","../Resources/ccb/pagelist.ccbi");

    return pNode;
};
