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

class LevelLayerDelegate{
public:
    virtual void levelNumChange(unsigned iLevel)=0;
    virtual void gameOver()=0;

};


class LevelLayer : public cocos2d::Layer
{
public:
    LevelLayer(unsigned iLevel);
    static LevelLayer* create(unsigned int iLevel);
    virtual bool init();
    virtual void onEnter();
    CC_SYNTHESIZE(unsigned int , _levelNum, LevelNum);
    CC_SYNTHESIZE(LevelLayerDelegate*, _delegate, Delegate);
private:
    void createBlocks(int rows);
    void updateCount(float ft);
    void nextLevel();
    void gameOver();
    void parseJson();
    cocos2d::LabelTTF* _ttfCountDown;
    cocos2d::LabelTTF* _ttfLevel;
    int _countDown;
    CC_SYNTHESIZE(std::string, _normalWord, NormalWord);
    CC_SYNTHESIZE(std::string, _wrongWord, WrongWord);
    std::vector<WordBlock*>* _vecBlocks;
    std::vector<Question>* _vecEasyQuestion;
    std::vector<Question>* _vecMedQuestion;
    std::vector<Question>* _vecQuestion;
};

#endif /* defined(__CrazyWord__LevelLayer__) */
