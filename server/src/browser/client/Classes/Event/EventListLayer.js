var lc = lc = lc || {};

lc.kTagLayerBattle              =   1;
lc.kTagLayerHeroHead            =   2;
lc.kTagLayerHeroInfo            =   3;
lc.kTagLayerDialog              =   4;
lc.kTagLayerOpenBox             =   5;
lc.kTagLayerOpenBoxResult       =   6;
lc.kTagLayerBattleResult        =   7;


lc.EventListLayer = cc.Layer.extend({
    m_target : null,         //callback listener
    m_pfnSelector : null,    //callback selector
    p_pPage : null,      //Point of page
    mChapterId : 0,
    mLEventType : lc.kLEventTypeGeneralBattle,       //Current Event's event type
    p_CurEvent : null,          //Current Event
    mEventDataList : null,        //All Event in this page
    p_CurLayer : null,       //Current Show Layer
    p_HeroHeadLayer : null,
    ctor:function () {
        this._super();
    },
    init:function () {

        var size = cc.Director.getInstance().getWinSize();
        var helloLabel = cc.LabelTTF.create("EventList", "Arial", 22);
        helloLabel.setColor(cc.red());
        helloLabel.setPosition(cc.p(size.width / 2, size.height /2));
        this.addChild(helloLabel, 9);

        return true;
    },
    initLayer : function (tChapterId,p_page,target,pfnSelector)
    {
        this.mLEventType = lc.kLEventTypeOneEventWasFinished;

        this.m_target = target;
        this.m_pfnSelector = pfnSelector;

        this.p_pPage = p_page;

        this.mChapterId = tChapterId;

        this.p_HeroHeadLayer = null;

        if ( !p_pPage )return;

        this.getEventDataList();
    },
    callbackEventWasFinished : function (node,data)
    {
        this.schedule(this.showSideEvent, 0.01);
    },
     //显示当前事件的分支事件, 战斗结果, 开宝箱
    showSideEvent : function ()
    {
        if ( this.mLEventType == lc.kLEventTypeDialogue )
        {
            this.showDialogLayer();
        }
        else if ( this.mLEventType == lc.kLEventTypeSpecialBattle )
        {
            this.showSpecialBattleLayer();
        }
        else if ( this.mLEventType == lc.kLEventTypeGeneralBattle ){
            this.showGeneralBattleLayer();
        }
        else  if ( this.mLEventType == lc.kLEventTypeFinishedEvent ||  this.mLEventType == lc.kLEventTypeOneEventWasFinished ) {
            this.schedule(this.removeAndCleanSelf, 0.01);
        }
    },
    getCurEvent : function ()
    {
        if ( this.mEventDataList.length > 0 )
        {
            this.p_CurEvent = this.mEventDataList[0];

            switch (this.p_CurEvent.type) {
                case lc.kLEventTypeGeneralBattle:
                {
                    this.mLEventType = lc.kLEventTypeGeneralBattle;
                    break;
                }
                case lc.kLEventTypeDialogue:
                {
                    this.mLEventType = lc.kLEventTypeDialogue;
                    break;
                }
                case lc.kLEventTypeSpecialBattle:
                {
                    this.mLEventType = lc.kLEventTypeSpecialBattle;
                }
                default:
                    break;
            }
        }
        else {
            this.p_CurEvent = null;
        }

        return this.p_CurEvent;
    },
    popEvent : function ()
    {
        if ( this.mEventDataList.length > 0 )
        {
            this.mEventDataList.splice(0,1);

            if ( this.mEventDataList.length > 0 )
            {
                this.p_CurEvent = this.mEventDataList[0];

                switch (this.p_CurEvent.type) {
                    case lc.kLEventTypeGeneralBattle:
                    {
                        this.mLEventType = lc.kLEventTypeGeneralBattle;
                        break;
                    }
                    case lc.kLEventTypeDialogue:
                    {
                        this.mLEventType = lc.kLEventTypeDialogue;
                        break;
                    }
                    case lc.kLEventTypeSpecialBattle:
                    {
                        this.mLEventType = lc.kLEventTypeSpecialBattle;
                        break;
                    }
                    default:
                    {
                        this.mLEventType = lc.kLEventTypeFinishedEvent;
                        this.p_CurEvent = null;
                        break;
                    }
                }
            }
            else {
                this.mLEventType = lc.kLEventTypeFinishedEvent;
                this.p_CurEvent = null;
            }
        }
        else {
            this.mLEventType = lc.kLEventTypeFinishedEvent;
            this.p_CurEvent = null;
        }
    },
    getLEventType : function ()
    {
        return this.mLEventType;
    },
    showCurEvent : function ()
    {
        if ( this.mLEventType == lc.kLEventTypeDialogue )
        {
            this.showDialogLayer();
        }
        else if ( this.mLEventType == lc.kLEventTypeSpecialBattle )
        {
            this.showSpecialBattleLayer();
        }
        else if ( this.mLEventType == lc.kLEventTypeGeneralBattle ){
            this.showGeneralBattleLayer();
        }
        else  if ( this.mLEventType == lc.kLEventTypeFinishedEvent ||  this.mLEventType == lc.kLEventTypeOneEventWasFinished ) {
            this.schedule(this.removeAndCleanSelf, 0.01);
        }
    },
    showDialogLayer : function ()
    {
        var tDialog = lc.NPCDialogLayer.create(this);
        if (tDialog)
        {
            this.removeAllChildLayer();

            tDialog.setData(this.p_CurEvent, this, this. callbackEventWasFinished);

            this.p_CurLayer = tDialog;

            this.addChild(this.p_CurLayer,lc.kTagLayerDialog);
        }
    },
    showGeneralBattleLayer : function ()
    {
        var tGeneralBattle = this.GeneralBattleLayer.create(this);
        if (tGeneralBattle)
        {
            this.removeAllChildLayer();

            tGeneralBattle.setData(this.p_CurEvent, this, this. callbackEventWasFinished);

            this.p_CurLayer = tGeneralBattle;

            this.addChild(this.p_CurLayer,lc.kTagLayerBattle);
        }
    },
    showSpecialBattleLayer : function ()
    {
        var tSpecialBattle = lc.SpecialBattleLayer.create(this);
        if (tSpecialBattle)
        {
            this.removeAllChildLayer();

            tSpecialBattle.setData(this.p_CurEvent, this, this. callbackEventWasFinished);

            this.p_CurLayer = tSpecialBattle;

            this.addChild(this.p_CurLayer,lc.kTagLayerBattle);
        }
    },
    //开箱子, 战斗结果 都依赖于以上面三个界面
    showOpenBoxLayer  : function ()
    {
        if ( this.p_CurEvent && this.p_CurEvent.m_bBoxIsOpened == false && this.p_CurEvent.box_id != -1 )
        {
            this.removeAllChildLayer();

            var pLayer = lc.OpenBoxLayer.create(this);
            pLayer.setData(this.p_CurEvent,this, this.callbackEventWasFinished);

            this.p_CurLayer = pLayer;
            this.addChild(this.p_CurLayer,lc.kTagLayerOpenBox);
        }
    },
    showBattleResultLayer : function ()
    {
        this.removeAllChildLayer();

        var pLayer = lc.BattleResultLayer.create(this);
        pLayer.setData(this.p_CurEvent,this, this.callbackEventWasFinished);
        this.p_CurEvent.m_bBattleResultIsShowed = true;
        pLayer.initLayer();

        this.p_CurLayer = pLayer;

        this.addChild(this.p_CurLayer,lc.kTagLayerBattleResult);
    },
    showHeroHeadLayer  : function ()
    {
        if (this.p_HeroHeadLayer)
        {
            this.p_HeroHeadLayer.removeFromParentAndCleanup(true);
            this.p_HeroHeadLayer = null;
        }
        else {
            this.p_HeroHeadLayer = lc.HeroHeadLayer.create(this);
            this.addChild(this.p_HeroHeadLayer,lc.kTagLayerHeroHead);
        }
    },
    removeAndCleanSelf : function ()
    {
        if (this.m_target && (typeof(this.m_pfnSelector) == "function")) {
            this.m_pfnSelector.call(this.m_target, this);
        }
    },
    removeAllChildLayer : function ()
    {
        if ( this.p_CurLayer )
        {
            this.p_CurLayer.removeFromParentAndCleanup(true);

            this.p_CurLayer = null;
        }
    },
    getEventDataList : function ()
    {
        //NetManager::shareNetManager()->sendEx(kModeEvent, kDoGetEventList, callfuncND_selector(EventListLayer::netCallBackEventList), this, "\"chapterId\": %d, \"pageId\": %d, \"eventId\": %d", mChapterId, p_pPage->id, p_pPage->eventId);
    },
    netCallBackEventList : function (pNode,data)
    {

    }
});

lc.fristEventListLayer = true;

lc.EventListLayer.create = function () {
    if (lc.fristEventListLayer) {
        lc.fristEventListLayer = false;
        var ret = new lc.EventListLayer();
        if (ret && ret.init()) {
            return ret;
        }
    }
    return null;
};