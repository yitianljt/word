//
//  ShowYouAd.cpp
//  CrazyBox
//
//  Created by jintao on 14-6-12.
//
//

#include "ShowYouAd.h"


SINGLETON_IMPL(ShowYouAd);

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
void ShowYouAd::showYouWallSpot()
{

}

void ShowYouAd::showSpots()
{

}
#endif

bool ShowYouAd::init()
{
	return true;
}