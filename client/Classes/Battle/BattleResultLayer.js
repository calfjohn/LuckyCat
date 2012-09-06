var lc = lc = lc || {};

lc.BattleResultLayer = lc.TouchLayer.extend({
    p_CurEvent : null,
    m_target : null,         //callback listener
    m_pfnSelector : null,    //callback selector
    ctor:function () {
        this._super();
    },
    init:function () {
        this._super();

        var size = cc.Director.getInstance().getWinSize();
        var helloLabel = cc.LabelTTF.create("Battle Result", "Arial", 22);
        helloLabel.setColor(cc.red());
        helloLabel.setPosition(cc.p(size.width / 2, size.height /2));
        this.addChild(helloLabel, 9);

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
            if ( this.p_CurEvent.batleProcess.m_battleResult == lc.kBattleResultWin )
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

        var bonusLabel = cc.LabelTTF.create("过关奖励", cc.SizeMake(screanSize.width * 0.8, screanSize.height * 0.15 ), cc.TEXT_ALIGNMENT_LEFT, cc.TEXT_ALIGNMENT_CENTER,"Arial", 18);
        bonusLabel.setColor(cc.orange());
        bonusLabel.setAnchorPoint(cc.PointZero());
        bonusLabel.setPosition(cc.SizeMake(basePosition.x, basePosition.y - 40));
        this.addChild(bonusLabel);

        basePosition = bonusLabel.getPosition();
        for (var _iter = 0; _iter < tEvent.bonus.length; _iter++)
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
                /*todo
                var pTempEquip = DictDataManager::shareDictDataManager()->getEquipment(_goods.id);
                if (pTempEquip) {
                    strChar = "获得装备 ：" + pTempEquip.equipName + " " + _goods.count + "件";
                }
                else {
                    strChar= "获得装备 ：错误id " + _goods.id;
                }
                */
            }
            bonusLabel = cc.LabelTTF.create(strChar, cc.SizeMake(screanSize.width * 0.8, screanSize.height * 0.15 ), cc.TEXT_ALIGNMENT_LEFT, cc.TEXT_ALIGNMENT_CENTER,"Arial", 18);
            bonusLabel.setColor(cc.white());
            bonusLabel.setAnchorPoint(cc.PointZero());
            bonusLabel.setPosition(cc.PointMake(basePosition.x, basePosition.y  - 18));
            this.addChild(bonusLabel);
            basePosition = bonusLabel.getPosition();
        }

        bonusLabel = cc.LabelTTF.create("战斗奖励", cc.SizeMake(screanSize.width * 0.8, screanSize.height * 0.15 ), cc.TEXT_ALIGNMENT_LEFT, cc.TEXT_ALIGNMENT_CENTER,"Arial", 18);
        bonusLabel.setColor(cc.orange());
        bonusLabel.setAnchorPoint(cc.PointZero());
        bonusLabel.setPosition(cc.PointMake(basePosition.x, basePosition.y - 18));
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
            bonusLabel = cc.LabelTTF.create(strChar, cc.SizeMake(screanSize.width * 0.8, screanSize.height * 0.15 ), cc.TEXT_ALIGNMENT_LEFT, cc.TEXT_ALIGNMENT_CENTER,"Arial", 18);
            bonusLabel.setColor(cc.white());
            bonusLabel.setAnchorPoint(cc.PointZero());
            bonusLabel.setPosition(cc.PointMake(basePosition.x, basePosition.y  - 18));
            this.addChild(bonusLabel);
            basePosition = bonusLabel.getPosition();
        }
    },
    removeAndCleanSelf : function ()
    {
        if (this.m_target && (typeof(this.m_pfnSelector) == "function")) {
            this.m_pfnSelector.call(this.m_target, this);
        }
    }
});

lc.BattleResultLayer.create = function (pOwner) {
    var ret = new lc.BattleResultLayer();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};
