#include "LuckySprite.h"
#include "DictDataManager.h"

LuckySprite::LuckySprite(void)
{

}

LuckySprite::~LuckySprite(void)
{
}

LuckySprite* LuckySprite::create(int imageId, float scale)
{
    const stImage *pImage = DictDataManager::shareDictDataManager()->getImage(imageId);
    if (!pImage) 
    {
        return NULL;
    }
    
    LuckySprite *pobSprite = new LuckySprite();
    if (pImage->type == 0) 
    {
        if (pobSprite && pobSprite->initWithFile(pImage->filePath.c_str()))
        {
            pobSprite->autorelease();
            return pobSprite;
        }
    }
    else 
    {
        if (pobSprite && pobSprite->initWithSpriteFrameName(pImage->name.c_str()))
        {
            pobSprite->autorelease();
            pobSprite->setScale(scale);
            return pobSprite;
        }
    }
    
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

cocos2d::CCTexture2D *LuckySprite::getTextrue2D(const char *file_name)
{
    return cocos2d::CCTextureCache::sharedTextureCache()->addImage(file_name);
}

cocos2d::CCSpriteFrame *LuckySprite::getSpriteFrame(const char *_name)
{
    return cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name);
}
