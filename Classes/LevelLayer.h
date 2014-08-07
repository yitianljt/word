//
//  LevelLayer.h
//  CrazyWord
//
//  Created by jintao on 14-8-7.
//
//

#ifndef __CrazyWord__LevelLayer__
#define __CrazyWord__LevelLayer__

#include <iostream>
#include "cocos2d.h"
#include "WordBlock.h"


class LevelLayer : public cocos2d::Layer
{
public:
    LevelLayer(unsigned iLevel);
    static LevelLayer* create(unsigned int iLevel);
    virtual bool init();
    virtual void onEnter();
    CC_SYNTHESIZE(unsigned int , _levelNum, LevelNum);
private:
    void createBlocks(int rows);
    std::vector<WordBlock>* _vecBlocks;
    CC_SYNTHESIZE(std::string, _normalWord, NormalWord);
    CC_SYNTHESIZE(std::string, _wrongWord, WrongWord);
};

#endif /* defined(__CrazyWord__LevelLayer__) */
