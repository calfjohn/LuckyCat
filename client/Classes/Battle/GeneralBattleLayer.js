var lc = lc = lc || {};

lc.GeneralBattleLayer = lc.TouchLayer.extend({
    mSpriteNpc : null,
    p_CurEvent : null,
    m_target : null,         //callback listener
    m_pfnSelector : null,    //callback selector
    m_action : null,
    ctor:function () {
        this._super();
    },
    init:function () {
        this._super();

        var size = cc.Director.getInstance().getWinSize();

        var lazyLayer = new cc.LazyLayer();
        this.addChild(lazyLayer);

        var sprite = cc.Sprite.create("../Resources/HelloWorld.png");
        sprite.setAnchorPoint(cc.p(0.5, 0.5));
        sprite.setPosition(cc.p(size.width / 2, size.height / 2));
        sprite.setScale(0.5);

        lazyLayer.addChild(sprite, 0);


        var helloLabel = cc.LabelTTF.create("GeneralBattleLayer", "Arial", 38);
        helloLabel.setPosition(cc.p(size.width / 2, size.height /2));
        lazyLayer.addChild(helloLabel, 9);

        this.setIsTouchAreaEnabled(true);
        this.registerTouchNode(sprite);

        return true;
    },
    onMenuItemClicked : function ( pTarget )
    {
        cc.log("tag " + pTarget.getTag());
        /*todo
        if(pTarget.getTag() == 1){
            var pNode = this.getChildByTag(lc.TAG_PLAYER_INFO);
            if (!pNode)
            {
                var pInfo = lc.PlayerInfoLayer.create(this);
                this.addChild(pInfo);
                pInfo.setTag(lc.TAG_PLAYER_INFO);
            }
            else {
                pNode.removeFromParentAndCleanup(true);
            }
        }
        */
    },
    onCCControlButtonClicked : function ( pSender, pCCControlEvent)
    {

    },
    notificationTouchEvent : function ( tLTouchEvent )
    {

        /*todo
        if (tLTouchEvent == lc.kLTouchEventSingleClick)
        {
            this.getChildByTag(lc.TAG_EFFECT_NODE).runAction(CCSequence::create(
                cc.CCShow.create(),
                m_action,
                cc.CCHide.create(),
                cc.CCCallFuncND.create(m_target, m_pfnSelector)));

            this.setIsTouchForbidden(true);
        }
        */
        if ( tLTouchEvent == lc.kLTouchEventOutsideTouchArea )
        {
            cc.log("kLTouchEvent Outside TouchArea");
        }
        else if ( tLTouchEvent == lc.kLTouchEventInsideTouchArea )
        {
            cc.log("kLTouchEvent Inside TouchArea");
        }
        else if (tLTouchEvent == lc.kLTouchEventSingleClick)
        {
            cc.log("kLTouchEvent SingleClick");
        }
    },
    setData : function ( tEvent, target, pfnSelector)
    {
        this.p_CurEvent = tEvent;
        this.m_target = target;
        this.m_pfnSelector = pfnSelector;

        this.mSpriteNpc = this.getChildByTag(91);

//        LuckySprite *pSpriteMonster = static_cast<LuckySprite *>(this->getChildByTag(TAG_MONSTER));
//        if (pSpriteMonster)
//        {
//            const stMonster * pMonster = DictDataManager::shareDictDataManager()->getMonsterImageId(p_CurEvent->targetId);
//            pSpriteMonster->setNewTexture(pMonster->imageId);
//        }

        this.showDialog();
    },
    removeAndCleanSelf : function ()
    {
        if (this.m_target && (typeof(this.m_pfnSelector) == "function")) {
            this.m_pfnSelector.call(this.m_target, this);
        }
    }
});

lc.GeneralBattleLayer.create = function (pOwner) {
    var ret = new lc.GeneralBattleLayer();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};