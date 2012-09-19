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
        this.removeAndCleanSelf();
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
    },
    removeAndCleanSelf : function ()
    {
        this.m_pfnSelector.call();
    }
});

lc.SpecialBattleLayerLoader = cc.LayerLoader.extend({
                                                _createCCNode:function (parent, ccbReader) {
                                                return lc.SpecialBattleLayer.create();
                                                }
                                                });

lc.SpecialBattleLayerLoader.loader = function () {
    return new lc.SpecialBattleLayerLoader();
};

lc.SpecialBattleLayer.create = function ()
{
    var ret = new lc.SpecialBattleLayer();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.SpecialBattleLayer.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary.registerCCNodeLoader("BasicInfoLayer", lc.BasicInfoLayerLoader.loader());

    ccNodeLoaderLibrary.registerCCNodeLoader("SpecialBattleLayer", lc.SpecialBattleLayerLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);
    
    var pNode = ccbReader.readNodeGraphFromFile("../Resources/",s_ccbiBattle);
    
    return pNode;
};