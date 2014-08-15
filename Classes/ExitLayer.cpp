//
//  ExitLayer.cpp
//  CrazyWord
//
//  Created by jintao on 14-8-15.
//
//

#include "ExitLayer.h"
#include "ComUtil.h"
USING_NS_CC;


bool ExitLayer::init()
{
	Layer::init();
	
	
	_window = CCSprite::create("res/image/tp_exit_bg.png");
	_window->setPosition(Point(COMWinSize().width/2,COMWinSize().height/2));
	this->addChild(_window);
	
	Sprite *yesNormal_ = Sprite::create("res/image/tp_exit_yes_normal.png");
	Sprite *yesSelected_ = Sprite::create("res/image/tp_exit_yes_selected.png");
	MenuItemSprite *yes_ = MenuItemSprite::create(yesNormal_,yesSelected_,this,
													  menu_selector(ExitLayer::onYesButtonTouch));
	Sprite *noNormal_ = Sprite::create("res/image/tp_exit_no_normal.png");
	Sprite *noSelected_ = Sprite::create("res/image/tp_exit_no_selected.png");
	MenuItemSprite *no_ = MenuItemSprite::create(noNormal_,noSelected_,this,
													 menu_selector(ExitLayer::onNoButtonTouch));
	
	_menu = CCMenu::create(yes_,no_,NULL);
	_menu->alignItemsHorizontallyWithPadding(50);
	_menu->setTouchEnabled(false);
	_window->addChild(_menu);
	
	this->setVisible(false);
	this->setKeypadEnabled(true);
	return true;
}

void ExitLayer::showIn()
{

	this->setVisible(true);
	_window->setScale(0);
	ScaleTo *scale_ = CCScaleTo::create(0.3,1);
	EaseBackOut *ease_ = CCEaseBackOut::create(scale_);
	Action *sequence_ = CCSequence::create(ease_,NULL);
	_window->runAction(sequence_);
}

void ExitLayer::onKeyPressed()
{
	Layer::keyBackClicked();
	CCLOG("点击退出按钮");
	if (this->isVisible())
	{
		this->showOut();
	}else{

	}
}

void ExitLayer::showOut()
{
	_menu->setTouchEnabled(false);
	CCScaleTo *scale_ = CCScaleTo::create(0.3,0);
	CCEaseBackIn *ease_ = CCEaseBackIn::create(scale_);
	CCAction *sequence_ = CCSequence::create(ease_,NULL);
	_window->runAction(sequence_);
}

void ExitLayer::onYesButtonTouch(CCObject *aSender)
{
	_menu->setTouchEnabled(false);
    
    CCDirector::getInstance()->end();
}

void ExitLayer::onNoButtonTouch(CCObject *aSender)
{
	_menu->setTouchEnabled(false);
	this->showOut();
}
