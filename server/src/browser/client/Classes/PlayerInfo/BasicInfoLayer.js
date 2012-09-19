var lc = lc = lc || {};

lc.BasicInfoLayer = cc.Layer.extend({
    sendBasicInfo: function ()
    {
        var str = "";
        lc.NetManager.sharedNetManager().sendRequest(ModeRequestType.kModeActor,DoRequestType.kDoGetBasicInfo,str,this,this.responesBasicInfo,this.responesBasicInfoError);
    },
    responesBasicInfo: function (data)
    {
        if ( data )
        {
            //var that = lc.EventListLayer.getInstance();
            var that = this;
            var retData = JSON.parse(data);
            var tInfo = retData.meta.out;

            var t = this.getChildByTag(1);
            this.getChildByTag(1).setString("等级:"+tInfo.level);
            this.getChildByTag(7).setString("经验:"+tInfo.exp);
            this.getChildByTag(6).setString("金币:"+120);
            this.getChildByTag(3).setString("H P:"+tInfo.hp);
            this.getChildByTag(2).setString("攻击:"+tInfo.attack);
            this.getChildByTag(4).setString("防御:"+tInfo.defence);
            this.getChildByTag(5).setString("速度:"+tInfo.speed);
            this.getChildByTag(8).setString("战绩:"+"66胜1负");
            this.getChildByTag(9).setString(tInfo.nickname);


        }
    },
    responesBasicInfoError: function (data)
    {
        //
    }
});

lc.BasicInfoLayerLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return lc.BasicInfoLayer.create();
    }
});

lc.BasicInfoLayerLoader.loader = function () {
    return new lc.BasicInfoLayerLoader();
};

lc.BasicInfoLayer.create = function ()
{
    var ret = new lc.BasicInfoLayer();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.BasicInfoLayer.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary.registerCCNodeLoader("BasicInfoLayer", lc.BasicInfoLayerLoader.loader());

    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

    var pNode = ccbReader.readNodeGraphFromFile("../Resources/","/ccb/basic.ccbi");

    return pNode;
};
