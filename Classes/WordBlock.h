//
//  WordBlock.h
//  CrazyWord
//
//  Created by jintao on 14-8-7.
//
//

#ifndef __CrazyWord__WordBlock__
#define __CrazyWord__WordBlock__

#include <iostream>
#include "cocos2d.h"

class WordBlock : public cocos2d::Sprite
{
public:
    static WordBlock* create(cocos2d::Size,std::string strLabel,bool isDiffWord );
    virtual bool init(cocos2d::Size,std::string strLabel,bool isDiffWord);
private:
    bool _isDiffWord;
    
};

#endif /* defined(__CrazyWord__WordBlock__) */
