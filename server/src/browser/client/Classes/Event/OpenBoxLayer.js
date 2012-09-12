var lc = lc = lc || {};

lc.TAG_BUTTON_OPEN_BOX = 11;

lc.OpenBoxLayer = lc.TouchLayer.extend({
    p_CurEvent : null,
    m_target : null,         //callback listener
    m_pfnSelector : null,    //callback selector
    m_bIsOpen : false,
    ctor:function () {
        this._super();
    },
    init:function () {
        this._super();

        var size = cc.Director.getInstance().getWinSize();
        var helloLabel = cc.LabelTTF.create("OpenBox", "Arial", 22);
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
        if ( this.m_bIsOpen == false && this.p_CurEvent.m_bBoxIsOpened == false && this.p_CurEvent && this.p_CurEvent.box_id != -1)
        {
            var pOpenBoxResult = lc.OpenBoxResultLayer.create();
            pOpenBoxResult.initLayer(this.p_CurEvent.boxAward);
            this.addChild(pOpenBoxResult,99);

            this.m_bIsOpen = true;

            var pControlButton = this.getChildByTag(lc.TAG_BUTTON_OPEN_BOX);
            if (pControlButton)
            {
                pControlButton.setEnabled(false);
            }


            if (this.p_CurEvent)
            {
                this.p_CurEvent.m_bBoxIsOpened = true;
            }
        }else {
            this.removeAndCleanSelf();
        }
    },
    notificationTouchEvent : function ( tLTouchEvent )
    {
        if (tLTouchEvent == lc.kLTouchEventSingleClick)
        {
            this.onCCControlButtonClicked(null,null);
        }
    },
    setData : function ( tEvent, target, pfnSelector)
    {
        this.p_CurEvent = tEvent;
        this.m_target = target;
        this.m_pfnSelector = pfnSelector;
    },
    removeAndCleanSelf : function (dt)
    {
        if (this.m_target && (typeof(this.m_pfnSelector) == "function")) {
            this.m_pfnSelector.call(this.m_target, this);
        }
    }
});

lc.OpenBoxLayerLoader = cc.LayerLoader.extend({
                                                _createCCNode:function (parent, ccbReader) {
                                                return lc.OpenBoxLayer.create();
                                                }
                                                });

lc.OpenBoxLayerLoader.loader = function () {
    return new lc.OpenBoxLayerLoader();
};

lc.OpenBoxLayer.create = function ()
{
    var ret = new lc.OpenBoxLayer();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};

lc.OpenBoxLayer.createLoader = function (pOwner) {
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary.registerCCNodeLoader("OpenBoxLayer", lc.OpenBoxLayerLoader.loader());
    
    var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);
    
    var pNode = ccbReader.readNodeGraphFromFile("",s_ccbiOpenBox);
    
    return pNode;
};
