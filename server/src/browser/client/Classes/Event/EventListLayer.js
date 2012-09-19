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
    _eventList : null,
    ctor:function () {
        this._super();
    },
    init:function () {

        var size = cc.Director.getInstance().getWinSize();
        var helloLabel = cc.LabelTTF.create("EventList", "Arial", 22);
        helloLabel.setColor(cc.green());
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

        if ( !this.p_pPage )return;

        this.getEventDataList();
    },
    callbackEventWasFinished : function ()
    {
        var that = lc.EventListLayer.getInstance();
        that.showSideEvent();
    },
     //显示当前事件的分支事件, 战斗结果, 开宝箱
    showSideEvent : function ()
    {
        if ( this.isNeedShowBattleResult() )
        {
            this.showBattleResultLayer();
        }
        else if ( this.isNeedShowOpenBoxLayer() ) {
            this.showOpenBoxLayer();
        }
        else if ( this.isLostBattle() ){//战斗失败,事件不再执行
            this.removeAndCleanSelf();
        }else {
            this.popEvent();

            this.showCurEvent();
        }
    },
    isNeedShowBattleResult:function ()
    {
        return false;
    },
    isNeedShowOpenBoxLayer:function ()
    {
        return false;
    },
    isLostBattle:function ()
    {
        return false;
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
            this.removeAndCleanSelf();
        }
    },
    showDialogLayer : function ()
    {
        var tDialog = lc.NPCDialogLayer.createLoader(this);
        if (tDialog)
        {
            this.removeAllChildLayer();

            tDialog.setData(this.p_CurEvent, this, this.callbackEventWasFinished);

            this.p_CurLayer = tDialog;

            this.addChild(this.p_CurLayer,lc.kTagLayerDialog);
        }
    },
    showGeneralBattleLayer : function ()
    {
        var tGeneralBattle = lc.GeneralBattleLayer.createLoader(this);
        if (tGeneralBattle)
        {
            this.removeAllChildLayer();

            tGeneralBattle.setData(this.p_CurEvent, this, this.callbackEventWasFinished);

            this.p_CurLayer = tGeneralBattle;

            this.addChild(this.p_CurLayer,lc.kTagLayerBattle);
        }
    },
    showSpecialBattleLayer : function ()
    {
        var tSpecialBattle = lc.SpecialBattleLayer.createLoader(this);
        if (tSpecialBattle)
        {
            this.removeAllChildLayer();

            tSpecialBattle.setData(this.p_CurEvent, this, this.callbackEventWasFinished);

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

            var pLayer = lc.OpenBoxLayer.createLoader(this);
            pLayer.setData(this.p_CurEvent,this, this.callbackEventWasFinished);

            this.p_CurLayer = pLayer;
            this.addChild(this.p_CurLayer,lc.kTagLayerOpenBox);
        }
    },
    showBattleResultLayer : function ()
    {
        this.removeAllChildLayer();

        var pLayer = lc.BattleResultLayer.createLoader(this);
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
            this.p_HeroHeadLayer = lc.HeroHeadLayer.createLoader(this);
            this.addChild(this.p_HeroHeadLayer,lc.kTagLayerHeroHead);
        }
    },
    removeAndCleanSelf : function ()
    {
        this.m_pfnSelector.call(this.m_target);
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
        var str = "\"chapterId\":" + this.mChapterId + ",\"pageId\":"  + this.p_pPage.id  + ",\"eventId\":" + this.p_pPage.event_id;
        lc.NetManager.sharedNetManager().sendRequest(ModeRequestType.kModeEvent,DoRequestType.kDoGetEventList,str,lc.EventListLayer.getInstance().netCallBackEventList,lc.EventListLayer.getInstance().netErrorCallBackEventList);
    },
    netCallBackEventList : function (data)
    {
        if ( data )
        {
            var that = lc.EventListLayer.getInstance();
            var retData = JSON.parse(data);
            that.mEventDataList = retData.meta.out.eventList;

            for(var i = 0; i < that.mEventDataList.length; i++)
            {
                var temp = that.mEventDataList[i];
                temp.battleResultIsShowed = false;
                temp.boxIsOpened = false;
                temp.battleResult = lc.kBattleResultWin;
            }

            that.p_CurEvent = that.getCurEvent();
            that.showCurEvent();
        }
    },
    netErrorCallBackEventList : function (data)
    {
        var that = lc.EventListLayer.getInstance();
        that.mEventDataList = null;
    }
});


lc.fristEventListLayer = true;
lc.s_SharedEventListLayer = null;

lc.EventListLayer.getInstance = function () {
    if (lc.fristEventListLayer) {
        lc.fristEventListLayer = false;
        lc.s_SharedEventListLayer = new lc.EventListLayer();
        lc.s_SharedEventListLayer.init();
    }
    return lc.s_SharedEventListLayer;
};

lc.EventListLayer.destroyInstance = function () {
    lc.fristEventListLayer = true;
    lc.s_SharedEventListLayer = null;
}