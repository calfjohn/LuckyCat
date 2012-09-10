
var lc = lc = lc || {};

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

        var size = cc.Director.getInstance().getWinSize();

        this.mLabelNpcName = cc.LabelTTF.create("NPC Dialog", "Arial", 38);
        this.mLabelNpcName.setPosition(cc.p(size.width / 2, size.height /2));
        this.addChild(this.mLabelNpcName, 9);

        this.setIsTouchAreaEnabled(true);

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
    setDialog : function ( talk )
    {
        var dialog = lc.EventDataManager.getShareInstance().getDialogFromTalk(tTalk);
        this.mLabelNpcName.setString(tTalk.npcName);
        mLabelDialogContent.setString(dialog);
    },
    setData : function ( tEvent, target, pfnSelector)
    {
        this.p_CurEvent = tEvent;
        this.m_target = target;
        this.m_pfnSelector = pfnSelector;

        this.mLabelNpcName = this.getChildByTag(10);
        this.mLabelDialogContent = this.getChildByTag(11);
        this.mSpriteNpc = this.getChildByTag(91);

        this.mTalkList.clear();

        this.mTalkList = lc.EventDataManager.getShareInstance().getAllTalk(p_CurEvent.id);


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
            this.setDialog(tTalk);
        }
        else {
            //Dialog was end.
           this.removeAndCleanSelf();

        }
    },
    removeAndCleanSelf : function ()
    {
        if (this.m_target && (typeof(this.m_pfnSelector) == "function")) {
            this.m_pfnSelector.call(this.m_target, this);
        }
    }
});


lc.NPCDialogLayer.create = function (pOwner) {
    var ret = new lc.NPCDialogLayer();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};