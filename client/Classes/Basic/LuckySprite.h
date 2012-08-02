#ifndef _BALL_H_
#define _BALL_H_

#include "cocos2d.h"


class LuckySprite : public cocos2d::CCSprite
{
public:
    LuckySprite(void);
    virtual ~LuckySprite(void);

public:
    static LuckySprite* create(int imageId, float scale = 1);
};

#endif
