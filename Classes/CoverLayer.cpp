//
//  CoverLayer.cpp
//  CrazyWord
//
//  Created by jintao on 14-8-6.
//
//

#include "CoverLayer.h"
#include "ComUtil.h"
USING_NS_CC;



bool CoverLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    MenuItemLabel* label = MenuItemLabel::create(LabelTTF::create("开始游戏", "黑体", 50),CC_CALLBACK_1(CoverLayer::menuStartCallback, this) );
    Menu* menu = Menu::create(label, nullptr);
    menu->setPosition(Point(COMWinSize().width,COMWinSize().height));
    this->addChild(menu);
    return true;
}

Scene* CoverLayer::createScene()
{
    Scene* scene = Scene::create();
    CoverLayer* layer = CoverLayer::create();
    scene->addChild(layer);
    return scene;
}

void CoverLayer::transitionScene()
{
    Director::getInstance()->replaceScene(nullptr);
}

void CoverLayer::menuStartCallback(Ref* pRef)
{
    
}