//
//  Player.h
//  StickHero
//
//  Created by 胡振生 on 15/8/26.
//
//

#ifndef __StickHero__Player__
#define __StickHero__Player__

#include "cocos2d.h"


USING_NS_CC;

class Player{
private:
    Sprite* _player;
    // Animation* WalkAnimation;
    // Animation* StayAnimation;
    Animate* WalkAnimate;
    Animate* StayAnimate;
    
    int runSpeed;
    
public:
    // Player(int typeID);
    virtual ~Player();
    
    bool init(int typeID);
    Sprite* getPlayer();
    
    static Animate* animationWithFrameName(const char *frameName, int iloops, float delay);

    void SetPosition(Vec2);
    void Walk();
    void Stay();
    void Stop();
    void Start(Vec2);
    Animate* getWalkAnimate();
    Animate* getStayAnimate();
    
    int getSpeed();
    
};

#endif /* defined(__StickHero__Player__) */
