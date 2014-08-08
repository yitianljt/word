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
USING_NS_CC;
USING_NS_CC_EXT;


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
    //LabelTTF* labelDes = LabelTTF::create(PlayRound::shared()->getPrivityDescription(PlayRound::shared()->getLevel()), "黑体", 30);
    LabelTTF* labelDes = LabelTTF::create(PlayRound::shared()->getPrivityDescription(0), "黑体", 30);
    labelDes->setPosition(Point(COMWinSize().width/2,COMWinSize().height*0.8));
    addChild(labelDes);
    
    __String* strLevel = __String::createWithFormat("我到了第%d层啦!",PlayRound::shared()->getLevel());
    LabelTTF* labelLevel = LabelTTF::create(strLevel->getCString(), "黑体", 40);
    labelLevel->setPosition(Point(COMWinSize().width/2,COMWinSize().height*0.7));
    addChild(labelLevel);

    MenuItemLabel* label = MenuItemLabel::create(LabelTTF::create("重新开始", "黑体", 50),CC_CALLBACK_1(ResultLayer::menuRestart, this) );
    Menu* menu = Menu::create(label, nullptr);
    menu->setPosition(Point(COMWinSize().width/2,COMWinSize().height/2));
    this->addChild(menu);
    //reach level
    return true;
}


void ResultLayer::menuRestart(cocos2d::Ref* pSender)
{
    if (getDelegate())
    {
        getDelegate()->restartGame();
    }
}
