/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;


import org.cocos2dx.lib.Cocos2dxActivity;

import android.R;
import android.app.Activity;
import android.os.Bundle;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import net.youmi.android.AdManager;
import net.youmi.android.banner.AdSize;
import net.youmi.android.banner.AdView;
import net.youmi.android.diy.DiyManager;
import net.youmi.android.spot.SpotManager;

public class AppActivity extends Cocos2dxActivity {
    public static AppActivity appActive ;  

	@Override
    protected void onCreate(Bundle savedInstanceState) {
        // TODO Auto-generated method stub
        super.onCreate(savedInstanceState);
        appActive = this;
        // 初始化应用的发布 ID 和密钥，以及设置测试模式
        AdManager.getInstance(this).init("48c1d5353545f8fa", "86d9d62121259df9", false);
        SpotManager.getInstance(this).loadSpotAds();
        SpotManager.getInstance(this).setSpotTimeout(5000); // 5秒
        SpotManager.getInstance(this).setAutoCloseSpot(true);// 设置自动关闭插屏开关
        SpotManager.getInstance(this).setCloseTime(6000); // 设置关闭插屏时间
        
        
     // 广告条接口调用（适用于游戏）

     // 实例化LayoutParams(重要)
     FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(
     FrameLayout.LayoutParams.FILL_PARENT,
     FrameLayout.LayoutParams.WRAP_CONTENT);
     // 设置广告条的悬浮位置
     layoutParams.gravity = Gravity.BOTTOM | Gravity.RIGHT; // 这里示例为右下角
     // 实例化广告条
     AdView adView = new AdView(this,
     AdSize.FIT_SCREEN);
     // 调用Activity的addContentView函数
     this.addContentView(adView, layoutParams);

    
       
    }
	
	@Override
    protected void onDestroy() {
            SpotManager.getInstance(this).unregisterSceenReceiver();
            super.onDestroy();
    }
	public void showSpotAds()
	{
		SpotManager.getInstance(this).showSpotAds(this);
	    SpotManager.getInstance(this).disMiss(true);  

	}
	public void showDiyAds()
	{
		DiyManager.showRecommendWall(this);  
	}
	
	static public void showTest()
	{
		appActive.showSpotAds();
	}
	
	static public void staticShowDiy()
	{
		appActive.showDiyAds();
	}
	
	@Override
	public void onBackPressed() {
	    // 如果有需要，可以点击后退关闭插屏广告（可选）。
	    if (!SpotManager.getInstance(this).disMiss(true)) {
	        super.onBackPressed();
	    }
	}

	@Override
	protected void onStop() {
	    //如果不调用此方法，则按home键的时候会出现图标无法显示的情况。
	    SpotManager.getInstance(this).disMiss(false);
	    super.onStop();
	}
	
}
