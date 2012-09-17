
var lc = lc = lc || {};

lc.TAG_DIALOG_MONSTER       =   91;
lc.TAG_DIALOG_NPC_NAME      =   10;
lc.TAG_DIALOG_NPC_DIALOG    =   11;

lc.NPCDialogLayer = lc.TouchLayer.extend({
    mLabelNpcName : null,
    mLabelDialogContent : null,
    mSpriteNpc : null,
    p_CurEvent : null,
    mTalkList : [],
    m_target : null,         //callback listener
    m_pfnSelector : null,    //callback selector
    ctor:function () {
        this._super();
    },
    init:function () {
        this._super();
        return true;
    },
    onMenuItemClicked : function ( pTarget )
    {

    },
    onCCControlButtonClicked : function ( pSender, pCCControlEvent)
    {
    },
    notificationTouchEvent : function ( tLTouchEvent )
    {
        if (tLTouchEvent == lc.kLTouchEventSingleClick)
        {
            this.getNextTalk();

            this.showDialog();
        }
    },
    setDialogByStTalk : function ( tTalk )
    {
        var dialog = lc.EventDataManager.getInstance().getDialogFromTalk(tTalk);
        this.mLabelNpcName.setString(tTalk.npcName);
        this.mLabelDialogContent.setString(dialog);
    },
    setData : function ( tEvent, target, pfnSelector)
    {
        this.p_CurEvent = tEvent;
        this.m_target = target;
        this.m_pfnSelector = pfnSelector;

        this.mLabelNpcName = this.getChildByTag(lc.TAG_DIALOG_NPC_NAME);
        this.mLabelDialogContent = this.getChildByTag(lc.TAG_DIALOG_NPC_DIALOG);
        this.mSpriteNpc = this.getChildByTag(lc.TAG_DIALOG_MONSTER);

        this.mTalkList.length = 0;

        //this.mTalkList = lc.EventDataManager.getInstance().getAllTalk(5);//getAllTalk(this.p_CurEvent.id);
        this.mTalkList = lc.EventDataManager.getInstance().getAllTalk(5);

//        LuckySprite *pSpriteMonster = static_cast<LuckySprite *>(this->getChildByTag(TAG_MONSTER));
//        if (pSpriteMonster)
//        {
//            const stMonster * pMonster = DictDataManager::shareDictDataManager()->getMonsterImageId(p_CurEvent->targetId);
//            pSpriteMonster->setNewTexture(pMonster->imageId);
//        }

        this.showDialog();
    },
    getCurTalk : function ()
    {
        var ret = null;
        if ( this.mTalkList.length > 0 )
        {
            ret =  this.mTalkList[0];
        }
        return ret;
    },
    getNextTalk : function ()
    {
        var ret = null;
        if ( this.mTalkList.length > 0 )
        {
            this.mTalkList.splice(0,1);
            if ( this.mTalkList.length > 0 )
            {
                ret = this.mTalkList[0];
            }
        }
        return ret;
    },
    showDialog : function ()
    {
        var tTalk = this.getCurTalk();

        if (tTalk)
        {
            this.setDialogByStTalk(tTalk);
        }
        else {
            //Dialog was end.
           this.removeAndCleanSelf();

        }
    },
    removeAndCleanSelf : function ()
    {
        cc.log("Dialog is ending. remove this Layer.");
        if (this.m_target && (typeof(this.m_pfnSelector) == "function")) {
            this.m_pfnSelector.call(this.m_target, this);
        }
    }
});

lc.NPCDialogLayerLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return lc.NPCDialogLayer.create();
    }
});

lc.NPCDialogLayerLoader.loader = function () {
    return new lc.NPCDialogLayerLoader();
};

lc.NPCDialogLayer.create = function ()
{
    var ret = new lc.NPCDialogLayer();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.NPCDialogLayer.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary.registerCCNodeLoader("FuzzyBgLayer", lc.FuzzyBgLayerLoader.loader());

    ccNodeLoaderLibrary.registerCCNodeLoader("NPCDialogLayer", lc.NPCDialogLayerLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("../Resources/","/ccb/dialog.ccbi");

    return pNode;
};

lc.FuzzyBgLayer = cc.Layer.extend({});

lc.FuzzyBgLayerLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return lc.FuzzyBgLayer.create();
    }
});

lc.FuzzyBgLayerLoader.loader = function () {
    return new lc.FuzzyBgLayerLoader();
};

lc.FuzzyBgLayer.create = function ()
{
    var ret = new lc.FuzzyBgLayer();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.FuzzyBgLayer.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary.registerCCNodeLoader("FuzzyBgLayer", lc.FuzzyBgLayerLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("../Resources/","/ccb/fuzzy.ccbi");

    return pNode;
};
