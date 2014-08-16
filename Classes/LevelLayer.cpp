//
//  LevelLayer.cpp
//  CrazyWord
//
//  Created by jintao on 14-8-7.
//
//

#include "LevelLayer.h"
#include "ComUtil.h"
#include "cocostudio/CocoStudio.h"
#include "PlayRound.h"
#include "FileTool.h"
#include "ShowYouAd.h"
#include <ctime>
USING_NS_CC;
using namespace std;

static int s_showAdCount = 0;
LevelLayer::LevelLayer(unsigned int iLevel)
{
    setLevelNum(iLevel);
    _countDown = 30;
    _wrongCount = 0;
    _vecBlocks = nullptr;
    _vecEasyQuestion = nullptr;
    _vecMedQuestion = nullptr;
    setNormalWord("");
    setWrongWord("");
    //初始化所有的题目
    parseJson();
}

LevelLayer* LevelLayer::create(unsigned int iLevel)
{
    LevelLayer *pRet = new LevelLayer(iLevel);
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}


bool LevelLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    __String* strLevel = __String::createWithFormat("第%d层/99层",getLevelNum());
    _ttfLevel = LabelTTF::create(strLevel->getCString(), "黑体", FONTSIZE(30));
    _ttfLevel->setPosition(Point(COMWinSize().width/2,COMWinSize().height*0.9));
    this->addChild(_ttfLevel);
    
    __String* strCount = __String::createWithFormat("%d秒",_countDown);
    _ttfCountDown = LabelTTF::create(strCount->getCString(), "黑体", FONTSIZE(40));
    _ttfCountDown->setPosition(_ttfLevel->getPosition()+Point(0,-_ttfLevel->getContentSize().height/2-40));
    this->addChild(_ttfCountDown);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* t, Event* e)
    {
        
        WordBlock* block;
        CCLOG("size = %lu",_vecBlocks->size());
        for(auto it = _vecBlocks->begin(); it != _vecBlocks->end(); it++)
        {
            block = *it;
            if(block->getIsDiff() && block->getBoundingBox().containsPoint(t->getLocation()))
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Correct.MP3");
                _wrongCount = 0;
                nextLevel();
                return true;
            }
            else if(!block->getIsDiff() && block->getBoundingBox().containsPoint(t->getLocation()))
            {
                _wrongCount++;
                CCLOG("wrong=%d,ad=%d",_wrongCount,s_showAdCount);
                if (_wrongCount>=4 && s_showAdCount ==0) {
                    //ShowYouAd::shared()->showDiyAds();
                }
                else if (_wrongCount>=5 && CCRANDOM_0_1()>0.4+0.2*std::min(3,s_showAdCount) && s_showAdCount>0)
                {
//                    ShowYouAd::shared()->showDiyAds();
//                    _wrongCount = 0;
//                    s_showAdCount++;
                }
                
                if ( _wrongCount>=6)
                {
                    ShowYouAd::shared()->showYouWallSpot();
                    _wrongCount = 0;
                    s_showAdCount++;
                }
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Pass.m4a");
                return false;
            }
        }
        return false;
    };  
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    schedule(schedule_selector(LevelLayer::updateCount), 1.0f);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/bgm.mp3",true);
    return true;
}

void LevelLayer::updateCount(float ft)
{
    _countDown--;
    PlayRound::shared()->setCount(_countDown);
    if (_countDown<=0) {
        unschedule(schedule_selector(LevelLayer::updateCount));
        gameOver();
        return;
    }
    __String* strCount = __String::createWithFormat("%d秒",_countDown);
    _ttfCountDown->setString(strCount->getCString());
}

void LevelLayer::onEnter()
{
    Layer::onEnter();
    if (getLevelNum()<=3) {
        int row=2;
        createBlocks(row);
    }
    
}

void LevelLayer::createBlocks(int rows)
{
    setNormalWord(_vecQuestion->at(getLevelNum()-1).strNormal);
    setWrongWord(_vecQuestion->at(getLevelNum()-1).strDiff);

    _vecBlocks = new vector<WordBlock*>();
    float cellWidth = (COMWinSize().width-40)/(rows*1.0);
    
    float startX = COMWinSize().width/2-(rows/2)*cellWidth;
    float startY = COMWinSize().height/2+(rows/2-1)*cellWidth;
    srand((int)time(NULL));
    int iRandNum =  rand()%(rows*rows);

    for (int i=0;i<rows*rows; i++) {
        WordBlock* block = WordBlock::create(Size(cellWidth,cellWidth), i==iRandNum?getWrongWord():getNormalWord(),i==iRandNum);
        block->setPosition(Point(startX,startY)+Point((i/rows)*cellWidth,-(i%rows)*cellWidth));
        addChild(block);
        _vecBlocks->push_back(block);
    }
}

void LevelLayer::nextLevel()
{
    _levelNum++;
    PlayRound::shared()->setLevel(_levelNum);
    __String* strLevel = __String::createWithFormat("第%d层/99层",getLevelNum());
    _ttfLevel->setString(strLevel->getCString());

    for(auto it = _vecBlocks->begin(); it != _vecBlocks->end(); it++)
    {
        WordBlock* block = *it;
        block->removeFromParent();
    }
    _vecBlocks->clear();
    delete _vecBlocks;
    if (_levelNum<=3) {
        createBlocks(2);
    }
    else if(_levelNum<=6)
    {
        createBlocks(4);
    }
    else  if(_levelNum<=9)
    {
        createBlocks(6);
    }
    else
    {
        createBlocks(8);
    }
}

void LevelLayer::gameOver()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    if (this->getDelegate())
    {
        this->getDelegate()->gameOver();
    }
}

void LevelLayer::parseJson()
{
    rapidjson::Document doc;
    string strPath = FileUtils::getInstance()->fullPathForFilename("data/word.json");//getStringFromFile("test.json");
    string strData = FileUtils::getInstance()->getStringFromFile(strPath);
    
    if (strData.size()==0) {
        CCLOG("not found file");
        return;
    }
    _vecEasyQuestion = new vector<Question>();
    _vecMedQuestion = new vector<Question>();
    _vecQuestion = new vector<Question>();
    
    doc.Parse<0>(strData.c_str());
    if (doc.HasParseError()) {
        CCLOG("GetParseError = %s\n",doc.GetParseError());
    }
    else if(doc.IsObject())
    {
        rapidjson::Value &easyArray = doc["easy"];
        rapidjson::Value &medArray = doc["med"];

        if (easyArray.IsArray()) {
            for (unsigned int i=0; i<easyArray.Size(); i++) {
                Question que = Question();
                que.strNormal = doc["easy"][i]["nor"].GetString();
                que.strDiff = doc["easy"][i]["diff"].GetString();
                _vecEasyQuestion->push_back(que);
            }
        }
        if (medArray.IsArray()) {
            for (unsigned int i=0; i<medArray.Size(); i++) {
                Question que = Question();
                que.strNormal = doc["med"][i]["nor"].GetString();
                que.strDiff = doc["med"][i]["diff"].GetString();
                _vecMedQuestion->push_back(que);
            }
        }
        srand((unsigned)(time(NULL)));
        random_shuffle(_vecEasyQuestion->begin(), _vecEasyQuestion->end());
        for (int i=0; i<_vecEasyQuestion->size(); i++) {
            CCLOG("new [%d]=%s,",i,_vecEasyQuestion->at(i).strNormal.c_str());
        }
        for (int i=0; i<10; i++) {
            int iTime = (unsigned)(time(NULL)+i);
            srand(iTime);
            int iRand = rand()%_vecEasyQuestion->size();
            CCLOG("1= iRand=%d",iRand);

            Question queTmp = _vecEasyQuestion->at(iRand);
            _vecEasyQuestion->at(iRand) = _vecEasyQuestion->at((iRand+1)%_vecEasyQuestion->size());
            _vecEasyQuestion->at((iRand+1)%_vecEasyQuestion->size()) = queTmp;

        }
        srand((unsigned)(time(NULL)));
        random_shuffle(_vecMedQuestion->begin(), _vecMedQuestion->end());
        for (int i=0; i<10; i++) {
            int iTime = (unsigned)(time(NULL)+i);
            srand(iTime);
            int iRand = rand()%_vecMedQuestion->size();
            CCLOG("2= iRand=%d",iRand);
            Question queTmp = _vecMedQuestion->at(iRand);
            _vecMedQuestion->at(iRand) = _vecMedQuestion->at((iRand+1)%_vecMedQuestion->size());
            _vecMedQuestion->at((iRand+1)%_vecMedQuestion->size()) = queTmp;
        }
        for (int i=0; i<_vecEasyQuestion->size(); i++) {
            CCLOG("old [%d]=%s,",i,_vecEasyQuestion->at(i).strNormal.c_str());
        }
    }
    _vecQuestion->assign(_vecEasyQuestion->begin(), _vecEasyQuestion->begin()+4);
    for (int i=0; i<_vecMedQuestion->size(); i++) {
        _vecQuestion->push_back(_vecMedQuestion->at(i));
    }
}
