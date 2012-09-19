var lc = lc = lc || {};

lc.argH = 2;

lc.BattleResultLayer = lc.TouchLayer.extend({
    p_CurEvent : null,
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
             this.removeAndCleanSelf();
         }
    },
    setData : function ( tEvent, target, pfnSelector)
    {
        this.p_CurEvent = tEvent;
        this.m_target = target;
        this.m_pfnSelector = pfnSelector;
    },
    initLayer : function ()
    {
        var screanSize = cc.Director.getInstance().getWinSize();

        var resultOfBattle = this.getChildByTag(10);

        if (resultOfBattle)
        {
            if ( this.p_CurEvent.battleResult == lc.kBattleResultWin )
            {
                resultOfBattle.setString("战斗胜利");
            }
            else {
                resultOfBattle.setString("战斗失败");

                return;
            }
        }

        var labtip = this.getChildByTag(11);

        var basePosition = labtip.getPosition();

        var bonusLabel = cc.LabelTTF.create("过关奖励","Arial", 18);
        bonusLabel.setColor(cc.orange());
        bonusLabel.setAnchorPoint(cc.PointZero());
        bonusLabel.setPosition(cc.PointMake(basePosition.x, basePosition.y - 40*lc.argH));
        this.addChild(bonusLabel);

        basePosition = bonusLabel.getPosition();
        for (var _iter = 0; _iter < this.p_CurEvent.bonus.length; _iter++)
        {
            var _goods = this.p_CurEvent.bonus[_iter];

            var strChar = "";

            if (_goods.type == 1) {
                strChar = "获得金币 ：" + _goods.count;
            }
            else if (_goods.type == 2)
            {
                strChar = "获得经验 ：" + _goods.count;
            }
            else if (_goods.type == 3){
                strChar = "获得物品 ：" + _goods.count;
            }
            else if (_goods.type == 4){
                 var pTempEquip = lc.DictDataManager.getInstance().getEquipment(_goods.id);
                 if (pTempEquip)
                 {
                 strChar = "获得装备 ：" + pTempEquip.name + " " + _goods.count + "件";
                 }
                 else {
                 strChar= "获得装备 ：错误id " + _goods.id;
                 }
            }
            bonusLabel = cc.LabelTTF.create(strChar, "Arial", 18);
            bonusLabel.setColor(cc.white());
            bonusLabel.setAnchorPoint(cc.PointZero());
            bonusLabel.setPosition(cc.PointMake(basePosition.x, basePosition.y  - 18*lc.argH));
            this.addChild(bonusLabel);
            basePosition = bonusLabel.getPosition();
        }

        bonusLabel = cc.LabelTTF.create("战斗奖励","Arial", 18);
        bonusLabel.setColor(cc.orange());
        bonusLabel.setAnchorPoint(cc.PointZero());
        bonusLabel.setPosition(cc.PointMake(basePosition.x, basePosition.y - 18*lc.argH));
        this.addChild(bonusLabel);

        basePosition = bonusLabel.getPosition();
        for (var _iter = 0; _iter < this.p_CurEvent.awardArray.length; _iter++)
        {
            var _goods = this.p_CurEvent.awardArray[_iter];

            var strChar;

            if (_goods.type == 1) {
                strChar = "获得金币 ：" + _goods.count;
            }
            else if (_goods.type == 2)
            {
                strChar = "获得经验 ：" + _goods.count;
            }
            else if (_goods.type == 3){
                strChar = "获得物品 ：" + _goods.count;
            }
            else if (_goods.type == 4){
                strChar = "获得装备 ：" + _goods.count;
            }
            bonusLabel = cc.LabelTTF.create(strChar,"Arial", 18);
            bonusLabel.setColor(cc.white());
            bonusLabel.setAnchorPoint(cc.PointZero());
            bonusLabel.setPosition(cc.PointMake(basePosition.x, basePosition.y  - 18*lc.argH));
            this.addChild(bonusLabel);
            basePosition = bonusLabel.getPosition();
        }
    },
    removeAndCleanSelf : function ()
    {
        this.m_pfnSelector.call(this.m_target);
    }
});

lc.BattleResultLayerLoader = cc.LayerLoader.extend({
                                                _createCCNode:function (parent, ccbReader) {
                                                return lc.BattleResultLayer.create();
                                                }
                                                });

lc.BattleResultLayerLoader.loader = function () {
    return new lc.BattleResultLayerLoader();
};

lc.BattleResultLayer.create = function ()
{
    var ret = new lc.BattleResultLayer();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.BattleResultLayer.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary.registerCCNodeLoader("BattleResultLayer", lc.BattleResultLayerLoader.loader());
    
    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);
    
    var pNode = ccbReader.readNodeGraphFromFile("../Resources/",s_ccbiBattleResult);
    
    return pNode;
};
