//
//  GameOverLayer.cpp
//  StickHero
//
//  Created by 胡振生 on 15/8/26.
//
//

#include "GameOverLayer.h"
#include "BackgroundLayer.h"
#include "string.h"
USING_NS_CC;

bool isRestart;

bool GameOverLayer::init(){
    
    if(!Layer::init()){
        return false;
    }
    
    Size  MyWinSize = Director::getInstance()->getVisibleSize();
    
    MenuItemSprite *reStartBtn = MenuItemSprite::create(Sprite::create("res/image/uires_5.png"),
                                                        Sprite::create("res/image/uires_5.png"),
                                                        NULL,
                                                        [&](Ref* ref){
                                                            log("GameOverLayer::reStart()");
                                                            isRestart = true;
                                                            
                                                            auto* sence  = BackgroundLayer::createScene();
                                                            TransitionFade *trans = TransitionFade::create(0.2f,sence);
                                                            Director::getInstance()->replaceScene(trans);
                                                        }
                                                        );
    MenuItemSprite *homeBtn = MenuItemSprite::create(Sprite::create("res/image/uires_8.png"),
                                                     Sprite::create("res/image/uires_8.png"),
                                                     [&](Ref * ref){
                                                         auto* sence  = BackgroundLayer::createScene();
                                                         
                                                         TransitionFade *trans = TransitionFade::create(0.2f,sence);
                                                         Director::getInstance()->replaceScene(trans);
                                                     });
    
    reStartBtn->setPosition(MyWinSize.width/2+reStartBtn->getContentSize().width/2,MyWinSize.height/2 +8);
    homeBtn->setPosition(MyWinSize.width/2-homeBtn->getContentSize().width/2,MyWinSize.height/2 +8);
    Menu *menu = Menu::create(reStartBtn,homeBtn,NULL);
    menu->setPosition(0,0);
    this->addChild(menu);
    return true;
}

void GameOverLayer::reStart(){
    
    log("GameOverLayer::reStart()");
    isRestart = true;
    
    auto* sence  = BackgroundLayer::createScene();
    TransitionFade *trans = TransitionFade::create(0.2f,sence);
    Director::getInstance()->replaceScene(trans);
}

void GameOverLayer::home(){
    log("GameOverLayer::home");
    log("GameOverLayer::reStart()");
    auto* sence  = BackgroundLayer::createScene();
    
    TransitionFade *trans = TransitionFade::create(0.2f,sence);
    Director::getInstance()->replaceScene(trans);
}
GameOverLayer::GameOverLayer() {
        isRestart = false;
}

GameOverLayer::~GameOverLayer() {
}

