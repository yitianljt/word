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

typedef enum {
    kStartTag
}kMenuTag;

class CoverLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(CoverLayer);
    virtual bool init();
    static cocos2d::Scene* createScene();
    int iKeyCount ;
    time_t oldTime;
private:
    void transitionScene();
    void onClick(cocos2d::Ref* pRef);
    virtual void onKeyPressed();

};

#endif /* defined(__CrazyWord__CoverLayer__) */
