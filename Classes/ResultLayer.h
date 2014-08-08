//
//  ResultLayer.h
//  CrazyWord
//
//  Created by jintao on 14-8-8.
//
//

#ifndef __CrazyWord__ResultLayer__
#define __CrazyWord__ResultLayer__

#include <iostream>
#include "cocos2d.h"

class ResultLayerDelegate{
public:
    virtual void restartGame() = 0;
};

class ResultLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(ResultLayer);
    ResultLayer();
    virtual bool init();
    CC_SYNTHESIZE(ResultLayerDelegate* , _delegate, Delegate);
private:
    void menuRestart(cocos2d::Ref* pSender);
};

#endif /* defined(__CrazyWord__ResultLayer__) */
