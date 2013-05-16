#ifndef __S1MAIN_SCENE_H__
#define __S1MAIN_SCENE_H__

#include "cocos2d.h"
#include <string.h>
#include "SimpleAudioEngine.h"

class S1Main : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

	cocos2d::CCMenu* _menu;
	
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	

    void menuselect(CCObject* pSender);


    cocos2d::CCArray * excelArray;
    
    cocos2d::CCLabelTTF *titleLabel;

    cocos2d::CCSprite * pTabBar;
    cocos2d::CCMenuItemSprite *m_practiceItem, *m_prepareItem, *m_setting;
    cocos2d::CCSprite *m_practiceSprite, *m_prepareSprite, *m_settingSprite;
    cocos2d::CCLabelTTF *m_practiceLabel, *m_prepareLabel, *m_settingLabel;
    cocos2d::CCSprite * m_highlightSp;
    cocos2d::CCMenuItemSprite * m_touchedItem;

    
    
    CREATE_FUNC(S1Main);
    
};

#endif  // __HELLOWORLD_SCENE_H__