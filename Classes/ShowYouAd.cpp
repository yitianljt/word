//
//  ShowYouAd.cpp
//  CrazyBox
//
//  Created by jintao on 14-6-12.
//
//

#include "ShowYouAd.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif
USING_NS_CC;

SINGLETON_IMPL(ShowYouAd);

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
void ShowYouAd::showYouWallSpot()
{
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                 "org/cocos2dx/cpp/AppActivity",
                                                 "showTest",
                                                 "()V"
                                                 );
    jobject activityObj;  
    if (isHave)  
    {  CCLOG("ShowYouAd::showYouWallSpot");
        activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);  
    }
    else
    {
        CCLOG("no  ShowYouAd::showYouWallSpot");
    }

}

void ShowYouAd::showSpots()
{

}
#endif

bool ShowYouAd::init()
{
	return true;
}