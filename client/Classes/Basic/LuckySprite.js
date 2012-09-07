var lc = lc = lc || {};

lc.LuckySprite = cc.Sprite.extend({
    m_nImageId : 0,
    m_fScale : 1.0,
    ctor:function () {
        this._super();
    },
    //在这里初始化数据,读取数据库
    init:function () {
        this._super();

        if (this.m_nImageId > 0)
        {
            var pImage = lc.DictDataManager.getShareInstance().getImage(this.m_nImageId);
            if ( !pImage )
            {
                return false;
            }

            if (pImage.type == 0)
            {
                this.initWithFile(pImage.filePath);
            }
            else
            {
                this.initWithSpriteFrameName(pImage.name);
            }

            return true;
        }

        return false;
    },
    setNewTexture:function (imageId)
    {
        if (imageId == m_nImageId)
        {
            return true;
        }

        var pImage = lc.DictDataManager.getShareInstance().getImage(this.m_nImageId);
        if (!pImage)
        {
            return false;
        }

        m_nImageId = imageId;

        if (pImage.type == 0)
        {
            var pTexture = cc.SpriteFrameCache.getInstance().getSpriteFrame(pImage.filePath);
            if (!pTexture)
            {
                return false;
            }
            this.setTexture(pTexture);
        }
        else
        {
            var pFrame = cc.SpriteFrameCache.getInstance().getSpriteFrame(pImage.name);
            if (!pFrame)
            {
                return false;
            }
            this.setDisplayFrame(pFrame);
        }

        return true;
    }
});

lc.LuckySprite.create = function (imageId, scale)
{
    var retValue = new lc.LuckySprite();
    switch (arguments.length) {
        case 2:
        {
            retValue.m_nImageId = imageId;
            retValue.m_fScale = scale;
            break;
        }
        case 1:
        {
            retValue.m_nImageId = imageId;
            break;
        }
        default:
            break;
    }

    if ( retValue && retValue.init() )
    {
        return retValue;
    }
    return null;
};