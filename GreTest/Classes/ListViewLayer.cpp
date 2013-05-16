#include "ListViewLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;


bool ListViewLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF( !CCLayer::init() );
             
		pTableView = CCTableView::create(this, tableviewSize);
		pTableView->setDirection(kCCScrollViewDirectionVertical);
		//pTableView->setPosition(tableviewPosition);
        //pTableView->setPosition//(ccp(-(this->getContentSize().width/2),-(this->getContentSize().height/2)));//(ccp(-(this->getContentSize().width/8),-(this->getContentSize().height/8)));
		pTableView->setDelegate(this);
		pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->addChild(pTableView);
		pTableView->reloadData();

		bRet = true;
	}while(0);

	return bRet;
}

void ListViewLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
}

CCSize ListViewLayer::tableCellSizeForIndex(CCTableView *table,unsigned int idx)
{
    const char * str = aVect[idx].c_str();
    
    CCLabelTTF *pLabel = CCLabelTTF::create(str, "Arial", 20.0,CCSizeMake(table->getContentSize().width, 0), kCCTextAlignmentLeft);
    CCLOG("%f",pLabel->getContentSize().height);
    
    return pLabel->getContentSize();

}

CCTableViewCell* ListViewLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    //CCString *pString = (CCString *)aArray->objectAtIndex(idx);
    const char * str = aVect[idx].c_str();
    CCLOG("%s\n/////////",str);
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
       /* CCSprite *pSprite = CCSprite::create("pBackground.png");
        //pSprite->setColor(ccBLUE);
        pSprite->setAnchorPoint(CCPointZero);
		pSprite->setPosition(CCPointZero);
        pCell->addChild(pSprite);
*/
        CCLabelTTF *pLabel = CCLabelTTF::create(str, "Arial", 20.0,CCSizeMake(table->getContentSize().width, 0), kCCTextAlignmentLeft);
        pLabel->setPosition(CCPointZero);
		pLabel->setAnchorPoint(CCPointZero);
        pLabel->setTag(123);
        pLabel->setColor(ccBLACK);
        //pLabel->setContentSize(CCSizeMake(table->getContentSize().width-60, 120));
        pCell->addChild(pLabel);
    }
    else
    {
        CCLabelTTF *pLabel = (CCLabelTTF*)pCell->getChildByTag(123);
        pLabel->setString(str);
    }


    return pCell;
}

unsigned int ListViewLayer::numberOfCellsInTableView(CCTableView *table)
{
    CCLOG("%d",aVect.size());
    return aVect.size();
}


