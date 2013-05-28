#include "S2PracticeScene.h"
#include "AppMacros.h"
#include "S1MainScene.h"
#include "ScriptParser.h"
using namespace cocos2d;


#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define rate1 1.0
#define rate2 1.0

#define classPlistName_macro "S2Practice.plist"

#define s2FontSize1_macro 40.0//title1
#define s2FontSize2_macro 16.0//title2
#define s2FontSize3_macro 40.0//title3

#define s2Position5_macro(aSprite)  ccp(origin.x+1656/rate1,origin.y+850/rate2)//PracticeList
#define s2Position6_macro(aItem)    ccp(origin.x+1600/rate1,origin.y+0/rate2)//cell后面的的label位置 selftest
#define s2Position7_macro(aSprite)  ccp(origin.x+1024/rate1,origin.y+1072/rate2)//tableview background image

#define s2Size1_macro(aTableView)   CCSizeMake(601, 800 - s2Less1_macro)//small table
#define s2Size2_macro(aCell)        CCSizeMake(s2Size1_macro(aTableView).width, 92.0)//cell small
#define s2Size3_macro(aTableView)   CCSize(1877,549 - s2Less2_macro)//tableview
#define s2Size4_macro(aCell)        CCSizeMake(s2Size3_macro(aTableView).width, 92.0) //cell big
#define s2Size5_macro(aItem)        CCSizeMake(200, s2Size4_macro(aCell).height)//cell后面的的label大小

#define s2Less1_macro 20.0 //small tableview 去掉上下一些距离，避免超过白色框的圆角
#define s2Less2_macro 40.0 //tableView 去掉上下一些距离，避免超过白色框的圆角
#define s2Less3_macro 20.0 //cell label 前面增加一些空间

#define s2Tag1        10//cell label
#define s2Tag2        11//practicelist tableview
#define s2Tag3        12//tableView
#define s2Tag4        13//s2pover


USING_NS_CC;
USING_NS_CC_EXT;


CCScene* S2PracticeScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		S2PracticeScene *layer = S2PracticeScene::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool S2PracticeScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
        
        
		//每个项目都要创建的东西

		_menu = CCMenu::create(NULL);
		_menu->setPosition(CCPointZero);
		CC_BREAK_IF(! _menu);

		this->addChild(_menu, 2);

        plistDic = CCDictionary::createWithContentsOfFile(classPlistName_macro);
        
        //*****************背景图/ NavBar/ Title*****************//
		{
			CCSprite * aSprite = CCSprite::create("pBackground.png");
			aSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
            //CC_BREAK_IF(! aSprite);
			this->addChild(aSprite,1);
            aSprite ->getTexture()->setAntiAliasTexParameters();//抗锯齿
		}
        
        {
			CCSprite * aSprite = CCSprite::create("pNavBar.png");
            aSprite->setPosition(ScriptParser::getPositionFromPlist(plistDic,"pNavBar"));
            //CC_BREAK_IF(! aSprite);
			this->addChild(aSprite,1);
		}
        
        {
            CCLabelTTF * titleLabel = CCLabelTTF::create("Practice 1", "Arial", s2FontSize1_macro);
            titleLabel->setPosition(ScriptParser::getPositionFromPlist(plistDic,"titleLabel"));
            //CC_BREAK_IF(! aSprite);
            this->addChild(titleLabel,1);
        }
        
        //*****************BackButton And BackLabel*****************//
        {
			CCSprite * sprite1 = CCSprite::create("pBackButton.png");
			CCSprite * sprite2 = CCSprite::create("pBackButton.png");
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                sprite1,
                sprite2,
                this,
                menu_selector(S2PracticeScene::menuOnBackCallback));
			CC_BREAK_IF(! aItem);
            aItem->setPosition(ScriptParser::getPositionFromPlist(plistDic,"pBackIcon"));
			_menu ->addChild(aItem,1);
            
            {
                CCLabelTTF *label_back = CCLabelTTF::create("Practice", "Arial", s2FontSize2_macro, sprite1->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
                label_back->setPosition(ScriptParser::getPositionFromPlist(plistDic,"pBackIcon"));
                this ->addChild(label_back,2);
            }
		}
        
        //*****************pRecButton*****************//
		{
			CCSprite * sprite1 = CCSprite::create("pRecButton.png");
			CCSprite * sprite2 = CCSprite::create("pRecButton.png");

			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
				sprite1,
				sprite2,
				this,
                                                               menu_selector(S2PracticeScene::menuShowPracticeList));
			CC_BREAK_IF(! aItem);
            aItem->setPosition(ScriptParser::getPositionFromPlist(plistDic, "pRectIcon"));
			_menu ->addChild(aItem,1);
		}
        
        //*****************Practice List 集,包括小TableView和背景*****************//
        {
            CCSprite *spritePracticeList = CCSprite::create("s2Popover.png");
            spritePracticeList->setPosition(s2Position5_macro(aSprite));
            CC_BREAK_IF(! spritePracticeList);
            spritePracticeList->setTag(s2Tag4);
            spritePracticeList->setVisible(false);
            this->addChild(spritePracticeList,10);
            
            CCTableView* pTableView = CCTableView::create(this, s2Size1_macro(aTableView));
            CC_BREAK_IF(! pTableView);
            pTableView->setDirection(kCCScrollViewDirectionVertical);
            pTableView->setPosition(ccp(129,160));//bug
            pTableView->setDelegate(this);
            pTableView->setTag(s2Tag2);
            
            //   设置顺序是自上往下
            pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
            
            spritePracticeList->addChild(pTableView);
            
            pTableView->reloadData();
            
        }
        
        //*****************大的TableView 及 背景*****************//
        CCSprite *spriteBackground = CCSprite::create("s2SixRowTable.png");
        spriteBackground->setPosition(s2Position7_macro(aSprite));
        CC_BREAK_IF(! spriteBackground);
        this->addChild(spriteBackground,1);
        
		{
            CCTableView* pTableView = CCTableView::create(this, s2Size3_macro(aTableView));
            CC_BREAK_IF(! pTableView);
            pTableView->setDirection(kCCScrollViewDirectionVertical);
            pTableView->setPosition(ccp(spriteBackground->getPosition().x-(spriteBackground->getContentSize().width / 2),spriteBackground->getPosition().y-(spriteBackground->getContentSize().height / 2) + s2Less2_macro / 2));
            pTableView->setDelegate(this);
            pTableView->setTag(s2Tag3);
            
            //   设置顺序是自上往下
            pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
            
            this->addChild(pTableView,1);
            
            {
                std::string str = "Section 1";
                aVectorCellValue.push_back(str);
            }
            {
                std::string str = "Section 2";
                aVectorCellValue.push_back(str);
            }
            {
                std::string str = "Section 3";
                aVectorCellValue.push_back(str);
            }
            {
                std::string str = "Section 4";
                aVectorCellValue.push_back(str);
            }
            {
                std::string str = "Section 5";
                aVectorCellValue.push_back(str);
            }
            
            
            pTableView->reloadData();
        }
        
		bRet = true;
	} while (0);

	return bRet;
}


CCSize S2PracticeScene::cellSizeForTable(CCTableView *table)
{
    return s2Size4_macro(aCell);
}

unsigned int S2PracticeScene::numberOfCellsInTableView(CCTableView *table)
{
    int tableTag = table->getTag();
    if (tableTag==s2Tag2) {//practicelist tableview
        return aVectorCellSmallValue.size();
        CCLog("aVectorCellSmallValue.size:%d",aVectorCellSmallValue.size());
    }else if(tableTag==s2Tag3){
        return aVectorCellValue.size();
    }
    return 0;
}

CCTableViewCell* S2PracticeScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    int tableTag = table->getTag();
    if (tableTag==s2Tag2) {//PracticeList TableView
        
        CCString *strCell = CCString::create(aVectorCellSmallValue[idx]);
        
        CCLog("strCellaa:%s",strCell->getCString());
        CCTableViewCell *pCell = table->dequeueCell();
        if (!pCell) {
            pCell = new CCTableViewCell();
            pCell->autorelease();
            CCSprite *pSprite = CCSprite::create("cellLine.png");
            pSprite->setPosition(CCPointZero);
            pSprite->setAnchorPoint(CCPointZero);
            pCell->addChild(pSprite,1);
            
            {
                CCLabelTTF *pLabel = CCLabelTTF::create(strCell->getCString(), "Arial", s2FontSize3_macro, s2Size2_macro(aCell), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
                pLabel->setPosition(ccp(s2Less3_macro,0));
                pLabel->setAnchorPoint(CCPointZero);
                pLabel->setColor(ccc3(0,0,0));
                pLabel->setTag(s2Tag1);
                pCell->addChild(pLabel,1);
            }
        }
        
        CCLabelTTF *pLabel = (CCLabelTTF*)pCell->getChildByTag(s2Tag1);
        pLabel->setString(strCell->getCString());
        
        return pCell;
        
    }else if (tableTag==s2Tag3){//TableView
        
        CCString *strCell = CCString::create(aVectorCellValue[idx]);
        CCLog("strCell:%s",strCell->getCString());
        CCTableViewCell *pCell = table->dequeueCell();
        if (!pCell) {
            pCell = new CCTableViewCell();
            pCell->autorelease();
            CCSprite *pSprite = CCSprite::create();//("cellLine.png");
            pSprite->setPosition(CCPointZero);
            pSprite->setAnchorPoint(CCPointZero);
            pCell->addChild(pSprite,1);
            
            {
                CCLabelTTF *pLabel = CCLabelTTF::create(strCell->getCString(), "Arial", s2FontSize3_macro, s2Size4_macro(aCell), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
                pLabel->setPosition(ccp(s2Less3_macro,0));
                pLabel->setAnchorPoint(CCPointZero);
                pLabel->setColor(ccc3(0,0,0));
                pLabel->setTag(s2Tag1);
                pCell->addChild(pLabel,1);
            }
            
            {
                CCLabelTTF *pLabel = CCLabelTTF::create("Completed", "Arial",s2FontSize3_macro, s2Size5_macro(aItem), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter);
                pLabel->setPosition(s2Position6_macro(aItem));
                pLabel->setAnchorPoint(CCPointZero);
                pLabel->setColor(ccc3(0,0,255));
                pLabel->setTag(s2Tag1);
                pCell->addChild(pLabel,1);
            }
            
        }
        
        CCLabelTTF *pLabel = (CCLabelTTF*)pCell->getChildByTag(10);
        pLabel->setString(strCell->getCString());
        
        
        return pCell;
    }
    
    
    return NULL;
}

void S2PracticeScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
}

void S2PracticeScene::scrollViewDidScroll(CCScrollView *view)
{
}

void S2PracticeScene::scrollViewDidZoom(CCScrollView *view)
{
}



void S2PracticeScene::menuOnBackCallback(CCObject* pSender)
{
    
    CCScene *newScene = CCScene::create();
    
    newScene->addChild(S1Main::create());
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(0.3, newScene));//动画过场
   // CCDirector::sharedDirector()->popScene();
}
void S2PracticeScene::menuShowPracticeList(CCObject* pSender)
{
    CCSprite *aSprite = (CCSprite*)this->getChildByTag(s2Tag4);
    if(aSprite->isVisible()){
        
        aSprite->setVisible(false);
    }else{
        
        aSprite->setVisible(true);
         
    }
}