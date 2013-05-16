//
//  S11FullScreenScene.cpp
//  GreTest
//
//  Created by lyy on 13-5-7.
//
//

#include "S11FullScreenScene.h"
#include "S11PrepareResScene.h"

#include "AppMacros.h"
#include "ScriptParser.h"
#include "CustomTableViewCell.h"

#include "S1MainScene.h"
#include "pSettingScene.h"



#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define rate1 1.0
#define rate2 1.0

#define s11Position1_macro(aItem) ccp(origin.x+1998/rate1,origin.y+1452/rate2)//pRecButton.png
#define s11Position2_macro(aItem) ccp(origin.x+1998/rate1,origin.y+1452/rate2)//s11FullScreenIcon.png
#define s11Position3_macro(aItem) ccp(origin.x+312/rate1,origin.y+1452/rate2)//leftTitle
#define s11Position4_macro(aItem) ccp(origin.x+1236/rate1,origin.y+1452/rate2)//rightTitle
#define s11Position5_macro(aItem) ccp(origin.x+804/rate1,origin.y+60/rate2)//m_practiceItem
#define s11Position6_macro(aItem) ccp(origin.x+1024/rate1,origin.y+60/rate2)//m_prepareItem
#define s11Position7_macro(aItem) ccp(origin.x+1244/rate1,origin.y+60/rate2)//m_setting

#define s11Position9_macro(aItem) ccp(origin.x+1304/rate1,origin.y+754/rate2)//rightlabel


#define s11Str1_macro "GRE模考"
#define s11Str2_macro "备考资料"
#define s11Str3_macro "设置"


#define s11Size2_macro CCSizeMake(1408/rate1, 1292/rate2)//detail Label size


#define s11FontName_macro "Thonburi"

#define s11TitleFontSize_macro 40
#define s11FontSize_macro 20

#define s11Blue_macro ccc3(168.0,168.0,168.0)

#define s11White_macro ccc3(255.0,255.0,255.0)

USING_NS_CC;
USING_NS_CC_EXT;

CCScene* S11FullScreen::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    S11FullScreen *layer = S11FullScreen::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool S11FullScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //每个项目都要创建的东西
    
    _menu = CCMenu::create(NULL);
    _menu->setPosition(CCPointZero);
    this->addChild(_menu, 101);
  
    
    
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
        this->addChild(aSprite,1);
    }

    
    titleLabel = CCLabelTTF::create(S11PrepareRes::titleString.c_str(),s11FontName_macro,s11TitleFontSize_macro);
    CCLabelTTF* pLabel = titleLabel;
    pLabel->setColor(ccWHITE);
    
    pLabel->setPosition( s11Position1_macro(pLabel));
    pLabel->setPosition( ccp( visibleSize.width/2,pLabel->getPosition().y));
    
    this->addChild(pLabel, 1);

    
    {
        CCSprite * aSprite = CCSprite::create("pRecButton.png");
        aSprite->setPosition(s11Position1_macro(aSprite));
        this->addChild(aSprite,100);
        
        
        CCSprite * aSprite1 = CCSprite::create("s11FullScreenIcon.png");
        aSprite1->setPosition(s11Position1_macro(aItem));
        this->addChild(aSprite1,100);
        
        CCSprite * sprite1 = CCSprite::create();
        CCSprite * sprite2 = CCSprite::create();
        
        CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                           sprite1,
                                                           sprite2,
                                                           this,
                                                           menu_selector(S11FullScreen::menuCloseCallback));
        aItem->setPosition(s11Position1_macro(aItem));
        aItem->setContentSize(aSprite->getContentSize());
        _menu ->addChild(aItem,100);
        
    }

    rightDetailTex = CCLabelTTF::create(S11PrepareRes::detailString.c_str(), "Helvetica", 30.0);
    rightDetailTex->setColor(ccBLACK);
    rightDetailTex-> setDimensions(s11Size2_macro);
    rightDetailTex->setPosition(s11Position9_macro(label));
    this->addChild(rightDetailTex,100);
    rightDetailTex->retain();
    //TabelBar
    
    {
        pTabBar = CCSprite::create("pTabBar.png");
        pTabBar->setAnchorPoint(ccp(0.0,0.0));
        pTabBar->setPosition(CCPointZero);
        
        this->addChild(pTabBar,100);
        
    }
    
    m_highlightSp = CCSprite::create("pTabBarSelectedHighlight.png");
    
    
    {
        
        m_practiceSprite = CCSprite::create("pPencilIcon.png");
        CCSprite * aSprite = m_practiceSprite;
        aSprite->setPosition(s11Position5_macro(aSprite));
        
        this->addChild(aSprite,100);
        
        CCSprite * sprite1 = CCSprite::create();
        CCSprite * sprite2 = CCSprite::create();
        m_practiceItem = CCMenuItemSprite::create(
                                                  sprite1,
                                                  sprite2,
                                                  this,
                                                  menu_selector(S11FullScreen::menuselect));
        CCMenuItemSprite *aItem = m_practiceItem ;
        aItem->setTag(2);
        
        
        aItem->setPosition(s11Position5_macro(aItem));
        aItem->setContentSize(m_highlightSp->getContentSize());
        _menu ->addChild(aItem,100);
        
        m_touchedItem = m_practiceItem;
        
        
        m_practiceLabel = CCLabelTTF::create(s11Str1_macro,s11FontName_macro,s11FontSize_macro);
        CCLabelTTF* pLabel = m_practiceLabel;
        pLabel->setColor(s11White_macro);
        pLabel->setAnchorPoint(ccp(0.5,1.0));
        pLabel->setPosition( ccp(aItem->getPosition().x,aItem->getPosition().y-aItem->getContentSize().height/2+11));
        this->addChild(pLabel, 100);
    }
    
    {
        
        m_prepareSprite = CCSprite::create("pDocumentIconActive.png");
        CCSprite * aSprite = m_prepareSprite;
        aSprite->setPosition(s11Position6_macro(aSprite));
        
        this->addChild(aSprite,100);
        
        CCSprite * sprite1 = CCSprite::create();
        CCSprite * sprite2 = CCSprite::create();
        
        m_prepareItem = CCMenuItemSprite::create(
                                                 sprite1,
                                                 sprite2,
                                                 this,
                                                 menu_selector(S11FullScreen::menuselect));
        CCMenuItemSprite *aItem = m_prepareItem ;
        aItem->setTag(3);
        
        aItem->setPosition(s11Position6_macro(aItem));
        aItem->setContentSize(m_highlightSp->getContentSize());
        _menu ->addChild(aItem,100);
        
        m_prepareLabel = CCLabelTTF::create(s11Str2_macro,s11FontName_macro,s11FontSize_macro);
        CCLabelTTF* pLabel = m_prepareLabel;
        pLabel->setColor(s11Blue_macro);
        pLabel->setAnchorPoint(ccp(0.5,1.0));
        pLabel->setPosition( ccp(aItem->getPosition().x,aItem->getPosition().y-aItem->getContentSize().height/2+11) );
        this->addChild(pLabel, 100);
    }
    
    
    {
        
        m_settingSprite = CCSprite::create("pSettingsIcon.png");
        CCSprite * aSprite = m_settingSprite;
        aSprite->setPosition(s11Position7_macro(aSprite));
        
        this->addChild(aSprite,100);
        
        CCSprite * sprite1 = CCSprite::create();
        CCSprite * sprite2 = CCSprite::create();
        
        
        m_setting = CCMenuItemSprite::create(
                                             sprite1,
                                             sprite2,
                                             this,
                                             menu_selector(S11FullScreen::menuselect));
        CCMenuItemSprite *aItem = m_setting ;
        aItem->setTag(5);
        
        
        aItem->setPosition(s11Position7_macro(aItem));
        aItem->setContentSize(m_highlightSp->getContentSize());
        _menu ->addChild(aItem,100);
        
        m_settingLabel= CCLabelTTF::create(s11Str3_macro,s11FontName_macro,s11FontSize_macro);
        CCLabelTTF* pLabel = m_settingLabel;
        pLabel->setColor(s11Blue_macro);
        pLabel->setAnchorPoint(ccp(0.5,1.0));
        pLabel->setPosition( ccp(aItem->getPosition().x,aItem->getPosition().y-aItem->getContentSize().height/2+11) );
        this->addChild(pLabel, 100);
    }
    
    m_highlightSp->setPosition(ccp(m_prepareSprite->getPosition().x,pTabBar->getPosition().y+pTabBar->getContentSize().height/2));
    
    this->addChild(m_highlightSp,100);
    m_highlightSp->setColor(ccc3(200, 200, 200));
    
    
    return true;
}


void S11FullScreen::menuCloseCallback(CCObject* pSender)
{
    CCScene *newScene = CCScene::create();
    
    newScene->addChild(S11PrepareRes::create());
    
    CCDirector::sharedDirector()->replaceScene(newScene);//动画过场
}
void S11FullScreen::menuselect(CCObject* pSender)
{
    CCMenuItemSprite * aItem = (CCMenuItemSprite *)pSender;
    
    if (aItem==m_practiceItem)
    {
        CCScene *newScene = CCScene::create();
        
        newScene->addChild(S1Main::create());
        
        CCDirector::sharedDirector()->replaceScene(newScene);//动画过场
    }
    if (aItem==m_prepareItem)
    {
        
    }
    if (aItem==m_setting)
    {
        CCScene *newScene = CCScene::create();
        
        newScene->addChild(pSetting::create());
        
        CCDirector::sharedDirector()->replaceScene(newScene);//动画过场
    }
}


