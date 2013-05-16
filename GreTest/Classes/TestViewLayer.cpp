#include "TestViewLayer.h"


USING_NS_CC;
USING_NS_CC_EXT;

#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点


#define rate1 2.0
#define rate2 2.0

#define s1FontSize5_macro 30/rate1 //m_EditBox

#define FONT_NAME                       "Helvetica"

#define s1Position10_macro(aItem) ccp(origin.x+1474/rate1,origin.y+650/rate2)//m_EditBox

#define s1Size10_macro(aItem) CCSizeMake(1100/rate1,1240/rate2)//

bool TestViewLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF( !CCLayer::init() );
             
		pTableView = CCTableView::create(this, tableviewSize);
		pTableView->setDirection(kCCScrollViewDirectionVertical);
		pTableView->setAnchorPoint(ccp(0,0));
        for (int i =0; i<textlineNum; i++)
        {
            std::string str = "";
            vector<std::string > arrayVect;
            arrayVect.push_back(str.c_str());
            aVector.push_back(arrayVect);
        }
		pTableView->setDelegate(this);
		pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->addChild(pTableView);
		pTableView->reloadData();
        
		bRet = true;
	}while(0);

	return bRet;
}

void TestViewLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
}

CCSize TestViewLayer::tableCellSizeForIndex(CCTableView *table,unsigned int idx)
{

    return CCSizeMake(tableviewSize.width, 35.0);

}

CCTableViewCell* TestViewLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
 
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell)
    {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        CCSprite *pSprite = CCSprite::create("pBackground.png");
        //pSprite->setColor(ccBLUE);
        pSprite->setAnchorPoint(CCPointZero);
		pSprite->setPosition(CCPointZero);
        pCell->addChild(pSprite);

        // bottom
        m_EditBox = cocos2d::extension::CCEditBox::create(CCSizeMake(tableviewSize.width, 30.0), cocos2d::extension::CCScale9Sprite::create());
        m_EditBox->setAnchorPoint(CCPointZero);
        m_EditBox->setPosition(CCPointZero);
        m_EditBox->setPlaceHolder("input");
        m_EditBox->setFont(FONT_NAME,s1FontSize5_macro);
        m_EditBox->setInputMode(cocos2d::extension::kEditBoxInputModeAny);// input model
        
        m_EditBox->setReturnType(cocos2d::extension::kKeyboardReturnTypeDefault);
        m_EditBox->setDelegate(this);
        m_EditBox->setFontColor(ccBLACK);
        m_EditBox->setTag(123);
        pCell->addChild(m_EditBox);
  
    
    }
    else
    {
        
        cocos2d::extension::CCEditBox *m_EditBox = (cocos2d::extension::CCEditBox*)pCell->getChildByTag(123);
        m_EditBox->setText(m_EditBox->getText());
         
    }


    return pCell;
}

unsigned int TestViewLayer::numberOfCellsInTableView(CCTableView *table)
{
 
    return 10;//aVector.size();
}

void TestViewLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{
    CCLog("editBox %p DidBegin !", editBox);
}

void TestViewLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{
    CCLog("editBox %p DidEnd !", editBox);
}

void TestViewLayer::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
    CCLog("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void TestViewLayer::editBoxReturn(cocos2d::extension::CCEditBox* editBox)
{
    CCLog("editBox %p was returned !");
    
    if (m_EditBox == editBox)
    {
        CCLOG("Name EditBox return !");
    }
    
}
