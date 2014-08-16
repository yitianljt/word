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
#include "LevelLayer.h"
#include "ResultLayer.h"

class MainLayer : public cocos2d::Layer,
                  public LevelLayerDelegate,
                  public ResultLayerDelegate
{
public:
    MainLayer();
    ~MainLayer();
    CREATE_FUNC(MainLayer);
    virtual bool init();
    static cocos2d::Scene* CreateScene();
    virtual void onKeyPressed();
    

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    //virtual void keyBackClicked();//Android 返回键
#endif
    void levelNumChange(unsigned iLevel);
    void restartGame();
    void gameOver();
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode,cocos2d::Event * pEvent);

private:
    void startGame();
    CC_SYNTHESIZE(unsigned int , _levelNum, LevelNum);
    LevelLayer* _layerLevel;
    ResultLayer* _resultLayer;
    
    
};

#endif /* defined(__CrazyWord__MainLayer__) */
