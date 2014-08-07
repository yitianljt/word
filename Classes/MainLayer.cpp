//
//  MainLayer.cpp
//  CrazyWord
//
//  Created by jintao on 14-8-6.
//
//

#include "MainLayer.h"
#include "ComUtil.h"
USING_NS_CC;


MainLayer::MainLayer()
{
    setLevelNum(1);
    _countDown = 60;
}

MainLayer::~MainLayer()
{
    
}

bool MainLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    LayerColor* layerColor = LayerColor::create(Color4B(30,170,200,255), COMWinSize().width, COMWinSize().height);
    addChild(layerColor);
    __String* strLevel = __String::createWithFormat("第%d层/99层",getLevelNum());
    _ttfLevel = LabelTTF::create(strLevel->getCString(), "黑体", 30);
    _ttfLevel->setPosition(Point(COMWinSize().width/2,COMWinSize().height*0.9));
    layerColor->addChild(_ttfLevel);
    
    __String* strCount = __String::createWithFormat("%d秒",_countDown);
    _ttfCountDown = LabelTTF::create(strCount->getCString(), "黑体", 40);
    _ttfCountDown->setPosition(_ttfLevel->getPosition()+Point(0,-_ttfLevel->getContentSize().height/2-40));
    layerColor->addChild(_ttfCountDown);
    startGame();
    return true;
}

Scene* MainLayer::CreateScene()
{
    Scene* scene = Scene::create();
    MainLayer* layer = MainLayer::create();
    scene->addChild(layer);
    
    return  scene;
}

void MainLayer::startGame()
{
    schedule(schedule_selector(MainLayer::updateCount), 1.0f);
}

void MainLayer::updateCount(float ft)
{
    _countDown--;
    if (_countDown<=0) {
        unschedule(schedule_selector(MainLayer::updateCount));
    }
    __String* strCount = __String::createWithFormat("%d秒",_countDown);
    _ttfCountDown->setString(strCount->getCString());
    
    
}

