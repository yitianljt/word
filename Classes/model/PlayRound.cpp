//
//  PlayRound.cpp
//  CrazyWord
//
//  Created by jintao on 14-8-8.
//
//

#include "PlayRound.h"
USING_NS_CC;

SINGLETON_IMPL(PlayRound);

PlayRound::~PlayRound()
{
    delete _privityDescriptions;
}

bool PlayRound::init()
{
    _privityDescriptions = __Array::create();
    CC_SAFE_RETAIN(_privityDescriptions);

    __Array *arr1_ = __Array::create();
	arr1_->addObject(CCString::create("请认真对待本游戏…"));
	arr1_->addObject(CCString::create("遇到难找的题，\n别忘了赶快跳过！"));
	arr1_->addObject(CCString::create("不要自责…\n或许是打开的方式有问题…"));
	_privityDescriptions->addObject(arr1_);
	
	__Array *arr2_ = __Array::create();
	arr2_->addObject(CCString::create("一定可以做得更好，\n再来一局！"));
	arr2_->addObject(CCString::create("就当这一局从没发生过吧…"));
	_privityDescriptions->addObject(arr2_);
	
	__Array *arr3_ = __Array::create();
	arr3_->addObject(CCString::create("节奏还未调整到最佳的状态，\n继续努力！"));
	arr3_->addObject(CCString::create("有一句成语叫“对牛弹琴”，\n你有同感了么？"));
	arr3_->addObject(CCString::create("来自星星的小伙伴，\n或许不懂地球人的梗…"));
	_privityDescriptions->addObject(arr3_);
	
	__Array *arr4_ = __Array::create();
	arr4_->addObject(CCString::create("还差得远呢，\n再加把劲儿啊！"));
	arr4_->addObject(CCString::create("再练练，\n绝对能猜得更多！"));
	arr4_->addObject(CCString::create("将近及格吧，\n还不行哦~！"));
	arr4_->addObject(CCString::create("恭喜您，\n您和小伙伴已击败了全国40%的玩家！"));
	arr4_->addObject(CCString::create("难道说才找对了这么点？\n不可能！"));
	_privityDescriptions->addObject(arr4_);
    
	__Array *arr5_ = __Array::create();
	arr5_->addObject(CCString::create("能够到达这个等级，\n不错呦~再接再厉！~"));
	_privityDescriptions->addObject(arr5_);
	
	__Array *arr6_ = __Array::create();
	arr6_->addObject(CCString::create("神助攻神猜词，\n一定要分享给更多小伙伴看看！"));
	arr6_->addObject(CCString::create("全明星般的流畅合作，\n帅爆了！"));
	_privityDescriptions->addObject(arr6_);
    
	__Array *arr7_ = __Array::create();
	arr7_->addObject(CCString::create("谁能超过我们？还有谁！"));
	arr7_->addObject(CCString::create("心灵相通，无人可挡！"));
	arr7_->addObject(CCString::create("这是什么节奏？天作之合的节奏！"));
	arr7_->addObject(CCString::create("猜对这么多，其实我们其实是一个人..."));
	arr7_->addObject(CCString::create("这一局如同神一般！Godlike！"));
	arr7_->addObject(CCString::create("默契度这么高，可以直接开房了！"));
	_privityDescriptions->addObject(arr7_);
	
	__Array *arr8_ = __Array::create();
    arr8_->addObject(CCString::create("人类已经无法阻止你了！"));
	_privityDescriptions->addObject(arr8_);
    
    __Array *arr9_ = __Array::create();
	arr9_->addObject(CCString::create("你确定自己来自地球？"));
	_privityDescriptions->addObject(arr9_);
    
    
	
    CCLOG(",size=%zd",_privityDescriptions->count());

    
    return true;
}


const char* PlayRound::getPrivityDescription(unsigned int aPrivity)
{
	int index_ = 0;
	if (aPrivity <=3)
	{
		index_ = 0;
	}else if (3 <= aPrivity && aPrivity < 5) {
		index_ = 1;
	}else if (5 <= aPrivity && aPrivity < 7) {
		index_ = 2;
	}else if (7 <= aPrivity && aPrivity < 9) {
		index_ = 3;
	}else if (9 <= aPrivity && aPrivity < 11) {
		index_ = 4;
	}else if (11 <= aPrivity && aPrivity < 12) {
		index_ = 5;
	}else if (12 <= aPrivity && aPrivity < 14) {
		index_ = 6;
	}else if (15 <= aPrivity && aPrivity <= 20) {
		index_ = 7;
	}
    else if (20<aPrivity)
    {
        index_ = 8;
    }
	const char* returnValue_ = "";
    CCLOG("getPrivityDescription=%d,size=%zd",index_,_privityDescriptions->count());
	__Array *sentences_ = (__Array*)_privityDescriptions->getObjectAtIndex(index_);
	if (sentences_==NULL) return "";
	int rndIndex_ = floorf(CCRANDOM_0_1()*sentences_->count());
	rndIndex_ = rndIndex_>=sentences_->count()?rndIndex_:sentences_->count()-1;
	__String *sentence_ = (__String *)sentences_->getObjectAtIndex(rndIndex_);
	returnValue_ = sentence_->getCString();
	return returnValue_;
}


void PlayRound::newRound()
{
    setCount(60);
    setLevel(1);
}
