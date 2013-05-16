//
//  S11FullScreenScene.h
//  GreTest
//
//  Created by lyy on 13-5-7.
//
//

#ifndef __GreTest__S11FullScreenScene__
#define __GreTest__S11FullScreenScene__

#include "cocos2d.h"
#include <string.h>
#include <map>
#include "cocos-ext.h"
#include "S11PrepareResScene.h"


class S11FullScreen : public cocos2d::CCLayer//,public S11PrepareRes
{
public:
    
    virtual bool init();
    
    
    static cocos2d::CCScene* scene();
    
    cocos2d::CCMenu* _menu;
    
    
    std::map<std::string, std::string> scriptMap;//right_TableView_map
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	
    
    void menuselect(CCObject* pSender);
    
    
    cocos2d::CCLabelTTF *titleLabel;
    
    cocos2d::CCLabelTTF * rightDetailTex;
    
    //std::string titleString;

    
    cocos2d::CCSprite * pTabBar;
    cocos2d::CCMenuItemSprite *m_practiceItem, *m_prepareItem, *m_setting;
    cocos2d::CCSprite *m_practiceSprite, *m_prepareSprite, *m_settingSprite;
    cocos2d::CCLabelTTF *m_practiceLabel, *m_prepareLabel, *m_settingLabel;
    cocos2d::CCSprite * m_highlightSp;
    cocos2d::CCMenuItemSprite * m_touchedItem;
    
    
    CREATE_FUNC(S11FullScreen);
};
#endif /* defined(__GreTest__S11PrepareResScene__) */
