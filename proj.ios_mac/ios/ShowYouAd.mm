//
//  ShowYouAd.cpp
//  CrazyBox
//
//  Created by jintao on 14-6-12.
//
//

#include "ShowYouAd.h"
#import  "YouMiWallSpot.h"
#import "YouMiWall.h"
#import "YouMiView.h"
#import "YouMiSpots.h"


void ShowYouAd::showYouWallSpot()
{
//    if ([YouMiWallSpot isReady]) {
//        [YouMiWallSpot showSpotViewWithBlock:^{
//            NSLog(@"积分插播退出");
//        }];
//    }
    //无积分
    [YouMiWall showOffers:NO didShowBlock:^{
        NSLog(@"有米推荐墙已显示");
    } didDismissBlock:^{
        NSLog(@"有米推荐墙已退出");
    }];
}

void ShowYouAd::showSpots()
{
//    [YouMiSpots requestSpotData];
//    [YouMiSpots showSpots:nil];
}

void ShowYouAd::showDiyAds(){};