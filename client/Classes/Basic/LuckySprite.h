#ifndef _BALL_H_
#define _BALL_H_

#include "cocos2d.h"

USING_NS_CC;

class LuckySprite : public CCSprite
{
public:
    LuckySprite(void);
    virtual ~LuckySprite(void);

public:
    static LuckySprite* create(int imageId, float scale = 1);
};

#endif
