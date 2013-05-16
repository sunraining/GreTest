#include "S3TestScene.h"
#include "S2PracticeScene.h"
#include "S2TestScene.h"
#include "AppMacros.h"
#include "S2SettingScene.h"
#include "S1MainScene.h"


#include <string.h>
#include <vector.h>


using namespace cocos2d;


#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define rate1 1.0
#define rate2 1.0

#define s3FontSize1_macro 40.0//title1
#define s3FontSize2_macro 16.0//title2
#define s3FontSize3_macro 40.0//title3 cell的label字体大小

#define s3Position1_macro(aItem)   ccp(origin.x+visibleSize.width/2/rate1,origin.y+1452/rate2)//title1
#define s3Position2_macro(aSprite) ccp(origin.x+visibleSize.width/2/rate1,origin.y+1452/rate2)//navbar
#define s3Position3_macro(aItem)   ccp(origin.x+85,origin.y+1452)//backitem
#define s3Position4_macro(aSprite) ccp(origin.x+1024/rate1,origin.y+848/rate2)//tableView background image
#define s3Position5_macro(aItem)   ccp(origin.x+804/rate1,origin.y+60/rate2)//GRE模考按钮
#define s3Position6_macro(aItem)   ccp(origin.x+1024/rate1,origin.y+60/rate2)//备考资料按钮
#define s3Position7_macro(aItem)   ccp(origin.x+1244/rate1,origin.y+60/rate2)//设置按钮
#define s3Position8_macro(aItem)   ccp(origin.x+1600/rate1,origin.y+0/rate2) //cell后面的的label位置  selftest

#define s3Size1_macro(aTableView)  CCSize(1877,1000 - s3Less1_macro)//tableView
#define s3Size2_macro(aCell)       CCSizeMake(s3Size1_macro(aTableView).width, 92.0)//cell
#define s3Size3_macro(aItem)       CCSizeMake(200, s3Size2_macro(aCell).height)//cell后面的的label大小

#define s3Less1_macro 40.0 //tableView 去掉上下一些距离，避免超过白色框的圆角
#define s3Less2_macro 20.0 //CellLabel 前面增加一些空间


USING_NS_CC;
USING_NS_CC_EXT;


CCScene* S3TestMain::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		S3TestMain *layer = S3TestMain::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
        
	} while (0);
    
	return scene;
}

bool S3TestMain::init()
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

        
	
        //NavBar及背景图
        
        {
            {
                CCSprite * aSprite = CCSprite::create("pBackground.png");
                aSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
                //CC_BREAK_IF(! aSprite);
                this->addChild(aSprite,1);
                aSprite ->getTexture()->setAntiAliasTexParameters();//抗锯齿
            }
            
            {
                CCSprite * aSprite = CCSprite::create("pNavBar.png");
                aSprite->setPosition(s3Position2_macro(aSprite));
                //CC_BREAK_IF(! aSprite);
                this->addChild(aSprite,1);
            }
            
            {
                CCLabelTTF * titleLabel = CCLabelTTF::create("Test", "Arial", s3FontSize1_macro);
                titleLabel->setPosition(s3Position1_macro(aItem));
                //CC_BREAK_IF(! aSprite);
                this->addChild(titleLabel,1);
            }
        }
		
        
        
        //TabBar及按钮
        
        {
            //TabBar
            {
                CCSprite * aSprite = CCSprite::create("pTabBar.png");
                aSprite->setPosition(CCPointZero);
                aSprite->setAnchorPoint(CCPointZero);
                //CC_BREAK_IF(! aSprite);
                this->addChild(aSprite,1);
            }
            
            //GRE模考按钮
            {
                CCSprite * sprite1 = CCSprite::create("pPencilIconActive.png");
                CCSprite * sprite2 = CCSprite::create("pPencilIconActive.png");
                CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                                   sprite1,
                                                                   sprite2,
                                                                   this,
                                                                   menu_selector(S3TestMain::menuOnPencil));
                CC_BREAK_IF(! aItem);
                aItem->setPosition(s3Position5_macro(aItem));
                _menu ->addChild(aItem,1);
            }
            
            //备考资料按钮
            {
                CCSprite * sprite1 = CCSprite::create("pDocumentIcon.png");
                CCSprite * sprite2 = CCSprite::create("pDocumentIconActive.png");
                CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                                   sprite1,
                                                                   sprite2,
                                                                   this,
                                                                   menu_selector(S3TestMain::menuOnDocument));
                CC_BREAK_IF(! aItem);
                aItem->setPosition(s3Position6_macro(aItem));
                _menu ->addChild(aItem,1);
            }
            
            //设置按钮
            {
                CCSprite * sprite1 = CCSprite::create("pSettingsIcon.png");
                CCSprite * sprite2 = CCSprite::create("pSettingsIconActive.png");
                CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                                   sprite1,
                                                                   sprite2,
                                                                   this,
                                                                   menu_selector(S3TestMain::menuOnSettings));
                CC_BREAK_IF(! aItem);
                aItem->setPosition(s3Position7_macro(aItem));
                _menu ->addChild(aItem,1);
            }
        }
        
        
		//控件
	
        {
			CCSprite * sprite1 = CCSprite::create("pBackButton.png");
			CCSprite * sprite2 = CCSprite::create("pBackButton.png");
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                sprite1,
                sprite2,
                this,
                menu_selector(S3TestMain::menuOnBackCallback));
			CC_BREAK_IF(! aItem);
			aItem->setPosition(s3Position3_macro(aItem));
			_menu ->addChild(aItem,1);
            
            
            CCLabelTTF *label_back = CCLabelTTF::create("GRE模考", "Arial", s3FontSize2_macro, sprite1->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
            label_back->setPosition(s3Position3_macro(aItem));
            this ->addChild(label_back,2);
		}
                
        
        CCSprite *spriteBackground = CCSprite::create("s3ElevenRowTable.png");
        spriteBackground->setPosition(s3Position4_macro(aSprite));
        CC_BREAK_IF(! spriteBackground);
        this->addChild(spriteBackground,1);
        
        
		CCTableView* pTableView = CCTableView::create(this, s3Size1_macro(aTableView));
        CC_BREAK_IF(! pTableView);
		pTableView->setDirection(kCCScrollViewDirectionVertical);
        pTableView->setAnchorPoint(CCPointZero);
        pTableView->setPosition(ccp(spriteBackground->getPosition().x-(spriteBackground->getContentSize().width / 2),spriteBackground->getPosition().y-(spriteBackground->getContentSize().height / 2) + s3Less1_macro / 2));
		pTableView->setDelegate(this);
        
        //   设置顺序是自上往下
		pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        
		this->addChild(pTableView,1);
        
        {
            std::string str = "Test 1";
            aVectorCellValue.push_back(str);
        }
        {
            std::string str = "Test 2";
            aVectorCellValue.push_back(str);
        }
        {
            std::string str = "Test 3";
            aVectorCellValue.push_back(str);
        }
        {
            std::string str = "Test 4";
            aVectorCellValue.push_back(str);
        }
        {
            std::string str = "Test 5";
            aVectorCellValue.push_back(str);
        }
        {
            std::string str = "Test 6";
            aVectorCellValue.push_back(str);
        }
        {
            std::string str = "Test 7";
            aVectorCellValue.push_back(str);
        }
        {
            std::string str = "Test 8";
            aVectorCellValue.push_back(str);
        }
        
		pTableView->reloadData();
        
		bRet = true;
	} while (0);

	return bRet;
}


CCSize S3TestMain::cellSizeForTable(CCTableView *table)
{
    return s3Size2_macro(aCell);
}

unsigned int S3TestMain::numberOfCellsInTableView(CCTableView *table)
{
    
    return aVectorCellValue.size();
}

CCTableViewCell* S3TestMain::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
//    CCString *strCell = CCString::createWithFormat("Practice %d",idx);
    CCString *strCell = CCString::create(aVectorCellValue[idx].c_str());
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        CCSprite *pSprite = CCSprite::create();//("cellLine.png");
        pSprite->setAnchorPoint(CCPointZero);
		pSprite->setPosition(CCPointZero);
        pCell->addChild(pSprite);
        
        {
            CCLabelTTF *pLabel = CCLabelTTF::create(strCell->getCString(), "Arial", s3FontSize3_macro, s3Size2_macro(aCell), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
            pLabel->setPosition(ccp(s3Less2_macro,0));
            pLabel->setAnchorPoint(CCPointZero);
            pLabel->setColor(ccc3(0,0,0));
            pLabel->setTag(10);
            pCell->addChild(pLabel,1);
        }
        
        {
            CCLabelTTF *pLabel = CCLabelTTF::create("Locked", "Arial",s3FontSize3_macro, s3Size3_macro(aItem), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter);
            pLabel->setPosition(s3Position8_macro(aItem));
            pLabel->setAnchorPoint(CCPointZero);
            pLabel->setColor(ccc3(0,0,255));
            pLabel->setTag(10);
            pCell->addChild(pLabel,1);
        }
        
    }
    
    CCLabelTTF *pLabel = (CCLabelTTF*)pCell->getChildByTag(10);
    pLabel->setString(strCell->getCString());
    
    return pCell;
}

void S3TestMain::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCScene *newScene = CCScene::create();
    S2TestMain *s2TestMain = S2TestMain::create();
    s2TestMain->aVectorCellSmallValue = aVectorCellValue;
    newScene->addChild(s2TestMain);
    CCDirector::sharedDirector()->pushScene(CCTransitionSlideInR::create(0.5, newScene));//动画过场
}

void S3TestMain::scrollViewDidScroll(CCScrollView *view)
{
}

void S3TestMain::scrollViewDidZoom(CCScrollView *view)
{
}



void S3TestMain::menuOnBackCallback(CCObject* pSender)
{
    CCScene *newScene = CCScene::create();
    
    newScene->addChild(S1Main::create());
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(0.3, newScene));//动画过场
    //CCDirector::sharedDirector()->popScene();
}
void S3TestMain::menuOnPencil(CCObject* pSender)
{
    CCScene *newScene = CCScene::create();
    newScene->addChild(S1Main::create());
    CCDirector::sharedDirector()->pushScene(CCTransitionSlideInR::create(0.5, newScene));//动画过场
}
void S3TestMain::menuOnDocument(CCObject* pSender)
{
    
}
void S3TestMain::menuOnSettings(CCObject* pSender)
{
    CCScene *newScene = CCScene::create();
    newScene->addChild(S2Setting::create());
    CCDirector::sharedDirector()->pushScene(CCTransitionSlideInR::create(0.5, newScene));//动画过场
}
