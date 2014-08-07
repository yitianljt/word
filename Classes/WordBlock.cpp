//
//  WordBlock.cpp
//  CrazyWord
//
//  Created by jintao on 14-8-7.
//
//

#include "WordBlock.h"
USING_NS_CC;


WordBlock* WordBlock::create(cocos2d::Size size,std::string strLabel,bool isDiffWord ){
    auto word = new WordBlock();
    CCLOG("word=%s",strLabel.c_str());
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
    
    auto label = LabelBMFont::create(strLabel, "fonts/word_128.fnt");
    label->setColor(Color3B(0,0,0));
    label->setString(strLabel);
    addChild(label);
    label->setPosition(size.width/2, size.height/2);
    
    return true;
}