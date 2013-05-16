#ifndef __TEXTVIEWLAYER_H__
#define __TEXTVIEWLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <string.h>
#include <vector.h>


class TestViewLayer : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate,public cocos2d::extension::CCEditBoxDelegate
{
public:
    virtual bool init();  
    
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
    
    cocos2d::extension::CCTableView* pTableView;
    
    cocos2d::CCSize tableviewSize;
    cocos2d::CCPoint tableviewPosition;
    cocos2d::CCArray * aArray;
    vector<vector<std::string> > aVector;
    int textlineNum;
    
    
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
    
    
    cocos2d::extension::CCEditBox* m_EditBox;
    
    CREATE_FUNC(TestViewLayer);
};

#endif 