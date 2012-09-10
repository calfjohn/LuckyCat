var lc = lc = lc || {};

lc.TAG_EFFECT_NODE = 3;
lc.TAG_MONSTER  = 91;

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

        this.setIsTouchAreaEnabled(true);

        var size = cc.Director.getInstance().getWinSize();

        var sprite = cc.Sprite.create("../Resources/HelloWorld.png");
        sprite.setAnchorPoint(cc.p(0.5, 0.5));
        sprite.setPosition(cc.p(size.width / 2, size.height / 2));
        this.addChild(sprite,99);
        sprite.setTag(lc.TAG_EFFECT_NODE);
        sprite.setVisible(false);

        var animation = cc.AnimationCache.getInstance().getAnimation("purpleBomb");
        this.m_action = cc.Animate.create(animation);

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
        if (tLTouchEvent == kLTouchEventSingleClick)
        {
            this.getChildByTag(lc.TAG_EFFECT_NODE).runAction(cc.Sequence.create(
                cc.Show.create(),
                this.m_action,
                cc.Hide.create(),
                cc.CallFunc.create(this.m_target, this.m_pfnSelector)) );

            this.setIsTouchForbidden(true);
        }
    },
    notificationTouchEvent : function ( tLTouchEvent )
    {
        if (tLTouchEvent == lc.kLTouchEventSingleClick)
        {
            this.getChildByTag(lc.TAG_EFFECT_NODE).runAction(cc.Sequence.create(
                cc.Show.create(),
                this.m_action,
                cc.Hide.create(),
                cc.CallFunc.create(this.m_target, this.m_pfnSelector)) );

            this.setIsTouchForbidden(true);
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

lc.GeneralBattleLayer.create = function () {
    var ret = new lc.GeneralBattleLayer();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};