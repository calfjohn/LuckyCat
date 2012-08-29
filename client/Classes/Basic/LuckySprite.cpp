#include "LuckySprite.h"
#include "DictDataManager.h"

USING_NS_CC;

LuckySprite::LuckySprite(void)
{
    m_nImageId =  0;
}

LuckySprite::LuckySprite(int imageId)
{
    m_nImageId = imageId;
}

LuckySprite::~LuckySprite(void)
{
}

bool LuckySprite::init()
{
    const stImage *pImage = DictDataManager::shareDictDataManager()->getImage(m_nImageId);
    if (!pImage) 
    {
        return false;
    }
    
    if (pImage->type == 0) 
    {
        initWithFile(pImage->filePath.c_str());
    }
    else 
    {
        initWithSpriteFrameName(pImage->name.c_str());
    }
    
    return true;
}

LuckySprite* LuckySprite::create(int imageId, float scale)
{
    LuckySprite *pSprite = new LuckySprite(imageId);
    if (pSprite && pSprite->init())
    {
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}
//
//cocos2d::CCTexture2D *LuckySprite::getTextrue2D(const char *file_name)
//{
//    return cocos2d::CCTextureCache::sharedTextureCache()->addImage(file_name);
//}

//cocos2d::CCSpriteFrame *LuckySprite::getSpriteFrame(const char *_name)
//{
//    return cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name);
//}

bool LuckySprite::setNewTexture(int imageId)
{
    if (imageId == m_nImageId) 
    {
        return true;
    }
    const stImage *pImage = DictDataManager::shareDictDataManager()->getImage(imageId);
    if (!pImage) 
    {
        return false;
    }
    
    m_nImageId = imageId;

    if (pImage->type == 0) 
    {
        cocos2d:CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pImage->filePath.c_str());
        if (!pTexture) 
        {
            return false;
        }
        setTexture(pTexture);
    }
    else 
    {
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pImage->name.c_str());
        if (!pFrame) 
        {
            return false;
        }
        setDisplayFrame(pFrame);
    }    
    return true;
}
