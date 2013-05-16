#ifndef __LISTVIEWLAYER_H__
#define __LISTVIEWLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <string.h>
#include <vector.h>

class ListViewLayer : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
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
    vector<std::string > aVect;
    
    CREATE_FUNC(ListViewLayer);
};

#endif 