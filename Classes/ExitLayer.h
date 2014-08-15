//
//  ExitLayer.h
//  CrazyWord
//
//  Created by jintao on 14-8-15.
//
//

#ifndef __CrazyWord__ExitLayer__
#define __CrazyWord__ExitLayer__

#include <iostream>
#include "cocos2d.h"

class ExitLayer:public cocos2d::Layer
{
public:
    CREATE_FUNC(ExitLayer);
    virtual bool init();
    void showIn();
    void showOut();
    void onKeyPressed();

private:
    cocos2d::Sprite *_window;
	cocos2d::Menu *_menu;
	std::function<void(void)> _yesCall;
	std::function<void(void)> _noCall;
	void onYesButtonTouch(cocos2d::Ref *aSender);
	void onNoButtonTouch(cocos2d::Ref *aSender);
};


#endif /* defined(__CrazyWord__ExitLayer__) */
