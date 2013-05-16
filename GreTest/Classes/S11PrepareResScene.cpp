//
//  S11PrepareResScene.cpp
//  GreTest
//
//  Created by lyy on 13-5-3.
//
//

#include "S11PrepareResScene.h"

#include "AppMacros.h"
#include "ScriptParser.h"
#include "CustomTableViewCell.h"

#include "S1MainScene.h"
#include "pSettingScene.h"
#include "S11FullScreenScene.h"


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
#define s11Position8_macro(aItem) ccp(origin.x+0/rate1,origin.y+117/rate2)//leftTableView
#define s11Position8_1_macro(aItem) ccp(origin.x+50.0/rate1,origin.y+25.0/rate2)//label of  first cell
#define s11Position9_macro(aItem) ccp(origin.x+1304/rate1,origin.y+754/rate2)//rightlabel



#define s11Str1_macro "GRE模考"
#define s11Str2_macro "备考资料"
#define s11Str3_macro "设置"

#define s11Size1_macro CCSizeMake(1408/2, 1292)//tableview size
#define s11Size2_macro CCSizeMake(1408/rate1, 1292/rate2)//detail Label size


#define s11FontName_macro "Thonburi"

#define s11TitleFontSize_macro 40
#define s11FontSize_macro 20

#define s11Blue_macro ccc3(168.0,168.0,168.0)

#define s11White_macro ccc3(255.0,255.0,255.0)


std::string S11PrepareRes::titleString = "";
std::string  S11PrepareRes::detailString = "";

USING_NS_CC;
USING_NS_CC_EXT;

CCScene* S11PrepareRes::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    S11PrepareRes *layer = S11PrepareRes::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool S11PrepareRes::init()
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
    
    titleString = "";
    
	scriptMap=ScriptParser::paserScript("S11PrepareRes.xml","leftTitle");//right_TableView_Map

 
    
    //背景图
    
    {
        CCSprite * aSprite = CCSprite::create("s11Background.png");
        aSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
        //CC_BREAK_IF(! aSprite);
        this->addChild(aSprite,98);
        aSprite ->getTexture()->setAntiAliasTexParameters();//抗锯齿
    }
    //控件
    
    {
        CCSprite * aSprite = CCSprite::create("s11NavBar.png");
        aSprite->setAnchorPoint(ccp(0.0,1.0));
        aSprite->setPosition(ccp(0,visibleSize.height-40));
        this->addChild(aSprite,100);
    }
    
    
    {
        CCLabelTTF * leftTitleLabel = CCLabelTTF::create(s11Str2_macro,s11FontName_macro,s11TitleFontSize_macro);
        CCLabelTTF* pLabel = leftTitleLabel;
        pLabel->setColor(ccWHITE);
        
        pLabel->setPosition( s11Position3_macro(pLabel));
        this->addChild(pLabel, 100);
    }
    
    titleLabel = CCLabelTTF::create(s11Str2_macro,s11FontName_macro,s11TitleFontSize_macro);
    CCLabelTTF* pLabel = titleLabel;
    pLabel->setColor(ccWHITE);
    
    pLabel->setPosition( s11Position4_macro(pLabel));
    this->addChild(pLabel, 100);
    
    
    
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
                                                           menu_selector(S11PrepareRes::menuCloseCallback));
        aItem->setPosition(s11Position1_macro(aItem));
        aItem->setContentSize(aSprite->getContentSize());
        _menu ->addChild(aItem,100);
        
    }

    
    
    CCTableView * tableView = CCTableView::create(this, s11Size1_macro);
    tableView->setAnchorPoint(ccp(0.0,0.0));
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setPosition(s11Position8_macro(tableView));
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    this->addChild(tableView,99);
    tableView->reloadData();
    

    std::string aStr = ScriptParser::readScript("s11TableCellTxt1.txt");
    S11PrepareRes::detailString = aStr;
    rightDetailTex = CCLabelTTF::create(aStr.c_str(), "Helvetica", 30.0);
    rightDetailTex->setColor(ccBLACK);
    rightDetailTex-> setDimensions(s11Size2_macro);
    rightDetailTex->setPosition(s11Position9_macro(label));
    this->addChild(rightDetailTex,100);
    //TabelBar
    
    {
        pTabBar = CCSprite::create("pTabBar.png");
        pTabBar->setAnchorPoint(ccp(0.0,1.0));
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
                                                  menu_selector(S11PrepareRes::menuselect));
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
                                                 menu_selector(S11PrepareRes::menuselect));
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
                                             menu_selector(S11PrepareRes::menuselect));
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


void S11PrepareRes::menuCloseCallback(CCObject* pSender)
{
 /*
    GameOverScene *gameOverScene = GameOverScene::create();
    gameOverScene->getLayer()->getLabel()->setString("You Lose :[");
    CCDirector::sharedDirector()->replaceScene(gameOverScene);
  */
    
    CCString *aString = CCString::createWithFormat("%u",selectIndex+1);
    std::string aStr = aString->m_sString;
    std::map<std::string,std::string>::iterator aIterator = scriptMap.find(aStr);
    std::string aStr2;
    if (aIterator !=scriptMap.end())
    {
        S11PrepareRes::titleString = aIterator->second;
        S11FullScreen *newScene = S11FullScreen::create();
        
        CCDirector::sharedDirector()->replaceScene((CCScene *)newScene);
    }
    
    
    
    
    /*
    CCScene *scene = About::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2, scene));
    */
    
}
void S11PrepareRes::menuselect(CCObject* pSender)
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


void S11PrepareRes::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    //CCLOG("cell touched at index: %i  %i", cell->getIdx(),aTTFArry->count());
   
    selectIndex = cell->getIdx();
    
    
    std::string aStr;
    switch (selectIndex)
    {
        case 0:
            aStr = ScriptParser::readScript("s11TableCellTxt1.txt");
            break;
        case 1:
            aStr = ScriptParser::readScript("s11TableCellTxt2.txt");
            break;
        case 2:
            aStr = ScriptParser::readScript("s11TableCellTxt3.txt");
            break;
            
        default:
            break;
    }
   
    
    rightDetailTex ->setString(aStr.c_str());
    S11PrepareRes::detailString = aStr;
    table->reloadData();
    
    
}

CCSize S11PrepareRes::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    CCSprite *pSprite = CCSprite::create("s11Active Bar.png");
    float aFloat = pSprite->getContentSize().height;
    return CCSizeMake(table->getContentSize().width, aFloat);
  
}

CCTableViewCell* S11PrepareRes::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell)
    {
        cell = new CustomTableViewCell();
        cell->autorelease();
        if (idx==0)
        {
            selectIndex=0;
        
        }
   
        CCLabelTTF *label = CCLabelTTF::create("点击输入", "Helvetica", 30.0);
        label->setColor(ccBLACK);
        label->setPosition(s11Position8_1_macro(label));
        label->setAnchorPoint(CCPointZero);
        label->setTag(123);
        cell->addChild(label,101);
        
        CCSprite *pSprite = CCSprite::create("s11CellDivideLine.png");
        pSprite->setAnchorPoint(CCPointZero);
		pSprite->setPosition(CCPointZero);
        cell->addChild(pSprite,101);
  
    }
    else
    {
        if (selectIndex ==idx)
        {
            if (activeSprite)
            {
                activeSprite->removeFromParentAndCleanup(false);
            }

            
            activeSprite = CCSprite::create("s11Active Bar.png");
            activeSprite->setAnchorPoint(CCPointZero);
            activeSprite->setPosition(CCPointZero);
            cell->addChild(activeSprite,99);
        }
        
         CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        CCString *aString = CCString::createWithFormat("%u",idx+1);
        std::string aStr = aString->m_sString;
        std::map<std::string,std::string>::iterator aIterator = scriptMap.find(aStr);
        std::string aStr2;
        if (aIterator !=scriptMap.end())
        {
            aStr2 = aIterator->second;
        }
        
        label->setString(aStr2.c_str());
  
    }
    
    return cell;
}

unsigned int S11PrepareRes::numberOfCellsInTableView(CCTableView *table)
{
    return scriptMap.size();
}

