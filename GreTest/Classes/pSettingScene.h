//
//  pSettingScene.h
//  GreTest
//
//  Created by lyy on 13-5-3.
//
//

#ifndef __GreTest__pSettingScene__
#define __GreTest__pSettingScene__

#include "cocos2d.h"
#include <string.h>
//#include <vector.h>
#include "cocos-ext.h"

class pSetting : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
public:
    
    virtual bool init();
    
    
    static cocos2d::CCScene* scene();
    
    cocos2d::CCMenu* _menu;
	
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	
    
    void menuselect(CCObject* pSender);
    
    
    cocos2d::CCArray * excelArray;
    
    cocos2d::CCDictionary* plistDic;
    
    cocos2d::CCLabelTTF *titleLabel;
    
    int selectIndex;
    std::map<std::string, std::string> aTTFStrMap;
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
    
    cocos2d::CCSprite * pTabBar;
    cocos2d::CCMenuItemSprite *m_practiceItem, *m_prepareItem, *m_setting;
    cocos2d::CCSprite *m_practiceSprite, *m_prepareSprite, *m_settingSprite;
    cocos2d::CCLabelTTF *m_practiceLabel, *m_prepareLabel, *m_settingLabel;
    cocos2d::CCSprite * m_highlightSp;
    cocos2d::CCMenuItemSprite * m_touchedItem;
    
    
    CREATE_FUNC(pSetting);
};

#endif /* defined(__GreTest__pSettingScene__) */
