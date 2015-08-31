//
//  BackgroundLayer.cpp
//  StickHero
//
//  Created by 胡振生 on 15/8/26.
//
//

#include "BackgroundLayer.h"
#include "GameOverLayer.h"

using namespace CocosDenshion;


Scene* BackgroundLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = BackgroundLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool BackgroundLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    
    
    
    MyWinSize = Director::getInstance()->getWinSize();
    /**
     * 闅忔満璁剧疆澹佺焊
     */
    int randomNumber = CCRANDOM_0_1()*10;
    int bgNumber = randomNumber % 5;
    switch (bgNumber) {
        case 0:
            Image_One = Sprite::create("res/image/bg/bg1.jpg");
            Image_Two = Sprite::create("res/image/bg/bg1.jpg");
            break;
        case 1:
            Image_One = Sprite::create("res/image/bg/bg2.jpg");
            Image_Two = Sprite::create("res/image/bg/bg2.jpg");
            break;
        case 2:
            Image_One = Sprite::create("res/image/bg/bg3.jpg");
            Image_Two = Sprite::create("res/image/bg/bg3.jpg");
            break;
        case 3:
            Image_One = Sprite::create("res/image/bg/bg4.jpg");
            Image_Two = Sprite::create("res/image/bg/bg4.jpg");
            break;
        case 4:
            Image_One = Sprite::create("res/image/bg/bg5.jpg");
            Image_Two = Sprite::create("res/image/bg/bg5.jpg");
            break;
        default:
            break;
    }
    
    Image_One->setPosition(MyWinSize.width / 2, MyWinSize.height / 2);
    Image_Two->setPosition(
                           MyWinSize.width / 2 + Image_Two->getContentSize().width,
                           MyWinSize.height / 2);
    
    this->addChild(Image_One, 1);
    this->addChild(Image_Two, 1);
    
    GameName = Sprite::create("res/image/uires_1.png");
    GameName->setPosition(MyWinSize.width / 2, MyWinSize.height - GameName->getContentSize().height);
    this->addChild(GameName, 2);
    
    auto startBtn = MenuItemSprite::create(
                                           Sprite::create("res/image/uires_2.png"),
                                           Sprite::create("res/image/uires_2.png"), NULL,
                                           CC_CALLBACK_1(BackgroundLayer::Start,this));
    startBtn->setName("startBtn");
    startBtn->setPosition(MyWinSize.width / 2, MyWinSize.height / 2 + 8);
    auto startBtnMoveDown = MoveTo::create(1,
                                           Vec2(MyWinSize.width / 2, MyWinSize.height / 2 - 18));
    auto startBtnMoveUp = MoveTo::create(1,
                                         Vec2(MyWinSize.width / 2, MyWinSize.height / 2 + 15));
    auto startMoveSeq = Sequence::create(startBtnMoveDown, startBtnMoveUp,
                                         NULL);
    auto startMoveRepeat = RepeatForever::create(startMoveSeq);
    startBtn->runAction(startMoveRepeat);
    menu = Menu::create(startBtn, NULL);
    menu->setPosition(0, 0);
    
    this->addChild(menu, 2);
    
    /*
     * 初始化 stage
     */
    for (int i = 0; i < 3; i++) {
        stageSprite[i] = Sprite::create("res/image/stage.png");
    }
    stageSprite[0]->setScaleX(30); // X 轴拉伸
    
    // 设置 stage 的初始化位置
    for (int i = 1; i < 3; i++) {
        stageSprite[i]->setPosition(
                                    Vec2(MyWinSize.width+ stageSprite[i]->getScaleX()* stageSprite[i]->getContentSize().width,
                                         stageSprite[i]->getContentSize().height / 2));
    }
    
    stageSprite[0]->setPosition(
                                Vec2(MyWinSize.width / 2,
                                     stageSprite[0]->getContentSize().height / 4));
    
    for (int i = 0; i < 3; i++) {
        this->addChild(stageSprite[i], 3);
    }
    
    /**
     * 添加触摸监听器并注册
     */
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(false);
    touchListener->onTouchBegan = CC_CALLBACK_2(BackgroundLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(BackgroundLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(BackgroundLayer::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(BackgroundLayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    /**
     * 添加palyer并初始化
     */
    player = new Player();
    player->init();
    player->getPlayer()->setPosition(Vec2(MyWinSize.width/2,stageSprite[0]->getContentSize().height/4*3));
    this->addChild(player->getPlayer(),10);
    player->Stay();
    
    stick = Sprite::create("res/image/stick.png");
    stick->setAnchorPoint(Vec2(0.5,0));
    stick->setPosition(-stick->getContentSize().width,-stick->getContentSize().height);
    this->addChild(stick,5);
    
    
    if (isRestart) {
        Start(NULL);
    }
    
    return true;
}
void BackgroundLayer::Start(Ref* pSender) {
    
    log("%s","BackgroundLayer::Start()");
    isStart=true;//代表游戏开始
    
    this->removeChild(menu);
    this->removeChild(GameName);
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    scoreTitle = Label::createWithBMFont("fonts/bitmapFontChinese.fnt","0");
    // scoreTitle->setSystemFontSize(30);
    // scoreTitle = Label::createWithTTF(toStr, "fonts/arial.ttf", 50);
    // scoreTitle = Label::createWithTTF(toStr, "fonts/Marker Felt.ttf", 50);
    scoreTitle->setPosition(Vec2(MyWinSize.width/2,MyWinSize.height/4*3));
    this->addChild(scoreTitle, 1);
    
    auto stageMove = MoveTo::create(0.2,Vec2(100, stageSprite[0]->getContentSize().height / 2));
    stageSprite[0]->runAction(stageMove);
    
    
    player->getPlayer()->runAction(MoveTo::create(0.2,Vec2(100, stageSprite[0]->getContentSize().height)));
    
    StickPoint=Vec2(100+stageSprite[0]->getScaleX()* stageSprite[0]->getContentSize().width/2, stageSprite[0]->getContentSize().height);
    
    addStage();
    //
}

void BackgroundLayer::addStage() {
    
    log("%s","BackgroundLayer::addStage()---->");
    
    stageSprite[stageNumber]->setScaleX(10 + CCRANDOM_0_1()*40);
    stageSprite[stageNumber]->setPosition(
                                          Vec2(MyWinSize.width+ stageSprite[stageNumber]->getScaleX()* stageSprite[stageNumber]->getContentSize().width,
                                               stageSprite[stageNumber]->getContentSize().height / 2));
    
    auto random = MyWinSize.width / 2 +CCRANDOM_0_1()*MyWinSize.width/3;
    auto stageMove = MoveTo::create(0.2,
                                    Vec2(random , stageSprite[stageNumber]->getContentSize().height/2));
    
    stageSprite[stageNumber]->runAction(stageMove);
    
    if (stageNumber + 1 <= 2) {
        stageNumber += 1;
    } else {
        stageNumber = 0;
    }
}
void BackgroundLayer::stageMove() {
    
    log("BackgroundLayer::stageMove()-->stageNumber:%d",stageNumber);
    
    /**
     * 停止背景移动
     */
    this->unschedule(schedule_selector(BackgroundLayer::bgMove));
    
    /*
     * 停止音效
     */
    SimpleAudioEngine::getInstance()->pauseEffect(kickId);
    NowStage = stageNumber == 0 ? 2 : stageNumber - 1;
    LastStage = NowStage == 0 ? 2 : (NowStage - 1);
    NextStage = NowStage == 2 ? 0 : (NowStage + 1);
    MoveTo* nowStageMove = MoveTo::create(0.2,Vec2(100, stageSprite[0]->getContentSize().height / 2));
    stageSprite[NowStage]->runAction(nowStageMove);
    MoveTo* lastStageMove = MoveTo::create(0.2,
                                           Vec2(-stageSprite[LastStage]->getContentSize().width * stageSprite[LastStage]->getScaleX(),
                                                stageSprite[0]->getContentSize().height / 2));
    stageSprite[LastStage]->runAction(lastStageMove);
    
    
    StickPoint = Vec2(100+stageSprite[NowStage]->getScaleX()*stageSprite[NowStage]->getContentSize().width/2,
                      stageSprite[0]->getContentSize().height);
    initStick();
    
    /*
     *同步player和stick的位置
     */
    player->getPlayer()->runAction(MoveTo::create(0.2,Vec2(100, stageSprite[0]->getContentSize().height )));
    addStage();
    successFlag = false;//设置successFlag
}

bool BackgroundLayer::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    log("%s","BackgroundLayer::onTouchBegan()");
    if(isStart){
        addStick();
    }
    return true;
}
void BackgroundLayer::onTouchMoved(Touch* pTouch, Event* pEvent)
{
}

void BackgroundLayer::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    if(isStart){
        StopStick();//stick停止变长
        RotateStickAndGo();//stick 开始旋转
    }
}

void BackgroundLayer::addStick()
{
    log("%s","BackgroundLayer::addStick()");
    stick->setScaleY(1);//初始化stck长度
    stick->setRotation(0);
    stick->setPosition(StickPoint);//初始化stick位置
    this->schedule(schedule_selector(BackgroundLayer::StickLength));
}

void BackgroundLayer::StickLength(float)
{
    //log("%s","BackgroundLayer::StickLength()");
    stick->setScaleY(stick->getScaleY()+STICK_SPEED);
}
void BackgroundLayer::StopStick()
{
    log("%s","BackgroundLayer::StopStick()");
    TouchLength = stick->getContentSize().height*stick->getScaleY();
    this->unschedule(schedule_selector(BackgroundLayer::StickLength));
}

void BackgroundLayer::RotateStickAndGo(){
    //	DestLengthMin = abs(stageSprite[LastStage]->getPositionX() - stageSprite[NowStage]->getPositionX()) - stageSprite[LastStage]->getContentSize().width*stageSprite[LastStage]->getScaleX()/2 - stageSprite[NowStage]->getContentSize().width*stageSprite[NowStage]->getScaleX()/2;
    DestLengthMin = std::abs(stageSprite[NextStage]->getPositionX() - stageSprite[NowStage]->getPositionX()) - stageSprite[NextStage]->getContentSize().width*stageSprite[NextStage]->getScaleX()/2 - stageSprite[NowStage]->getContentSize().width*stageSprite[NowStage]->getScaleX()/2;
    
    DestLengthMax = DestLengthMin + stageSprite[NextStage]->getContentSize().width*stageSprite[NextStage]->getScaleX();
    RotateTo* Ro_Stick = RotateTo::create(1, 90); //旋转90度
    
    log("ToTouchLength:%f,DestLengthMin:%f,DestLengthMax:%f",TouchLength,DestLengthMin,DestLengthMax);
    
    Ro_Stick->setTag(1);
    if(TouchLength<DestLengthMin || TouchLength > DestLengthMax)
    {
        successFlag=false;
    }
    else if(TouchLength >= DestLengthMin && TouchLength <=DestLengthMax)
    {
        scoreCount++;//记录分数
        successFlag=true;
    }
    
    log("BackgroundLayer::RotateStickAndGo()-->NextStage:%d",NextStage);
    log("BackgroundLayer::RotateStickAndGo()-->%d",successFlag);
    
    FiniteTimeAction *actionN ;
    if(successFlag==true){
        actionN= Sequence::create(Ro_Stick,
                                  CallFuncN::create(CC_CALLBACK_0(BackgroundLayer::stickCallBack,this,successFlag)),
                                  NULL);
        
    }else{
        actionN= Sequence::create(Ro_Stick,
                                  CallFuncN::create(CC_CALLBACK_0(BackgroundLayer::stickCallBack,this,successFlag)),
                                  NULL);
    }
    
    stick->runAction(actionN);
}

void BackgroundLayer::stickCallBack(bool successFlag){
    
    
    kickId = SimpleAudioEngine::getInstance()->playEffect("res/sound/kick.ogg",true);
    
    if(successFlag==true){
        
        auto playMove = MoveTo::create(0.2,Vec2( stageSprite[NextStage]->getPositionX(),stageSprite[NextStage]->getContentSize().height));
        player->Stop();
        player->Walk();
        auto playSeq  =Sequence::create(playMove,
                                        CallFuncN::create(CC_CALLBACK_0(BackgroundLayer::stageMove,this)),NULL);
        player->getPlayer()->runAction(playSeq);
        /*
         *停止背景移动
         */
        this->schedule(schedule_selector(BackgroundLayer::bgMove));
        
        /*
         * 移动之后，修改分数
         */
        scoreTitle->setString(StringUtils::toString(scoreCount));
    }else{
        auto playPoint = Vec2(
                              stageSprite[NowStage]->getPositionX()
                              + stageSprite[NowStage]->getContentSize().width*stageSprite[NowStage]->getScaleX()/2
                              + TouchLength
                              + player->getPlayer()->getContentSize().width/3,
                              stageSprite[NextStage]->getContentSize().height
                              );
        //player掉落后的位置
        auto playerDownPoint = Vec2(
                                    stageSprite[NowStage]->getPositionX()
                                    + stageSprite[NowStage]->getContentSize().width*stageSprite[NowStage]->getScaleX()/2
                                    + TouchLength
                                    + player->getPlayer()->getContentSize().width/3,
                                    -70);
        auto playerMove = MoveTo::create(0.2,playPoint);
        auto playerDown = MoveTo::create(0.3,playerDownPoint);
        auto playerSeq = Sequence::create(playerMove,
                                          playerDown,
                                          NULL);
        player->getPlayer()->runAction(playerSeq);
        
        RotateTo* RoDown_Stick = RotateTo::create(0.7,180);
        stick->runAction(RoDown_Stick);
        
        gameOver();
        
    }
}

void BackgroundLayer::initStick(){
    
    log("BackgroundLayer::initStick()");
    stick->setScaleY(1);//初始化stick长度
    stick->setRotation(0);
    stick->setPosition(StickPoint);
}

void BackgroundLayer::stopAudio(int audioId){
    
}

void BackgroundLayer::bgMove(float){
    
    log("BackgroundLayer::bgMove()-->");
    
    int x1 = Image_One->getPositionX();
    int x2 = Image_Two->getPositionX();
    x1 -= BG_SPEED;
    x2 -= BG_SPEED;
    Size size = Image_One->getContentSize();
    if (x1 < -size.width / 2) {
        x2 = size.width / 2;
        x1 = size.width / 2 + size.width;
    }
    if (x2 < -size.width / 2) {
        x1 = size.width / 2;
        x2 = size.width / 2 + size.width;
    }
    Image_One->setPositionX(x1);
    Image_Two->setPositionX(x2);
    
}
void BackgroundLayer::gameOver(){
    /*
     * 游戏结束，添加结束界面
     */
    
    gameOverLayer = GameOverLayer::create();
    auto callback = [](Touch * ,Event *)
    {
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,gameOverLayer);

    this->addChild(gameOverLayer,8);
    
}
BackgroundLayer::BackgroundLayer(){
    isStart = false;
    stageNumber=1;//设置第一个stage为1
    NowStage=0;//player所在stage
    LastStage=2;//player上一个stage
    NextStage=1;//player下一个stage
    scoreCount=0;
    successFlag=false;//true 移动成功的标志
    moveComplete=false;//true 移动完成的标志
    
}
BackgroundLayer::~BackgroundLayer(){
    delete player;
}


