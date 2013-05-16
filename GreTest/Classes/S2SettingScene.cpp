#include "S2SettingScene.h"
#include "AppMacros.h"

using namespace cocos2d;


#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define rate1 1.0
#define rate2 1.0

#define s2FontSize1_macro 40.0//title1
#define s2FontSize2_macro 40.0//title2 cell label

#define s2Position1_macro(aItem) ccp(origin.x+visibleSize.width/2/rate1,origin.y+1452/rate2)//title1
#define s2Position2_macro(aSprite) ccp(origin.x+visibleSize.width/2/rate1,origin.y+1452/rate2)//NavBar位置
#define s2Position3_macro(aSprite) ccp(origin.x+1024/rate1,origin.y+1072/rate2) //tableview background image
#define s2Position4_macro(aItem) ccp(origin.x+804/rate1,origin.y+60/rate2)//GRE模考按钮位置
#define s2Position5_macro(aItem) ccp(origin.x+1024/rate1,origin.y+60/rate2)//备考资料按钮位置
#define s2Position6_macro(aItem) ccp(origin.x+1244/rate1,origin.y+60/rate2)//设置按钮位置

#define s2Size1_macro(aTableView) CCSize(1873,549 - s2Less1_macro) //tableView的大小
#define s2Size2_macro(aCell) CCSizeMake(s2Size1_macro(aTableView).width, 89.0) //Cell的大小


#define s2Less1_macro 40.0 //tableView 去掉上下一些距离，避免超过白色框的圆角
#define s2Less2_macro 20.0 //CellLabel 前面增加一些空间

USING_NS_CC;
USING_NS_CC_EXT;


CCScene* S2Setting::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		S2Setting *layer = S2Setting::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool S2Setting::init()
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

        
	
        //背景图
        
		{
			CCSprite * aSprite = CCSprite::create("pBackground.png");
			aSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
            //CC_BREAK_IF(! aSprite);
			this->addChild(aSprite,1);
            aSprite ->getTexture()->setAntiAliasTexParameters();//抗锯齿
		}
        
        {
			CCSprite * aSprite = CCSprite::create("pNavBar.png");
			aSprite->setPosition(s2Position2_macro(aSprite));
            //CC_BREAK_IF(! aSprite);
			this->addChild(aSprite,1);
		}
        
        {
            CCLabelTTF * titleLabel = CCLabelTTF::create("设置", "Arial", s2FontSize1_macro);
            titleLabel->setPosition(s2Position1_macro(aItem));
            //CC_BREAK_IF(! aSprite);
            this->addChild(titleLabel,1);
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
                CCSprite * sprite1 = CCSprite::create("pPencilIcon.png");
                CCSprite * sprite2 = CCSprite::create("pPencilIconActive.png");
                CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                                   sprite1,
                                                                   sprite2,
                                                                   this,
                                                                   menu_selector(S2Setting::menuOnPencil));
                CC_BREAK_IF(! aItem);
                aItem->setPosition(s2Position4_macro(aItem));
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
                                                                   menu_selector(S2Setting::menuOnDocument));
                CC_BREAK_IF(! aItem);
                aItem->setPosition(s2Position5_macro(aItem));
                _menu ->addChild(aItem,1);
            }
            
            //设置按钮
            {
                CCSprite * sprite1 = CCSprite::create("pSettingsIconActive.png");
                CCSprite * sprite2 = CCSprite::create("pSettingsIconActive.png");
                CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                                   sprite1,
                                                                   sprite2,
                                                                   this,
                                                                   menu_selector(S2Setting::menuOnSettings));
                CC_BREAK_IF(! aItem);
                aItem->setPosition(s2Position6_macro(aItem));
                _menu ->addChild(aItem,1);
            }
        }
        
        
        
		//控件
        
        CCSprite *spriteBackground = CCSprite::create("s2SixRowTable.png");
        spriteBackground->setPosition(s2Position3_macro(aSprite));
        CC_BREAK_IF(! spriteBackground);
        this->addChild(spriteBackground,1);
        
        CCLabelTTF * titleLabel = CCLabelTTF::create("GRE模考 V1.0", "Arial", s2FontSize1_macro);
        titleLabel->setPosition(ccp(spriteBackground->getPosition().x,spriteBackground->getPosition().y-(spriteBackground->getContentSize().height)/2-30));
        //CC_BREAK_IF(! aSprite);
        titleLabel->setColor(ccc3(180,180,180));
        this->addChild(titleLabel,1);
        
        
        {
            std::string str1 = "恢复购买";
            aVectorCellValue.push_back(str1);
        }
        {
            std::string str1 = "意见反馈";
            aVectorCellValue.push_back(str1);
        }
        {
            std::string str1 = "分享给朋友";
            aVectorCellValue.push_back(str1);
        }
        {
            std::string str1 = "给我们评价";
            aVectorCellValue.push_back(str1);
        }
        {
            std::string str1 = "清空答题数据";
            aVectorCellValue.push_back(str1);
        }
        {
            std::string str1 = "关于";
            aVectorCellValue.push_back(str1);
        }
        
        
		CCTableView* pTableView = CCTableView::create(this, spriteBackground->getContentSize());
        CC_BREAK_IF(! pTableView);
		pTableView->setDirection(kCCScrollViewDirectionVertical);
        pTableView->setAnchorPoint(CCPointZero);
        pTableView->setPosition(ccp(spriteBackground->getPosition().x-(spriteBackground->getContentSize().width / 2),spriteBackground->getPosition().y-(spriteBackground->getContentSize().height / 2)));
        pTableView->setBounceable(false);
		pTableView->setDelegate(this);
        
        //   设置顺序是自上往下
		pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        
		this->addChild(pTableView,1);
        
        
		bRet = true;
	} while (0);

	return bRet;
}


CCSize S2Setting::cellSizeForTable(CCTableView *table)
{
    return s2Size2_macro(aCell);
}

unsigned int S2Setting::numberOfCellsInTableView(CCTableView *table)
{
    return aVectorCellValue.size();
}

CCTableViewCell* S2Setting::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *strCell = CCString::create(aVectorCellValue[idx]);
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        CCSprite *pSprite = CCSprite::create();//("cellLine.png");
        pSprite->setAnchorPoint(CCPointZero);
		pSprite->setPosition(CCPointZero);
        pCell->addChild(pSprite);
        
        {
            CCLabelTTF *pLabel = CCLabelTTF::create(strCell->getCString(), "Arial", s2FontSize2_macro, s2Size2_macro(aCell), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
            pLabel->setPosition(ccp(s2Less2_macro,0));
            pLabel->setAnchorPoint(CCPointZero);
            pLabel->setColor(ccc3(0,0,0));
            pLabel->setTag(10);
            pCell->addChild(pLabel,1);
        }
    }
    
    CCLabelTTF *pLabel = (CCLabelTTF*)pCell->getChildByTag(10);
    pLabel->setString(strCell->getCString());
    
    return pCell;
}

void S2Setting::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
}

void S2Setting::scrollViewDidScroll(CCScrollView *view)
{
}

void S2Setting::scrollViewDidZoom(CCScrollView *view)
{
}



void S2Setting::menuShowPracticeList(CCObject* pSender)
{
    
}
void S2Setting::menuOnPencil(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();//bug
}
void S2Setting::menuOnDocument(CCObject* pSender)
{
    
}
void S2Setting::menuOnSettings(CCObject* pSender)
{
    
}
