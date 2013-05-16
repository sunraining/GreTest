#include "S1MainScene.h"
#include "AppMacros.h"

#include "S5CompositionScene.h"
#include "S11PrepareResScene.h"
#include "pSettingScene.h"
#include "S2PracticeScene.h"
#include "S3TestScene.h"

using namespace cocos2d;


#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define rate1 1.0
#define rate2 1.0

#define s1Position1_macro(aItem) ccp(origin.x+1998/rate1,origin.y+1452/rate2)//pRecButton.png
#define s1Position2_macro(aItem) ccp(origin.x+1998/rate1,origin.y+1452/rate2)//s1HelpIconPosition_macro
#define s1Position3_macro(aItem) ccp(origin.x+512/rate1,origin.y+750/rate2)//s1PracticeButton_macro
#define s1Position4_macro(aItem) ccp(origin.x+1536/rate1,origin.y+750/rate2)//s1PracticeButton_macro
#define s1Position5_macro(aItem) ccp(origin.x+804/rate1,origin.y+60/rate2)//m_practiceItem
#define s1Position6_macro(aItem) ccp(origin.x+1024/rate1,origin.y+60/rate2)//m_prepareItem
#define s1Position7_macro(aItem) ccp(origin.x+1244/rate1,origin.y+60/rate2)//m_setting

#define s1Str1_macro "GRE模考"
#define s1Str2_macro "备考资料"
#define s1Str3_macro "设置"


#define s1FontName_macro "Thonburi"

#define s1TitleFontSize_macro 40
#define s1FontSize_macro 20

#define s1Blue_macro ccc3(168.0,168.0,168.0)

#define s1White_macro ccc3(255.0,255.0,255.0)



CCScene* S1Main::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		S1Main *layer = S1Main::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool S1Main::init()
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
		//控件
     
        {
			CCSprite * aSprite = CCSprite::create("pNavBar.png");
            aSprite->setAnchorPoint(ccp(0.0,1.0));
			aSprite->setPosition(ccp(0,visibleSize.height-40));
            CC_BREAK_IF(! aSprite);
			this->addChild(aSprite,1);
		}
       
        titleLabel = CCLabelTTF::create(s1Str1_macro,s1FontName_macro,s1TitleFontSize_macro);
        CCLabelTTF* pLabel = titleLabel;
        pLabel->setColor(ccWHITE);

        pLabel->setPosition( s1Position1_macro(pLabel));
        pLabel->setPosition( ccp( visibleSize.width/2,pLabel->getPosition().y));
                          
        this->addChild(pLabel, 1);
        
        {
			CCSprite * aSprite = CCSprite::create("pRecButton.png");
			aSprite->setPosition(s1Position1_macro(aSprite));
            CC_BREAK_IF(! aSprite);
			this->addChild(aSprite,1);
		}
		{
			CCSprite * sprite1 = CCSprite::create("s1HelpIcon.png");
			CCSprite * sprite2 = CCSprite::create("s1HelpIcon.png");
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S1Main::menuCloseCallback));
			CC_BREAK_IF(! aItem);
			aItem->setPosition(s1Position1_macro(aItem));
			_menu ->addChild(aItem,1);
		}
        
        
        
		{
			CCSprite * sprite1 = CCSprite::create("s1PracticeButton.png");
			CCSprite * sprite2 = CCSprite::create("s1PracticeButton.png");
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S1Main::menuCloseCallback));
			CC_BREAK_IF(! aItem);
			aItem->setPosition(s1Position3_macro(aItem));
            aItem->setTag(1);
			_menu ->addChild(aItem,1);
		}
        
		{
			CCSprite * sprite1 = CCSprite::create("s1TestButton.png");
			CCSprite * sprite2 = CCSprite::create("s1TestButton.png");
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S1Main::menuCloseCallback));
			CC_BREAK_IF(! aItem);
			aItem->setPosition(s1Position4_macro(aItem));
            aItem->setTag(2);
			_menu ->addChild(aItem,1);
		}

        {
			pTabBar = CCSprite::create("pTabBar.png");
            pTabBar->setAnchorPoint(ccp(0.0,0.0));
			pTabBar->setPosition(CCPointZero);
            CC_BREAK_IF(! pTabBar);
			this->addChild(pTabBar,1);
            
		}
        
        m_highlightSp = CCSprite::create("pTabBarSelectedHighlight.png");
        
        
        {
            
            m_practiceSprite = CCSprite::create("pPencilIconActive.png");
            CCSprite * aSprite = m_practiceSprite;
            aSprite->setPosition(s1Position5_macro(aSprite));
            
            this->addChild(aSprite,1);
            
            CCSprite * sprite1 = CCSprite::create();
            CCSprite * sprite2 = CCSprite::create();
            m_practiceItem = CCMenuItemSprite::create(
                                                      sprite1,
                                                      sprite2,
                                                      this,
                                                      menu_selector(S1Main::menuselect));
            CCMenuItemSprite *aItem = m_practiceItem ;
            aItem->setTag(2);
            
            
            aItem->setPosition(s1Position5_macro(aItem));
            aItem->setContentSize(m_highlightSp->getContentSize());
            _menu ->addChild(aItem,1);
            
            m_touchedItem = m_practiceItem;
            
            
            m_practiceLabel = CCLabelTTF::create(s1Str1_macro,s1FontName_macro,s1FontSize_macro);
            CCLabelTTF* pLabel = m_practiceLabel;
            pLabel->setColor(s1White_macro);
            pLabel->setAnchorPoint(ccp(0.5,1.0));
            pLabel->setPosition( ccp(aItem->getPosition().x,aItem->getPosition().y-aItem->getContentSize().height/2+11));
            this->addChild(pLabel, 1);
        }
        
        {
            
            m_prepareSprite = CCSprite::create("pDocumentIcon.png");
            CCSprite * aSprite = m_prepareSprite;
            aSprite->setPosition(s1Position6_macro(aSprite));
            
            this->addChild(aSprite,1);
            
            CCSprite * sprite1 = CCSprite::create();
            CCSprite * sprite2 = CCSprite::create();
            
            m_prepareItem = CCMenuItemSprite::create(
                                                     sprite1,
                                                     sprite2,
                                                     this,
                                                     menu_selector(S1Main::menuselect));
            CCMenuItemSprite *aItem = m_prepareItem ;
            aItem->setTag(3);
            
            aItem->setPosition(s1Position6_macro(aItem));
            aItem->setContentSize(m_highlightSp->getContentSize());
            _menu ->addChild(aItem,1);
            
            m_prepareLabel = CCLabelTTF::create(s1Str2_macro,s1FontName_macro,s1FontSize_macro);
            CCLabelTTF* pLabel = m_prepareLabel;
            pLabel->setColor(s1Blue_macro);
            pLabel->setAnchorPoint(ccp(0.5,1.0));
            pLabel->setPosition( ccp(aItem->getPosition().x,aItem->getPosition().y-aItem->getContentSize().height/2+11) );
            this->addChild(pLabel, 1);
        }
        
        
        {

            m_settingSprite = CCSprite::create("pSettingsIcon.png");
             CCSprite * aSprite = m_settingSprite;
			aSprite->setPosition(s1Position7_macro(aSprite));
            CC_BREAK_IF(! aSprite);
			this->addChild(aSprite,1);
            
			CCSprite * sprite1 = CCSprite::create();
			CCSprite * sprite2 = CCSprite::create();
	
            
			m_setting = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S1Main::menuselect));
            CCMenuItemSprite *aItem = m_setting ;
            aItem->setTag(5);
           
			CC_BREAK_IF(! aItem);
			aItem->setPosition(s1Position7_macro(aItem));
            aItem->setContentSize(m_highlightSp->getContentSize());
			_menu ->addChild(aItem,1);
            
            m_settingLabel= CCLabelTTF::create(s1Str3_macro,s1FontName_macro,s1FontSize_macro);
            CCLabelTTF* pLabel = m_settingLabel;
            pLabel->setColor(s1Blue_macro);
            pLabel->setAnchorPoint(ccp(0.5,1.0));
            pLabel->setPosition( ccp(aItem->getPosition().x,aItem->getPosition().y-aItem->getContentSize().height/2+11) );
            this->addChild(pLabel, 1);
		}

        m_highlightSp->setPosition(ccp(m_practiceSprite->getPosition().x,pTabBar->getPosition().y+pTabBar->getContentSize().height/2));
        CC_BREAK_IF(! m_highlightSp);
        this->addChild(m_highlightSp,1);
		m_highlightSp->setColor(ccc3(200, 200, 200));

		bRet = true;
	} while (0);

	return bRet;
}

void S1Main::menuCloseCallback(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    CCScene *newScene = CCScene::create();
    switch (aItem->getTag())
    {
        case 1:
            newScene->addChild(S2PracticeScene::create());
            
            break;
        case 2:
            newScene->addChild(S3TestMain::create());
            
            break;
            
        default:
            break;
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.3, newScene));//动画过场

}
void S1Main::menuselect(CCObject* pSender)
{
    CCMenuItemSprite * aItem = (CCMenuItemSprite *)pSender;
   
        if (aItem==m_practiceItem)
        {
          
        }
        if (aItem==m_prepareItem)
        {
            CCScene *newScene = CCScene::create();
            
            newScene->addChild(S11PrepareRes::create());
            
            CCDirector::sharedDirector()->replaceScene(newScene);//动画过场
        }
        if (aItem==m_setting)
        {
            CCScene *newScene = CCScene::create();
            
            newScene->addChild(pSetting::create());
            
            CCDirector::sharedDirector()->replaceScene(newScene);//动画过场
        }
}

