#ifndef _BALL_H_
#define _BALL_H_

#include "cocos2d.h"

class LuckySprite : public cocos2d::CCSprite
{
public:
    LuckySprite(void);
    LuckySprite(int imageId);
    virtual ~LuckySprite(void);

public:
    static LuckySprite* create(int imageId, float scale = 1);
    
//    static cocos2d::CCTexture2D *getTextrue2D(const char *_name);
    
//    static cocos2d::CCSpriteFrame *getSpriteFrame(const char *file_name);
    
    bool setNewTexture(int imageId);
    
private:
    bool init();
    
    int m_nImageId;
};

#endif
