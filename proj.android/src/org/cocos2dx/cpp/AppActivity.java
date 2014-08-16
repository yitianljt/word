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
        // ��ʼ��Ӧ�õķ��� ID ����Կ���Լ����ò���ģʽ
        AdManager.getInstance(this).init("48c1d5353545f8fa", "86d9d62121259df9", false);
        SpotManager.getInstance(this).loadSpotAds();
        SpotManager.getInstance(this).setSpotTimeout(5000); // 5��
        SpotManager.getInstance(this).setAutoCloseSpot(true);// �����Զ��رղ�������
        SpotManager.getInstance(this).setCloseTime(6000); // ���ùرղ���ʱ��
        
        
     // ������ӿڵ��ã���������Ϸ��

     // ʵ����LayoutParams(��Ҫ)
     FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(
     FrameLayout.LayoutParams.FILL_PARENT,
     FrameLayout.LayoutParams.WRAP_CONTENT);
     // ���ù����������λ��
     layoutParams.gravity = Gravity.BOTTOM | Gravity.RIGHT; // ����ʾ��Ϊ���½�
     // ʵ���������
     AdView adView = new AdView(this,
     AdSize.FIT_SCREEN);
     // ����Activity��addContentView����
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
	    // �������Ҫ�����Ե�����˹رղ�����棨��ѡ����
	    if (!SpotManager.getInstance(this).disMiss(true)) {
	        super.onBackPressed();
	    }
	}

	@Override
	protected void onStop() {
	    //��������ô˷�������home����ʱ������ͼ���޷���ʾ�������
	    SpotManager.getInstance(this).disMiss(false);
	    super.onStop();
	}
	
}
