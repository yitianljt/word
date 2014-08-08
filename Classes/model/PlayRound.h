//
//  PlayRound.h
//  CrazyWord
//
//  Created by jintao on 14-8-8.
//
//

#ifndef __CrazyWord__PlayRound__
#define __CrazyWord__PlayRound__

#include <iostream>
#include "Common.h"
#include "cocos2d.h"

class PlayRound{
    SINGLETON(PlayRound);
    ~PlayRound();
public:
    void newRound();
    const char* getPrivityDescription(unsigned int aPrivity);
    CC_SYNTHESIZE(unsigned int , _level, Level);
    CC_SYNTHESIZE(int , _count , Count);
    
    
private:
    cocos2d::__Array*  _privityDescriptions;
    
};


#endif /* defined(__CrazyWord__PlayRound__) */
