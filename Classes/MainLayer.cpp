//
//  MainLayer.cpp
//  CrazyWord
//
//  Created by jintao on 14-8-6.
//
//

#include "MainLayer.h"
#include "ComUtil.h"
#include "PlayRound.h"
USING_NS_CC;


MainLayer::MainLayer()
{
    setLevelNum(1);
    _layerLevel = nullptr;
    _resultLayer = nullptr;
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
    PlayRound::shared()->newRound();
    _levelNum = 1;
    if (_layerLevel) {
        _layerLevel->removeFromParent();
        _layerLevel = nullptr;
    }
    _layerLevel = LevelLayer::create(_levelNum);
    _layerLevel->setDelegate(this);
    this->addChild(_layerLevel);
}

void MainLayer::gameOver()
{
    if (_layerLevel) {
        _layerLevel->removeFromParent();
        _layerLevel = nullptr;
    }
    //show result
    if (_resultLayer) {
        _resultLayer->removeFromParent();
        _resultLayer = nullptr;
    }
    _resultLayer = ResultLayer::create();
    _resultLayer->setDelegate(this);
    addChild(_resultLayer);
}

void MainLayer::levelNumChange(unsigned iLevel)
{
    
}

void MainLayer::restartGame()
{
    if (_resultLayer) {
        _resultLayer->removeFromParent();
        _resultLayer = nullptr;
    }
    this->startGame();
}