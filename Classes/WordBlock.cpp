//
//  WordBlock.cpp
//  CrazyWord
//
//  Created by jintao on 14-8-7.
//
//

#include "WordBlock.h"
#include "cocos-ext.h"
#include "PlayRound.h"
USING_NS_CC;
USING_NS_CC_EXT;


WordBlock* WordBlock::create(cocos2d::Size size,std::string strLabel,bool isDiffWord ){
    auto word = new WordBlock();
    if (word && word->init(size,strLabel,isDiffWord)) {
        word->autorelease();
        return word;
    }
    else
    {
        delete word;
        word = nullptr;
        return nullptr;
    }
}

bool WordBlock::init(Size size,std::string strLabel,bool isDiffWord)
{
    if (!Sprite::init())
    {
        return false;
    }
    _isDiffWord = isDiffWord;
    setContentSize(size);
    setAnchorPoint(Point::ZERO);
    setTextureRect(Rect(0,0,size.width,size.height));
    
    Scale9Sprite* leftBorder = Scale9Sprite::create("image/border.png");
    leftBorder->setRotation(180);
    leftBorder->setContentSize(Size(6,size.height));
    leftBorder->setPosition(Point(0,size.height/2));
    Scale9Sprite* rightBorder = Scale9Sprite::create("image/border.png");
    rightBorder->setRotation(180);
    rightBorder->setContentSize(Size(6,size.height));
    rightBorder->setPosition(Point(size.width,size.height/2));
    Scale9Sprite* upBorder = Scale9Sprite::create("image/border.png");
    upBorder->setContentSize(Size(size.width,6));
    upBorder->setPosition(Point(size.width/2,size.height));
    Scale9Sprite* downBorder = Scale9Sprite::create("image/border.png");
    downBorder->setContentSize(Size(size.width,6));
    downBorder->setPosition(Point(size.width/2,0));
    this->addChild(leftBorder);
    this->addChild(rightBorder);
    this->addChild(upBorder);
    this->addChild(downBorder);
    __String* strFont;
    if (PlayRound::shared()->getLevel()<=4) {
        strFont = __String::create("fonts/word_128.fnt");
    }
    else
    {
        strFont = __String::create("fonts/word_64.fnt");
    }
    auto label = LabelBMFont::create(strLabel, strFont->getCString());
    label->setColor(Color3B(0,0,0));
    label->setString(strLabel);
    addChild(label);
    label->setScale(size.width*0.8/label->getContentSize().width);
    label->setPosition(size.width/2, size.height/2);
    return true;
}