var lc = lc = lc || {};

lc.TAG_BUTTON_BOOK = 1;
lc.TAG_BUTTON_MAGIC = 2;
lc.TAG_BUTTON_DAGGER = 3;
lc.TAG_BUTTON_OPTION = 4;

lc.Page = lc.TouchLayer.extend({
    _stPage: null,
    _nChapterId: null,
    ctor:function () {
        this._super();
    },
    init:function () {
        this._super();

        return true;
    },
    setData:function (tChapterId,tPage) {
        this._stPage = tPage;
        this._nChapterId = tChapterId;

        var tlabTitle = this.getChildByTag(6);
        var tlabContent = this.getChildByTag(7);
        var tSpriteBg = this.getChildByTag(8);
        var tSpriteMonster = this.getChildByTag(91);

        tlabTitle.setString(this._stPage.name);
        tlabContent.setString(this._stPage.content);

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
    },
    notificationTouchEvent : function ( tLTouchEvent )
    {
        if (tLTouchEvent == lc.kLTouchEventSingleClick)
        {
            this.showEventList();
        }
    },
    showEventList : function ()
    {
        if ( lc.fristEventListLayer == true )
        {
            var tEventListLayer = lc.EventListLayer.getInstance();
            tEventListLayer.initLayer(this._nChapterId,this._stPage, this, this.EventListCallBack);
            this.addChild(tEventListLayer,1);
        }
        else
        {
            lc.EventListLayer.getInstance().getEventDataList();
        }
    },
    EventListCallBack : function ()
    {
        //NetManager::shareNetManager()->sendEx(kModeBattle, kDoFight1, callfuncND_selector(Page::nextPageCallback), this, "\"chapterId\": %d, \"pageId\": %d", m_nChapterId, m_pPage->id);
        this.nextPageCallback();
    },
    nextPageCallback : function ()
    {
        lc.LevelDataManager.getInstance().changePageState(this._nChapterId, this._stPage.id);

        lc.fristEventListLayer = true;

        if ( lc.LevelDataManager.getInstance().isChapterEnd(this._nChapterId) ) //已经是最后一页了
        {
            var pScene = lc.Chapter.scene();
            cc.Director.getInstance().replaceScene(pScene);
        }
        else
        {
            var pPage = lc.LevelDataManager.getInstance().getNewPage(this._nChapterId);
            var pScene = lc.Page.scene(this._nChapterId,pPage);
            cc.Director.getInstance().replaceScene(pScene);
        }
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

lc.Page.scene = function (tChapterId,tPage)
{
    var tScene = cc.Scene.create();
    var tPageLayer = lc.Page.createLoader(tScene);
    tPageLayer.setData(tChapterId,tPage);

    tScene.addChild(tPageLayer);

    return tScene;
};

lc.Page.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary.registerCCNodeLoader("BasicInfoLayer", lc.BasicInfoLayerLoader.loader());

    ccNodeLoaderLibrary.registerCCNodeLoader("PageEx", lc.PageExLoader.loader());

    ccNodeLoaderLibrary.registerCCNodeLoader("Page", lc.PageLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("../Resources/","../Resources/ccb/Page.ccbi");

    return pNode;
};