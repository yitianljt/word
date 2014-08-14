//
//  ResultLayer.cpp
//  CrazyWord
//
//  Created by jintao on 14-8-8.
//
//

#include "ResultLayer.h"
#include "PlayRound.h"
#include "ComUtil.h"
#include "cocos-ext.h"
#include "ShowYouAd.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

#define FONTSIZE(__SIZE__)  (__SIZE__/960.0)*COMWinSize().height

ResultLayer::ResultLayer()
{
    setDelegate(nullptr);
}
bool ResultLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    //des
    LabelTTF* labelDes = LabelTTF::create(PlayRound::shared()->getPrivityDescription(PlayRound::shared()->getLevel()), "黑体", FONTSIZE(25));
    //LabelTTF* labelDes = LabelTTF::create(PlayRound::shared()->getPrivityDescription(0), "黑体", 30);
    labelDes->setPosition(Point(COMWinSize().width/2,COMWinSize().height*0.9));
    addChild(labelDes);
    
    __String* strLevel = __String::createWithFormat("我到了第%d层啦!",PlayRound::shared()->getLevel());
    LabelTTF* labelLevel = LabelTTF::create(strLevel->getCString(), "黑体", FONTSIZE(40));
    labelLevel->setPosition(Point(COMWinSize().width/2,COMWinSize().height*0.8));
    addChild(labelLevel);

    Sprite* spNormal = Sprite::create("image/btn_restart.png");
    Sprite* spSelect = Sprite::create("image/btn_restart.png");
    spSelect->setColor(Color3B(200,200,200));
    
    MenuItemSprite* itemSp = MenuItemSprite::create(spNormal, spSelect, CC_CALLBACK_1(ResultLayer::onClick, this));
    //MenuItemLabel* label = MenuItemLabel::create(LabelTTF::create("重新开始", "黑体", 50),CC_CALLBACK_1(ResultLayer::onClick, this) );
    itemSp->setTag(kResultRestartTag);
    Menu* menu = Menu::create(itemSp, nullptr);
    menu->setPosition(Point(COMWinSize().width/2,COMWinSize().height/2));
    this->addChild(menu);
    if (CCRANDOM_0_1()>0.8)
    {
        ShowYouAd::shared()->showYouWallSpot();
    }
    //Results.m4a
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Results.m4a");
    //历史分数
    __String* strHistory;

    int iHistory = UserDefault::getInstance()->getIntegerForKey("HistoryScore");
    if (iHistory<PlayRound::shared()->getLevel()) {
        iHistory = PlayRound::shared()->getLevel();
        UserDefault::getInstance()->setIntegerForKey("HistoryScore", PlayRound::shared()->getLevel());
        UserDefault::getInstance()->flush();
        strHistory = __String::createWithFormat("打破记录啦:%d层!!!",iHistory);

    }
    else
    {
        strHistory = __String::createWithFormat("历史最高:%d层",iHistory);
    }
    LabelTTF* ttfHistory = LabelTTF::create(strHistory->getCString(), "黑体", FONTSIZE(50));
    ttfHistory->setPosition(Point(COMWinSize().width/2,COMWinSize().height*0.7));
    addChild(ttfHistory);
    return true;
}

void ResultLayer::onClick(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Button.mp3");
    Node* node = (Node*)pSender;
    switch (node->getTag()) {
        case kResultRestartTag:
            if (getDelegate())
            {
                getDelegate()->restartGame();
            }
            break;
            
        default:
            break;
    }
    
}
