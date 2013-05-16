//
//  pSettingScene.cpp
//  GreTest
//
//  Created by lyy on 13-5-3.
//
//

#include "pSettingScene.h"

#include "S11PrepareResScene.h"
#include "S1MainScene.h"
#include "AppMacros.h"
#include "CustomTableViewCell.h"
#include "ScriptParser.h"


#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define rate1 1.0
#define rate2 1.0

#define classPlistName_macro "Psetting.plist"

#define s1Str1_macro "GRE模考"
#define s1Str2_macro "备考资料"
#define s1Str3_macro "设置"


#define s1FontName_macro "Thonburi"

#define s1TitleFontSize_macro 40
#define s1FontSize_macro 20

#define s1Blue_macro ccc3(168.0,168.0,168.0)

#define s1White_macro ccc3(255.0,255.0,255.0)



using namespace cocos2d;
using namespace CocosDenshion;
USING_NS_CC_EXT;

CCScene* pSetting::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    pSetting *layer = pSetting::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool pSetting::init()
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
    this->addChild(_menu, 2);
    

    plistDic = CCDictionary::createWithContentsOfFile(classPlistName_macro);
    
    
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
    
    titleLabel = CCLabelTTF::create(s1Str3_macro,s1FontName_macro,s1TitleFontSize_macro);
    CCLabelTTF* pLabel = titleLabel;
    pLabel->setColor(ccWHITE);
    
    pLabel->setPosition( ScriptParser::getPositionFromPlist(plistDic,"titleLabel"));
    pLabel->setPosition( ccp( visibleSize.width/2,pLabel->getPosition().y));
    
    this->addChild(pLabel, 1);
    
    
 
    
    {
        pTabBar = CCSprite::create("pTabBar.png");
        pTabBar->setAnchorPoint(ccp(0.0,0.0));
        pTabBar->setPosition(CCPointZero);
        
        this->addChild(pTabBar,1);
    }
    
    m_highlightSp = CCSprite::create("pTabBarSelectedHighlight.png");
    
    
    {
        
        m_practiceSprite = CCSprite::create("pPencilIcon.png");
        CCSprite * aSprite = m_practiceSprite;
        aSprite->setPosition(ScriptParser::getPositionFromPlist(plistDic,"pPencilIcon"));
        
        this->addChild(aSprite,1);
        
        CCSprite * sprite1 = CCSprite::create();
        CCSprite * sprite2 = CCSprite::create();
        m_practiceItem = CCMenuItemSprite::create(
                                                  sprite1,
                                                  sprite2,
                                                  this,
                                                  menu_selector(pSetting::menuselect));
        CCMenuItemSprite *aItem = m_practiceItem ;
  
        aItem->setPosition(m_practiceSprite->getPosition());
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
        aSprite->setPosition(ScriptParser::getPositionFromPlist(plistDic,"pDocumentIcon"));
        
        this->addChild(aSprite,1);
        
        CCSprite * sprite1 = CCSprite::create();
        CCSprite * sprite2 = CCSprite::create();
        
        m_prepareItem = CCMenuItemSprite::create(
                                                 sprite1,
                                                 sprite2,
                                                 this,
                                                 menu_selector(pSetting::menuselect));
        CCMenuItemSprite *aItem = m_prepareItem ;
 
        aItem->setPosition(m_prepareSprite->getPosition());
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
        
        m_settingSprite = CCSprite::create("pSettingsIconActive.png");
        CCSprite * aSprite = m_settingSprite;
        aSprite->setPosition(ScriptParser::getPositionFromPlist(plistDic,"pSettingsIconActive"));
        
        this->addChild(aSprite,1);
        
        CCSprite * sprite1 = CCSprite::create();
        CCSprite * sprite2 = CCSprite::create();
        
        
        m_setting = CCMenuItemSprite::create(
                                             sprite1,
                                             sprite2,
                                             this,
                                             menu_selector(pSetting::menuselect));
        CCMenuItemSprite *aItem = m_setting ;
        
        aItem->setPosition(m_settingSprite->getPosition());
        aItem->setContentSize(m_highlightSp->getContentSize());
        _menu ->addChild(aItem,1);
        
        m_settingLabel= CCLabelTTF::create(s1Str3_macro,s1FontName_macro,s1FontSize_macro);
        CCLabelTTF* pLabel = m_settingLabel;
        pLabel->setColor(s1Blue_macro);
        pLabel->setAnchorPoint(ccp(0.5,1.0));
        pLabel->setPosition( ccp(aItem->getPosition().x,aItem->getPosition().y-aItem->getContentSize().height/2+11) );
        this->addChild(pLabel, 1);
    }
    
    m_highlightSp->setPosition(ccp(m_setting->getPosition().x,pTabBar->getPosition().y+pTabBar->getContentSize().height/2));
    
    this->addChild(m_highlightSp,1);
    m_highlightSp->setColor(ccc3(200, 200, 200));
    
    
    return true;
}

void pSetting::menuCloseCallback(CCObject* pSender)
{
    
    
    
}
void pSetting::menuselect(CCObject* pSender)
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
        CCScene *newScene = CCScene::create();
        
        newScene->addChild(S11PrepareRes::create());
        
        CCDirector::sharedDirector()->replaceScene(newScene);//动画过场
    }
    if (aItem==m_setting)
    {
        
    }
}


void pSetting::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    //CCLOG("cell touched at index: %i  %i", cell->getIdx(),aTTFArry->count());
    
    /* m_EditBox->setVisible(true);
     
     CCTextFieldTTF * aTextTTF =  ((CCTextFieldTTF * )(aTTFArry->objectAtIndex(cell->getIdx())));
     CCLOG("%s",  aTextTTF->getString());
     m_EditBox->setText( aTextTTF->getString());
     */
    selectIndex = cell->getIdx();
    
}

CCSize pSetting::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSizeMake(table->getContentSize().width, 30.0);
}

CCTableViewCell* pSetting::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell)
    {
        cell = new CustomTableViewCell();
        cell->autorelease();
 
         
         
         CCLabelTTF *label = CCLabelTTF::create("点击输入", "Helvetica", 30.0);
         label->setPosition(CCPointZero);
         label->setString("asdaaaaaaaassdjkjsnfjkasnfkjaskjas");
         label->setAnchorPoint(CCPointZero);
         label->setTag(123);
         cell->addChild(label);
 
     
        if (idx==0)
        {
            selectIndex=0;
        }
    }
    else
    {
        
         CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
       
         std::string idxStr = CCString::createWithFormat("%d",idx)->getCString();

        std::map<std::string,std::string>::iterator aIterator = aTTFStrMap.find(idxStr);
        if (aIterator !=aTTFStrMap.end())
        {
            label->setString(aIterator->second.c_str());
        }
         
    }
    
    
    return cell;
}

unsigned int pSetting::numberOfCellsInTableView(CCTableView *table)
{
    return aTTFStrMap.size();
}
