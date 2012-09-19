var lc = lc = lc || {};

lc.OpenBoxResultLayer = cc.Layer.extend({
    ctor:function () {
        this._super();
    },
    init:function () {
        this._super();

        return true;
    },
    initLayer : function (tGoodList)
    {
        var screanSize = cc.Director.getInstance().getWinSize();

        var labtip = this.getChildByTag(11);

        var basePosition = labtip.getPosition();

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
                var pTempEquip = lc.DictDataManager.getInstance().getEquipment(_goods.id);
                if (pTempEquip)
                {
                    strChar = "获得装备 ：" + pTempEquip.name + " " + _goods.count + "件";
                }
                else {
                    strChar= "获得装备 ：错误id " + _goods.id;
                }
            }
            bonusLabel = cc.LabelTTF.create(strChar,"Arial", 18);
            bonusLabel.setColor(cc.white());
            bonusLabel.setAnchorPoint(cc.PointZero());
            bonusLabel.setPosition(cc.PointMake(basePosition.x, basePosition.y -25*_iter - 40*lc.argH));
            this.addChild(bonusLabel);
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

    ccNodeLoaderLibrary.registerCCNodeLoader("FuzzyBgLayer", lc.FuzzyBgLayerLoader.loader());

    ccNodeLoaderLibrary.registerCCNodeLoader("OpenBoxResultLayer", lc.OpenBoxResultLayerLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("../Resources/",s_ccbiOpenBoxResult);

    return pNode;
};