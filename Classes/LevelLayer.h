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


struct Question{
    std::string strNormal;
    std::string strDiff;
};

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
    void nextLevel();
    void parseJson();
    CC_SYNTHESIZE(std::string, _normalWord, NormalWord);
    CC_SYNTHESIZE(std::string, _wrongWord, WrongWord);
    std::vector<WordBlock*>* _vecBlocks;
    std::vector<Question>* _vecEasyQuestion;
    std::vector<Question>* _vecMedQuestion;
    std::vector<Question>* _vecQuestion;
};

#endif /* defined(__CrazyWord__LevelLayer__) */
