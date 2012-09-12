var lc = lc = lc || {};

lc.OpenBoxResultLayer = cc.Layer.extend({
    ctor:function () {
        this._super();
    },
    init:function () {
        this._super();

        var size = cc.Director.getInstance().getWinSize();
        var helloLabel = cc.LabelTTF.create("OpenBoxResult", "Arial", 22);
        helloLabel.setColor(cc.red());
        helloLabel.setPosition(cc.p(size.width / 2, size.height /2));
        this.addChild(helloLabel, 9);

        return true;
    },
    initLayer : function (tGoodList)
    {
        var screanSize = cc.Director.getInstance().getWinSize();

        var labtip = this.getChildByTag(11);

        var basePosition = labtip.getPosition();

        var bonusLabel = cc.LabelTTF.create("过关奖励", cc.SizeMake(screanSize.width * 0.8, screanSize.height * 0.15 ), cc.TEXT_ALIGNMENT_LEFT, cc.TEXT_ALIGNMENT_CENTER,"Arial", 18);
        bonusLabel.setColor(cc.orange());
        bonusLabel.setAnchorPoint(cc.PointZero());
        bonusLabel.setPosition(cc.PointMake(basePosition.x, basePosition.y - 40));
        this.addChild(bonusLabel);

        basePosition = bonusLabel.getPosition();
        for (var _iter = 0; _iter < tGoodList.length; _iter++)
        {
            var _goods = tGoodList[_iter];

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
            bonusLabel.setPosition(cc.PointMake(basePosition.x, basePosition.y -25*i - 40));
            this.addChild(bonusLabel);
            basePosition = bonusLabel.getPosition();
        }
    }
});

lc.OpenBoxResultLayerLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return lc.OpenBoxResultLayer.create();
    }
});

lc.OpenBoxResultLayerLoader.loader = function () {
    return new lc.OpenBoxResultLayerLoader();
};

lc.OpenBoxResultLayer.create = function ()
{
    var ret = new lc.OpenBoxResultLayer();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.OpenBoxResultLayer.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary.registerCCNodeLoader("OpenBoxResultLayer", lc.OpenBoxResultLayerLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("",s_ccbiOpenBoxResult);

    return pNode;
};