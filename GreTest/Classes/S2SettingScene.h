#ifndef __S2Setting_SCENE_H__
#define __S2Setting_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

class S2Setting : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    std::vector<std::string> aVectorCellValue;
    cocos2d::CCArray* _arrayCellValue;
    
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
    
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
    
	
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	cocos2d::CCMenu* _menu;
	
    // a selector callback
    void menuOnBackCallback(CCObject* pSender);
	void menuShowPracticeList(CCObject* pSender);
	void menuOnPencil(CCObject* pSender);
    void menuOnDocument(CCObject* pSender);
    void menuOnSettings(CCObject* pSender);
    
	//static inline CCPoint s2HelpIconPosition_macro(){return ccp(1998,1452);}
	//static inline CCPoint s2PracticeButton_macro(){return ccp(512,750);}
	//static inline CCPoint s2TestButton_macro(){return ccp(1536,750);}

	
    // implement the "static node()" method manually
    CREATE_FUNC(S2Setting);
};

#endif  // __HELLOWORLD_SCENE_H__