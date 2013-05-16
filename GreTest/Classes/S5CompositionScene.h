#ifndef __S5COMPOSITION_SCENE_H__
#define __S5COMPOSITION_SCENE_H__

#include "cocos2d.h"
#include <string.h>
#include <vector.h>
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

class KeyboardNotificationLayer;

class S5Composition : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate,public cocos2d::extension::CCEditBoxDelegate,public cocos2d::CCTextFieldDelegate,public cocos2d::CCIMEDelegate
{
public:

    virtual bool init();  

    static cocos2d::CCScene* scene();

	cocos2d::CCMenu* _menu;
	
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    vector<vector< std::string> > s1ParserExcl();

    
    
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
    

    cocos2d::extension::CCEditBox* m_EditBox;

    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

    
    
    //启动虚拟键盘时的回调函数
    virtual bool onTextFieldAttachWithIME(cocos2d::CCTextFieldTTF *pSender);
 
    
    //关闭虚拟键盘时的回调函数
    virtual bool onTextFieldDetachWithIME(cocos2d::CCTextFieldTTF *pSender);
  
    //进行输入时的回调函数
    virtual bool onTextFieldInsertText(cocos2d::CCTextFieldTTF *pSender, const char *text, int nLen);
    
    
    //删除文字时的回调函数
    virtual bool onTextFieldDeleteBackward(cocos2d::CCTextFieldTTF *pSender, const char *delText, int nLen);
 
    /*
    virtual std::string subtitle() = 0;
    virtual void onClickTrackNode(bool bClicked) = 0;
    
    virtual void registerWithTouchDispatcher();
    virtual void keyboardWillShow(cocos2d::CCIMEKeyboardNotificationInfo& info);
    
    // CCLayer
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    CCNode * m_pTrackNode;
    cocos2d::CCPoint  m_beginPos;
    */
    std::vector<cocos2d::CCTextFieldTTF *> aTTFVect;
    cocos2d::CCArray * aTTFArry ;
    int selectIndex;
    // implement the "static node()" method manually
    CREATE_FUNC(S5Composition);
   
};

#endif  // __S5COMPOSITION_SCENE_H__