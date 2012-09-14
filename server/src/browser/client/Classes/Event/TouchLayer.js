/**
 * Created with JetBrains WebStorm.
 * User: zhuxiaozhong
 * Date: 12-9-4
 * Time: 下午4:33
 * To change this template use File | Settings | File Templates.
 */
var lc = lc = lc || {};

/**
 * 这个类用于处理Touch事件,
 * 可扩展为手势处理
 */

/**
 * LTouchEvent 点击事件类型
 */
lc.kLTouchEventSingleClick              =   1;          //点击
lc.kLTouchEventDoubleClick              =   2;          //双击
lc.kLTouchEventSliding                  =   3;          //滑动
lc.kLTouchEventOutsideTouchArea         =   4;          //点击到点击区域之外
lc.kLTouchEventInsideTouchArea          =   5;          //点击到点击区域之内

lc.TouchLayer = cc.Layer.extend({
    m_bTouchForbidden : false,
    m_bTouchAreaEnabled : false,
    mBeginPoint : cc.PointZero(),
    m_TouchNodeList : [],
    pNode : null,
    ctor:function () {
        this._super();
    },
    init:function () {
        this.setTouchEnabled(true);
        return true;
    },
    registerWithTouchDispatcher:function () {
        cc.Director.getInstance().getTouchDispatcher().addTargetedDelegate(this,cc.MENU_HANDLER_PRIORITY + 10 , true);
    },
    onTouchBegan:function (touch, event) {
        cc.Assert(false, "Layer#onTouchBegan override me");
        if ( !touch ) return false;

        if ( this.getIsTouchAreaEnabled() )
        {
            var tPoint = touch._point;
            var _tPoint = this.convertTouchToNodeSpace(touch);

            cc.log("Orign x : " + tPoint.x + ", y: " + tPoint.y);
            cc.log("Conve x : " + _tPoint.x + ", y: " + _tPoint.y);
            if ( this.TouchAreaContainsPoint(tPoint) == false )
            {
                this.notificationTouchEvent(lc.kLTouchEventOutsideTouchArea);
            }
            else
            {
                this.notificationTouchEvent(lc.kLTouchEventInsideTouchArea);
            }
        }

        if ( this.getIsTouchForbidden() )
        {
            this.mBeginPoint.x = 0;
            this.mBeginPoint.y = 0;

            cc.log("Begin Touch Forbidden.");

            return false;
        }

        this.mBeginPoint.x = touch._point.x;
        this.mBeginPoint.y = touch._point.y;

        return true;
    },
    onTouchMoved:function (touch, event) {
    },
    onTouchEnded:function (touch, event) {
        if ( !touch ) return;

        if ( this.mBeginPoint.x != 0 && this.mBeginPoint.y != 0 )
        {
            this.notificationTouchEvent(lc.kLTouchEventSingleClick);
            cc.log("onTouchEnded Touch kLTouchEventSingleClick.");
        }

        this.mBeginPoint.x = 0;
        this.mBeginPoint.y = 0;
    },
    /**
     * 想要获得Touch事件的通知,必须重写这个函数
     */
    notificationTouchEvent:function (tLTouchEvent)
    {
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
    registerTouchNode:function (pNode)
    {
        if (pNode)
        {
            for (var i = 0; this.m_TouchNodeList && i < this.m_TouchNodeList.length ; i++)
            {
                var pN = this.m_TouchNodeList[i];
                if ( pN == pNode )
                {
                    return false;
                }
            }
            this.m_TouchNodeList.push(pNode);
            return true;
        }
        return false;
    },
    removeTouchNode:function (pNode)
    {
        if (pNode)
        {
            for (var i = 0; this.m_TouchNodeList && i < this.m_TouchNodeList.length ; i++)
            {
                var pN = this.m_TouchNodeList[i];
                if ( pN == pNode )
                {
                    this.m_TouchNodeList.splice(i,1);
                    return true;
                }
            }
        }
        return false;
    },
    TouchAreaContainsPoint:function (tPoint)
    {
        for (var i = 0; this.m_TouchNodeList && i < this.m_TouchNodeList.length; i++)
        {
            var pNode = this.m_TouchNodeList[i];
            if ( pNode )
            {
                var tRect = this.getRect(pNode);

                if ( cc.Rect.CCRectContainsPoint(tRect,tPoint) )
                {
                    return true;
                }
            }
        }
        return false;
    },
    getRect:function (pNode)
    {
        var rc = cc.RectMake(pNode.getPosition().x , pNode.getPosition().y , pNode.getContentSize().width , pNode.getContentSize().height);

        var scaleY = pNode.getScaleY();
        var scaleX = pNode.getScaleX();

        if ( scaleX != 1.0 )
        {
            rc.size.width *= scaleX;
        }
        if ( scaleY != 1.0 )
        {
            rc.size.height *= scaleY;
        }

        if ( pNode.isIgnoreAnchorPointForPosition() == false )
        {
            var tAnchorPoint = pNode.getAnchorPoint();

            rc.origin.x = ( rc.origin.x - rc.size.width * tAnchorPoint.x ) | 0;
            rc.origin.y = ( rc.origin.y - rc.size.height * tAnchorPoint.y ) | 0;
        }

        return rc;
    },
    getIsTouchForbidden:function()
    {
        return this.m_bTouchForbidden;
    },
    setIsTouchForbidden: function (tEnabled)
    {
        this.m_bTouchForbidden = tEnabled;
    },
    getIsTouchAreaEnabled: function ()
    {
        return this.m_bTouchAreaEnabled;
    },
    setIsTouchAreaEnabled: function (tEnabled)
    {
        this.m_bTouchAreaEnabled = tEnabled;
    }
});

lc.TouchLayer.create = function () {
    var ret = new lc.TouchLayer();
    if (ret && ret.init()) {
        return ret;
    }
    return null;
};