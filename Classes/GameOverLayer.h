//
//  GameOverLayer.h
//  StickHero
//
//  Created by 胡振生 on 15/8/26.
//
//

#ifndef __StickHero__GameOverLayer__
#define __StickHero__GameOverLayer__

#include "cocos2d.h"

extern bool isRestart;

class GameOverLayer : public cocos2d::Layer{
public:
    GameOverLayer();
    virtual ~GameOverLayer();
    virtual bool init();
    CREATE_FUNC(GameOverLayer);
    void reStart();
    void home();
};
#endif /* defined(__StickHero__GameOverLayer__) */
