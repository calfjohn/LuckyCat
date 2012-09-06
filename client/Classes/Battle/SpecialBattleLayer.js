var lc = lc = lc || {};

lc.SpecialBattleLayer = lc.TouchLayer.extend({
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
        var helloLabel = cc.LabelTTF.create("Special Battle Result", "Arial", 22);
        helloLabel.setColor(cc.red());
        helloLabel.setPosition(cc.p(size.width / 2, size.height /2));
        this.addChild(helloLabel, 9);

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

lc.SpecialBattleLayer.create = function (pOwner) {
    var ret = new lc.SpecialBattleLayer();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};