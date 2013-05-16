#include "S5CompositionScene.h"
#include "AppMacros.h"
#include "ExcelParser.h"
#include "ListViewLayer.h"
#include "TestViewLayer.h"
#include "CustomTableViewCell.h"


using namespace cocos2d;
USING_NS_CC_EXT;

#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点


#define rate1 1.0
#define rate2 1.0

#define s1Position1_macro(aItem) ccp(origin.x+250/rate1,origin.y+1460/rate2)//title1
#define s1Position2_macro(aItem) ccp(origin.x+1024/rate1,origin.y+1340/rate2)//title2
#define s1Position3_macro(aItem) ccp(origin.x+1680/rate1,origin.y+1430/rate2)//quit
#define s1Position4_macro(aItem) ccp(origin.x+1822/rate1,origin.y+1430/rate2)//help
#define s1Position5_macro(aItem) ccp(origin.x+1962/rate1,origin.y+1430/rate2)//next
#define s1Position6_macro(aItem) ccp(origin.x+1792/rate1,origin.y+1340/rate2)//hidetime
#define s1Position7_macro(aItem) ccp(origin.x+1954/rate1,origin.y+1340/rate2)//timelabel
/*
#define s1Position8_macro(aItem) ccp(origin.x+452/rate1-150,origin.y+1190/rate2-70)//tableview1
#define s1Position9_macro(aItem) ccp(origin.x+452/rate1-150,origin.y+550/rate2-320)//tableview2
#define s1Position10_macro(aItem) ccp(origin.x+1474/rate1-(1100/rate1)/2,origin.y+650/rate2-(1240/rate2)/2)//m_EditBox
 */
#define s1Position8_macro(aItem) ccp(origin.x+452/rate1-410,origin.y+1190/rate2-70)//tableview1
#define s1Position9_macro(aItem) ccp(origin.x+452/rate1-410,origin.y+550/rate2-550)//tableview2
#define s1Position10_macro(aItem) ccp(origin.x+1474/rate1-(1100/rate1)/2,origin.y+650/rate2-(1240/rate2)/2)//m_EditBox



#define s1FontSize1_macro 48/rate1 //title1
#define s1FontSize2_macro 30/rate1 //title2
#define s1FontSize3_macro 30/rate1 //pHidetimeShowtimeButton
#define s1FontSize4_macro 30/rate1 //timelabel
#define s1FontSize5_macro 30/rate1 //m_EditBox

#define FONT_NAME                       "Helvetica"



#define s1Size8_macro(aItem) CCSizeMake(820/rate1,160/rate2)//
#define s1Size9_macro(aItem) CCSizeMake(820/rate1,1040/rate2)//
#define s1Size10_macro(aItem) CCSizeMake(1100/rate1,1240/rate2)//

#define s1Str1_macro "Test 1 Section 1 of 5"//title1
#define s1Str2_macro "Question 1 of 2"//title2
#define s1Str6_macro "Hide Time"//title2
#define s1Str7_macro "00:30:00"//timelabel
#define excelFileName_macro "test1.xml"

CCScene* S5Composition::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		S5Composition *layer = S5Composition::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool S5Composition::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
        
        
		//每个项目都要创建的东西

		_menu = CCMenu::create(NULL);
		_menu->setPosition(CCPointZero);
		CC_BREAK_IF(! _menu);

		this->addChild(_menu, 100);

        setTouchEnabled(true);
       // CCDirector* pDirector = CCDirector::sharedDirector();
        //pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
        
        {
			CCSprite * aSprite = CCSprite::create("pBackground.png");
			aSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
            CC_BREAK_IF(! aSprite);
			this->addChild(aSprite,1);
            aSprite ->getTexture()->setAntiAliasTexParameters();//抗锯齿
		}
        //背景图
        
		{
			CCSprite * aSprite = CCSprite::create("s5WrittingBackground.png");
			//aSprite->setPosition(ccp(visibleSize.width / 2+160, (visibleSize.height/2-110)));
            aSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height/2));
            CC_BREAK_IF(! aSprite);
			this->addChild(aSprite,1);
            aSprite ->getTexture()->setAntiAliasTexParameters();//抗锯齿
            
		}
        //控件
        {
            string str = s1Str1_macro;
            CCLabelTTF* label = CCLabelTTF::create(str.c_str(), FONT_NAME, s1FontSize1_macro);
            addChild(label, 100);
            label->setPosition(s1Position1_macro(aItem));
            label ->setColor(ccBLACK);
        }
        
        {
            string str = s1Str2_macro;
            CCLabelTTF* label = CCLabelTTF::create(str.c_str(), FONT_NAME, s1FontSize2_macro);
            addChild(label, 100);
            label->setPosition(s1Position2_macro(aItem));
            label ->setColor(ccBLACK);
        }
        
		{
			CCSprite * sprite1 = CCSprite::create("pQuitButton.png");
			CCSprite * sprite2 = CCSprite::create("pQuitButton.png");
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S5Composition::menuCloseCallback));
			CC_BREAK_IF(! aItem);
			aItem->setPosition(s1Position3_macro(aItem));
            aItem->setScale(0.8);
			_menu ->addChild(aItem,100);
		}
        
		{
			CCSprite * sprite1 = CCSprite::create("pHelpButton.png");
			CCSprite * sprite2 = CCSprite::create("pHelpButton.png");
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S5Composition::menuCloseCallback));
			CC_BREAK_IF(! aItem);
			aItem->setPosition(s1Position4_macro(aItem));
            aItem->setScale(0.8);
			_menu ->addChild(aItem,100);
		}
        
        {
			CCSprite * sprite1 = CCSprite::create("pNextButton.png");
			CCSprite * sprite2 = CCSprite::create("pNextButton.png");
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S5Composition::menuCloseCallback));
			CC_BREAK_IF(! aItem);
			aItem->setPosition(s1Position5_macro(aItem));
            aItem->setScale(0.8);
			_menu ->addChild(aItem,100);
		}
		
        {
			CCSprite * sprite1 = CCSprite::create("pHidetimeShowtimeButton.png");
			CCSprite * sprite2 = CCSprite::create("pHidetimeShowtimeButton.png");
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S5Composition::menuCloseCallback));
			CC_BREAK_IF(! aItem);
			aItem->setPosition(s1Position6_macro(aItem));
            
			_menu ->addChild(aItem,100);
            
            string str = s1Str6_macro;
            CCLabelTTF* label = CCLabelTTF::create(str.c_str(), FONT_NAME, s1FontSize3_macro);
            addChild(label, 100);
            label->setPosition(s1Position6_macro(aItem));
            label ->setColor(ccBLACK);
		}
        //timelabel
		{
            string str = s1Str7_macro;
            CCLabelTTF* label = CCLabelTTF::create(str.c_str(), FONT_NAME, s1FontSize4_macro);
            addChild(label, 100);
            label->setPosition(s1Position7_macro(aItem));
            label ->setColor(ccBLACK);
        }
        
        
        
        
        
        vector<vector<string> > vector1 = s1ParserExcl();
        
        
        /*
        
        CCString * string1 = CCString::createWithFormat(RequirementStr.c_str());
        CCArray * aTTFArry = CCArray::create();
        aArray->addObject(string1);
        CCLOG("%s",((CCString * )aArray->objectAtIndex(0))->getCString());
        */
        
        
        
     
        {
            vector<string > RequirementVector = vector1[1];
            string RequirementStr = RequirementVector[2];
            
            vector<string > arrayVect;
            arrayVect.push_back(RequirementStr.c_str());
            
            
            ListViewLayer * listViewLayer = new(ListViewLayer);
            listViewLayer->setPosition(s1Position8_macro(listViewLayer));
            listViewLayer->setContentSize(s1Size8_macro(listViewLayer));
            listViewLayer->tableviewSize = s1Size8_macro(listViewLayer);
            listViewLayer->aVect = arrayVect;
            //memory Control
            
             if (listViewLayer && listViewLayer->init())
             {
             listViewLayer->autorelease();
             }
             else
             {
             CC_SAFE_DELETE(listViewLayer);
             }
             
            this ->addChild(listViewLayer,99);
            
        }
        
        {
            vector<string > vector2 = vector1[1];
            string str = vector2[1];
            // CCLOG("%s",str.c_str());
            vector<string > arrayVect;
            arrayVect.push_back(str.c_str());
            
            ListViewLayer * listViewLayer = new(ListViewLayer);
            listViewLayer->setPosition(s1Position9_macro(listViewLayer));
            listViewLayer->setContentSize(s1Size9_macro(listViewLayer));
            listViewLayer->tableviewSize = s1Size9_macro(listViewLayer);
            listViewLayer->aVect = arrayVect;
            //memory Control
            
            if (listViewLayer && listViewLayer->init())
            {
                listViewLayer->autorelease();
            }
            else
            {
                CC_SAFE_DELETE(listViewLayer);
            }
            
            this ->addChild(listViewLayer,99);
        }
    
        aTTFArry = CCArray::create();
        for (int i= 0; i<20; i++)
        {
            CCString * aStr=CCString::create("");
            aTTFArry->addObject(aStr);
        }
     
        
        CCTableView * tableView = CCTableView::create(this, s1Size10_macro(tableView));
        tableView->setAnchorPoint(ccp(0.0,0.0));
        tableView->setDirection(kCCScrollViewDirectionVertical);
        tableView->setPosition(s1Position10_macro(tableView));
        tableView->setDelegate(this);
        tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->addChild(tableView,99);
        tableView->reloadData();
        

        /*
        //m_EditBox = CCEditBox::create(CCSizeMake(tableView->getContentSize().width, 60.0), CCScale9Sprite::create());
        m_EditBox = CCEditBox::create(CCSizeMake(1100/2, 60.0), CCScale9Sprite::create());
        m_EditBox->setVisible(false);
        m_EditBox->setAnchorPoint(ccp(1.0,1.0));
        //m_EditBox->setPosition(ccp(tableView->getPosition().x, tableView->getPosition().y));
        m_EditBox->setPosition(ccp(1500, 130));
        m_EditBox->setPlaceHolder("input");
        m_EditBox->setFont(FONT_NAME,s1FontSize5_macro);
        m_EditBox->setInputMode(kEditBoxInputModeAny);// input model
   
        
        m_EditBox->setReturnType(kKeyboardReturnTypeDefault);
        m_EditBox->setDelegate(this);
        m_EditBox->setFontColor(ccBLACK);
        m_EditBox->setTag(123);
        this->addChild(m_EditBox,99);
   */
		bRet = true;
	} while (0);

	return bRet;
}
vector<vector< std::string> > S5Composition::s1ParserExcl()
{
    CCFileUtils* aCCFileUtils = CCFileUtils::sharedFileUtils();
    std::string documentPath = aCCFileUtils->getWritablePath();
    
    string fileName = excelFileName_macro;
    
    string filePath = documentPath + fileName;
    
    string path = filePath;
    FILE *fp =fopen(path.c_str(),"r");//根据路径打开文件
    
    char *pchBuf = NULL;//将要取得的字符串
    int  nLen = 0;//将要取得的字符串长度
    fseek(fp,0,SEEK_END);//文件指针移到文件尾
    nLen =ftell(fp); //得到当前指针位置,即是文件的长度
    rewind(fp);   //文件指针恢复到文件头位置
    
    //动态申请空间,为保存字符串结尾标志\0,多申请一个字符的空间
    pchBuf = (char*)malloc(sizeof(char)*nLen+1);
    if(!pchBuf)
    {
        // perror("内存不够!\n");
        exit(0);
    }
    
    //读取文件内容//读取的长度和源文件长度有可能有出入，这里自动调整 nLen
    nLen =fread(pchBuf,sizeof(char), nLen, fp);
    
    pchBuf[nLen] ='\0';//添加字符串结尾标志
    
    //printf("%s\n", pchBuf);//把读取的内容输出到屏幕看看
    string detailStr = pchBuf;
    fclose(fp); //关闭文件
    free(pchBuf);//释放空间
    
    //CCLOG("%s",detailStr.c_str());
    vector<vector<string> > aVector = ExcelParser::paserExcel(detailStr);
    
    return aVector;
    
}
void S5Composition::menuCloseCallback(CCObject* pSender)
{
    /*
    CCScene *newScene = CCScene::create();
    newScene->addChild(HelloWorld::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.5, newScene));//动画过场
*/
}


void S5Composition::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{
 


    CCLog("editBox %p DidBegin !", editBox);
}

void S5Composition::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{

   

    CCLog("editBox %p DidEnd !", editBox);
}

void S5Composition::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
   //aTTFArry->replaceObjectAtIndex(selectIndex,((CCString *)editBox->getText()),true);

    CCLog("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void S5Composition::editBoxReturn(cocos2d::extension::CCEditBox* editBox)
{
    CCLog("editBox %p was returned !");
    /*CCTextFieldTTF * aTextTTF =  ((CCTextFieldTTF * )(aTTFArry->objectAtIndex(selectIndex)));
    
    aTextTTF->setString(m_EditBox->getText());
    CCLog("editBoxString %s",m_EditBox->getText());
     */
    /*
    if (m_EditBox == editBox)
    {
        CCLOG("Name EditBox return !");
    }
    */
}


void S5Composition::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    //CCLOG("cell touched at index: %i  %i", cell->getIdx(),aTTFArry->count());
    
   /* m_EditBox->setVisible(true);
 
   CCTextFieldTTF * aTextTTF =  ((CCTextFieldTTF * )(aTTFArry->objectAtIndex(cell->getIdx())));
   CCLOG("%s",  aTextTTF->getString());
    m_EditBox->setText( aTextTTF->getString());
    */
    selectIndex = cell->getIdx();
    
}

CCSize S5Composition::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSizeMake(table->getContentSize().width, 30.0);
}

CCTableViewCell* S5Composition::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell)
    {
        cell = new CustomTableViewCell();
        cell->autorelease();
      
        /*
        CCTextFieldTTF* textField = CCTextFieldTTF::textFieldWithPlaceHolder("点击输入", "Helvetica", 24);
        //textField->setContentSize(CCSizeMake(table->getContentSize().width, 24));
       // textField->setPosition(CCPointZero);
        textField->setAnchorPoint(ccp(0.0,1.0));
        textField->setPosition(CCPointZero);
        //textField->setString("asdaaaaaaaassdjkjsnfjkasnfkjaskjas");
        textField->setTag(123);
        
      
        CCLabelTTF *label = CCLabelTTF::create("点击输入", "Helvetica", 30.0);
        label->setPosition(CCPointZero);
        label->setString("asdaaaaaaaassdjkjsnfjkasnfkjaskjas");
		label->setAnchorPoint(CCPointZero);
        label->setTag(123);
        cell->addChild(label);
        aTTFArry->addObject(label->getCString());
         */
        //m_EditBox = CCEditBox::create(CCSizeMake(tableView->getContentSize().width, 60.0), CCScale9Sprite::create());
        CCEditBox * m_EditBox1 = CCEditBox::create(CCSizeMake(1100/2, 60.0), CCScale9Sprite::create());
        m_EditBox1->setPosition(CCPointZero);
        m_EditBox1->setPlaceHolder("input");
        m_EditBox1->setFont(FONT_NAME,s1FontSize5_macro);
        m_EditBox1->setInputMode(kEditBoxInputModeAny);// input model
        m_EditBox1->setText("asdasdahjsdjkah");
        
        m_EditBox1->setReturnType(kKeyboardReturnTypeDefault);
        m_EditBox1->setDelegate(this);
        m_EditBox1->setFontColor(ccBLACK);
        m_EditBox1->setTag(123);
        cell->addChild(m_EditBox1,99);
        if (idx==0)
        {
            selectIndex=0;
            m_EditBox1->attachWithIME();
        }
    }
    else
    {
        /*
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(aTTFArry->objectAtIndex(idx));
        */
        
        CCEditBox * m_EditBox1 = (CCEditBox*)cell->getChildByTag(123);
        
        CCLog("kkk==%i",idx);
            std::string aStr = (((CCString * )aTTFArry->objectAtIndex(idx))->getCString());
            m_EditBox1->setText(aStr.c_str());
        
  
    }
    
    
    return cell;
}

unsigned int S5Composition::numberOfCellsInTableView(CCTableView *table)
{
    return 20;
}

//启动虚拟键盘时的回调函数
bool S5Composition::onTextFieldAttachWithIME(CCTextFieldTTF *pSender)
{
    CCLOG("启动输入");
    return false;
    //    return true; 不启动
}

//关闭虚拟键盘时的回调函数
bool S5Composition::onTextFieldDetachWithIME(CCTextFieldTTF *pSender)
{
    CCLOG("关闭输入");
    return false;
    //    return true; 不关闭
}

//进行输入时的回调函数
bool S5Composition::onTextFieldInsertText(CCTextFieldTTF *pSender, const char *text, int nLen)
{
    CCLOG("输入字符");
    return false;
    //    return true; 不输入
}

//删除文字时的回调函数
bool S5Composition::onTextFieldDeleteBackward(CCTextFieldTTF *pSender, const char *delText, int nLen)
{
    CCLOG("删除字符");
    return false;
    //    return true; 不删除
}
/*
std::string S5Composition::subtitle()
{
    return "CCTextFieldTTF with action and char limit test";
}

void S5Composition::onClickTrackNode(bool bClicked)
{
    CCTextFieldTTF * pTextField = (CCTextFieldTTF*)m_pTrackNode;
    if (bClicked)
    {
        // TextFieldTTFTest be clicked
        CCLOG("TextFieldTTFActionTest:CCTextFieldTTF attachWithIME");
        pTextField->attachWithIME();
    }
    else
    {
        // TextFieldTTFTest not be clicked
        CCLOG("TextFieldTTFActionTest:CCTextFieldTTF detachWithIME");
        pTextField->detachWithIME();
    }
}

void S5Composition::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

void S5Composition::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{*/
    /*CCLOG("TextInputTest:keyboardWillShowAt(origin:%f,%f, size:%f,%f)",
          info.end.origin.x, info.end.origin.y, info.end.size.width, info.end.size.height);
    
    if (! m_pTrackNode)
    {
        return;
    }
    
    CCRect rectTracked = getRect(m_pTrackNode);
    CCLOG("TextInputTest:trackingNodeAt(origin:%f,%f, size:%f,%f)",
          rectTracked.origin.x, rectTracked.origin.y, rectTracked.size.width, rectTracked.size.height);
    
    // if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
    if (! rectTracked.intersectsRect(info.end))
    {
        return;
    }
    
    // assume keyboard at the bottom of screen, calculate the vertical adjustment.
    float adjustVert = info.end.getMaxY() - rectTracked.getMinY();
    CCLOG("TextInputTest:needAdjustVerticalPosition(%f)", adjustVert);
    
    // move all the children node of KeyboardNotificationLayer
    CCArray * children = getChildren();
    CCNode * node = 0;
    int count = children->count();
    CCPoint pos;
    for (int i = 0; i < count; ++i)
    {
        node = (CCNode*)children->objectAtIndex(i);
        pos = node->getPosition();
        pos.y += adjustVert;
        node->setPosition(pos);
    }
*/
/*}
// CCLayer function

bool S5Composition::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("++++++++++++++++++++++++++++++++++++++++++++");
    m_beginPos = pTouch->getLocation();
    return true;
}

void S5Composition::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{*/
    /*if (! m_pTrackNode)
    {
        return;
    }
    
    CCPoint endPos = pTouch->getLocation();
    
    float delta = 5.0f;
    if (::abs(endPos.x - m_beginPos.x) > delta
        || ::abs(endPos.y - m_beginPos.y) > delta)
    {
        // not click
        m_beginPos.x = m_beginPos.y = -1;
        return;
    }
    
    // decide the trackNode is clicked.
    CCRect rect;
    CCPoint point = convertTouchToNodeSpaceAR(pTouch);
    CCLOG("KeyboardNotificationLayer:clickedAt(%f,%f)", point.x, point.y);
    
    rect = getRect(m_pTrackNode);
    CCLOG("KeyboardNotificationLayer:TrackNode at(origin:%f,%f, size:%f,%f)",
          rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    
    this->onClickTrackNode(rect.containsPoint(point));
    CCLOG("----------------------------------");*/
/*}
*/


