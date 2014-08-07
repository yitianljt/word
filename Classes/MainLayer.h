//
//  MainLayer.h
//  CrazyWord
//
//  Created by jintao on 14-8-6.
//
//

#ifndef __CrazyWord__MainLayer__
#define __CrazyWord__MainLayer__

#include <iostream>
#include "cocos2d.h"

class MainLayer : public cocos2d::Layer
{
public:
    MainLayer();
    ~MainLayer();
    CREATE_FUNC(MainLayer);
    virtual bool init();
    static cocos2d::Scene* CreateScene();
private:
    CC_SYNTHESIZE(unsigned int , _levelNum, LevelNum);
    void startGame();
    void updateCount(float ft);
    cocos2d::LabelTTF* _ttfCountDown;
    cocos2d::LabelTTF* _ttfLevel;
    int _countDown;
    
};

#endif /* defined(__CrazyWord__MainLayer__) */
