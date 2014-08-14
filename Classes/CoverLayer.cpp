//
//  CoverLayer.cpp
//  CrazyWord
//
//  Created by jintao on 14-8-6.
//
//

#include "CoverLayer.h"
#include "ComUtil.h"
#include "MainLayer.h"
#include "ShowYouAd.h"
USING_NS_CC;



bool CoverLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    LayerColor* layerColor = LayerColor::create(Color4B(30,170,200,255), COMWinSize().width, COMWinSize().height);
    addChild(layerColor);
    
    LabelTTF* ttfTitle = LabelTTF::create("亮瞎系列", "黑体", FONTSIZE(100));
    ttfTitle->setPosition(Point(COMWinSize().width/2,COMWinSize().height*0.7));
    addChild(ttfTitle);
    
    Sprite* spNormal = Sprite::create("image/btn_start.png");
    Sprite* spSelect = Sprite::create("image/btn_start.png");
//    spNormal->setScale(960/COMWinSize().height);
//    spSelect->setScale(960/COMWinSize().height);
    spSelect->setColor(Color3B(200,200,200));
    
    MenuItemSprite* itemSp = MenuItemSprite::create(spNormal, spSelect, CC_CALLBACK_1(CoverLayer::onClick, this));
    
    //MenuItemLabel* label = MenuItemLabel::create(LabelTTF::create("开始游戏", "黑体", 60),CC_CALLBACK_1(CoverLayer::onClick, this) );
    itemSp->setTag(kStartTag);
    Menu* menu = Menu::create(itemSp, nullptr);
    menu->setPosition(Point(COMWinSize().width/2,COMWinSize().height/2));
    this->addChild(menu);
    
   // ShowYouAd::shared()->showYouWallSpot();
    //ShowYouAd::shared()->showSpots();
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
    Director::getInstance()->replaceScene(TransitionFade::create(0.5,MainLayer::CreateScene()));
}

void CoverLayer::onClick(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Button.mp3");
    Node* node = (Node*)pSender;
    switch (node->getTag()) {
        case kStartTag:
            transitionScene();
            break;
        default:
            break;
    }
}