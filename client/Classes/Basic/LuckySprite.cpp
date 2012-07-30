#include "LuckySprite.h"
#include "DictDataManager.h"

LuckySprite::LuckySprite(void)
{
}

LuckySprite::~LuckySprite(void)
{
}

LuckySprite* LuckySprite::create(int imageId)
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
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pImage->plistPath.c_str(), pImage->filePath.c_str());
        if (pobSprite && pobSprite->initWithSpriteFrameName( (pImage->plistPath + "/" + pImage->name).c_str()))
//        if (pobSprite && pobSprite->initWithSpriteFrameName(pImage->name.c_str()))
        {
            pobSprite->autorelease();
            return pobSprite;
        }
    }
    
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}
