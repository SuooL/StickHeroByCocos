//
//  BackgroundLayer.h
//  StickHero
//
//  Created by 胡振生 on 15/8/26.
//
//

#ifndef __StickHero__BackgroundLayer__
#define __StickHero__BackgroundLayer__

#include <stdio.h>

#include "cocos2d.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
#include "GameOverLayer.h"
USING_NS_CC;
class BackgroundLayer:public Layer {
private:
    static const int STICK_SPEED = 2;//stick增长的速度
    static const int BG_SPEED = 2;
    bool isStart;
    bool isStickLength;
    Size MyWinSize;
    Menu* menu;
    Sprite* GameName;
    Sprite* Image_One;
    Sprite* Image_Two;
    Sprite* stageSprite[3];
    int stageNumber;
    int NowStage;
    int LastStage;
    int NextStage;
    
    Player* player;
    Sprite* stick;
    double TouchLength;
    double DestLengthMin;
    double DestLengthMax;
    int scoreCount;
    bool successFlag;//
    bool moveComplete;//
    Label* scoreTitle;//
    
    
    Vec2 StickPoint;
    int kickId;
    int countID;
    
    GameOverLayer* gameOverLayer;
    
    EventListenerTouchOneByOne* touchListener;
    
public:
    BackgroundLayer();
    ~BackgroundLayer();
    static Scene* createScene();
    CREATE_FUNC(BackgroundLayer);
    bool init();
    void Start(Ref* pSender);
    void ChangePlayer(Ref* pSender);
    void bgMove(float);//背景移动
    
    void addStage();
    void stageMove();
    bool onTouchBegan(Touch* pTouch, Event* pEvent);
    void onTouchMoved(Touch* pTouch, Event* pEvent);
    void onTouchEnded(Touch* pTouch, Event* pEvent);
    
    void addStick();
    void StickLength(float);
    void StopStick();
    void RotateStickAndGo();
    void stickCallBack(bool successFlag);
    void initStick();            //初始化stick
    void stopAudio(int audioId);
    void beforeOverAni(Vec2 point);
    void gameOver();
};



#endif /* defined(__StickHero__BackgroundLayer__) */
