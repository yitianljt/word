//
//  CoverLayer.h
//  CrazyWord
//
//  Created by jintao on 14-8-6.
//
//

#ifndef __CrazyWord__CoverLayer__
#define __CrazyWord__CoverLayer__

#include <iostream>
#include "cocos2d.h"

class CoverLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(CoverLayer);
    virtual bool init();
    static cocos2d::Scene* createScene();
private:
    void transitionScene();
    void menuStartCallback(cocos2d::Ref* pRef);

};

#endif /* defined(__CrazyWord__CoverLayer__) */
