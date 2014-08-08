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
	arr1_->addObject(CCString::create("千万不要辜负小伙伴，伤不起…"));
	arr1_->addObject(CCString::create("不怕神一样的对手，就怕那啥一样的队友"));
	arr1_->addObject(CCString::create("不用再怀疑了，队友一定是高级黑。"));
	arr1_->addObject(CCString::create("遇到难猜的题，别忘了赶快跳过！"));
	arr1_->addObject(CCString::create("不要自责…或许是打开的方式有问题…"));
	_privityDescriptions->addObject(arr1_);
	
	__Array *arr2_ = __Array::create();
	arr2_->addObject(CCString::create("别难为小伙伴了，快换个人猜吧…"));
	arr2_->addObject(CCString::create("一定可以做得更好，再来一局！"));
	arr2_->addObject(CCString::create("你们是在猜词还是在互黑？！"));
	arr2_->addObject(CCString::create("就当这一局从没发生过吧…"));
	arr2_->addObject(CCString::create("费了这么半天劲才猜出来，不会是想歪了吧…"));
	arr2_->addObject(CCString::create("久猜不对，累觉不爱了！"));
	_privityDescriptions->addObject(arr2_);
	
	__Array *arr3_ = __Array::create();
	arr3_->addObject(CCString::create("节奏还未调整到最佳的状态，继续努力！"));
	arr3_->addObject(CCString::create("如果用更奇葩的方式表演，小伙伴或许会更好猜。"));
	arr3_->addObject(CCString::create("有一句成语叫“对牛弹琴”，你有同感了么？"));
	arr3_->addObject(CCString::create("来自星星的小伙伴，或许不懂地球人的梗…"));
	arr3_->addObject(CCString::create("才过了这么几个词…时间都去哪儿了？"));
	arr3_->addObject(CCString::create("明明会的那些词都去哪儿了？"));
	_privityDescriptions->addObject(arr3_);
	
	__Array *arr4_ = __Array::create();
	arr4_->addObject(CCString::create("还差得远呢，再加把劲儿啊！"));
	arr4_->addObject(CCString::create("再练练，绝对能猜得更多！"));
	arr4_->addObject(CCString::create("将近及格吧，还不行哦~！"));
	arr4_->addObject(CCString::create("光顾着笑，忘了猜了~"));
	arr4_->addObject(CCString::create("恭喜您，您和小伙伴已击败了全国40%的玩家！"));
	arr4_->addObject(CCString::create("你的心里一定没有我。"));
	arr4_->addObject(CCString::create("难道说才猜对了这么点？不可能！"));
	_privityDescriptions->addObject(arr4_);
    
	__Array *arr5_ = __Array::create();
	arr5_->addObject(CCString::create("共藏多少意，不说两相知。"));
	arr5_->addObject(CCString::create("新鲜出炉！黄金搭档！"));
	arr5_->addObject(CCString::create("就这样被你们征服了，快去挑战下个难度吧！"));
	arr5_->addObject(CCString::create("众人拾材火焰高，多找些朋友再来试试！"));
	arr5_->addObject(CCString::create("如此有默契，我又相信爱情了~"));
	arr5_->addObject(CCString::create("白天不懂夜的黑，天若有情天亦老，再来一局吧。"));
	arr5_->addObject(CCString::create("能够到达这个等级，不错呦~再接再厉！~"));
	_privityDescriptions->addObject(arr5_);
	
	__Array *arr6_ = __Array::create();
	arr6_->addObject(CCString::create("遇到这么默契的小伙伴就嫁了吧。"));
	arr6_->addObject(CCString::create("高山流水遇知音，一鼓作气再一局！"));
	arr6_->addObject(CCString::create("精彩的配合，喜大普奔！"));
	arr6_->addObject(CCString::create("配合得漂亮！有没有吓坏不明真相的围观群众？"));
	arr6_->addObject(CCString::create("神助攻神猜词，一定要分享给更多小伙伴看看！"));
	arr6_->addObject(CCString::create("全明星般的流畅合作，帅爆了！"));
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
	arr8_->addObject(CCString::create("这样的神同步，不去买张彩票庆祝一下都对不起这样的好成绩！"));
	arr8_->addObject(CCString::create("所谓“心有灵犀一点通”也不过如此吧。"));
	arr8_->addObject(CCString::create("天妒英才，离满分就差那么一点点。"));
	arr8_->addObject(CCString::create("如果你们是男人，恭喜你可以直接出柜了，就他了。"));
	arr8_->addObject(CCString::create("配合得堪称珠联璧合，完美无缺，一起吃大餐庆祝一下！"));
	arr8_->addObject(CCString::create("考试不作弊来年当学弟，快招！你们有没有作弊！"));
	_privityDescriptions->addObject(arr8_);
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
	const char* returnValue_ = "";
    CCLOG("%d,size=%zd",index_,_privityDescriptions->count());
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
