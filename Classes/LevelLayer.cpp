//
//  LevelLayer.cpp
//  CrazyWord
//
//  Created by jintao on 14-8-7.
//
//

#include "LevelLayer.h"
#include "ComUtil.h"
USING_NS_CC;
using namespace std;


LevelLayer::LevelLayer(unsigned int iLevel)
{
    setLevelNum(iLevel);
    _vecBlocks = nullptr;
    setNormalWord("二");
    setWrongWord("大");
}

LevelLayer* LevelLayer::create(unsigned int iLevel)
{
    LevelLayer *pRet = new LevelLayer(iLevel);
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}


bool LevelLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    return true;
}


void LevelLayer::onEnter()
{
    Layer::onEnter();
    if (getLevelNum()<=3) {
        int row=2;
        createBlocks(row);
    }
    
}

void LevelLayer::createBlocks(int rows)
{
    _vecBlocks = new vector<WordBlock>();
    float cellWidth = (COMWinSize().width-40)/(rows*1.0);
    CCLOG("cellWidth=%f",cellWidth);
    
    float startX = COMWinSize().width/2-(rows/2)*cellWidth;
    float startY = COMWinSize().height/2-(rows/2-1)*cellWidth;
    
    CCLOG("startX=%f,startY=%f",startX,startY);

    
    int iRandNum = rand()%(rows*rows);
    
    for (int i=0;i<rows*rows; i++) {
        WordBlock* block = WordBlock::create(Size(cellWidth,cellWidth), i==iRandNum?getWrongWord():getNormalWord(),i==iRandNum);
        block->setPosition(Point(startX,startY)+Point((i/rows)*cellWidth,-(i%rows)*cellWidth));
        addChild(block);
    }
    
    
}
