#include "stdafx.h"
#include "WelcomScene.h"

static const char* g_pszName = "WelcomScene";
CWelcomScene::CWelcomScene():m_pkRootScene(0),m_pkExitBtn(0),m_pkStartBtn(0),m_pkStartMenu(0){}
CWelcomScene::~CWelcomScene(){}

const char* CWelcomScene::GetName() const
{
	return g_pszName;
}

bool CWelcomScene::Initialise()
{
	m_pkRootScene = CCScene::node();
	m_pkRootScene->addChild(this);

	if (0 == m_pkRootScene)
	{
		return false;
	}

	if (!InitialiseUI())
	{
		return false;
	}

	m_bIsInit = true;

	return true;
}

bool CWelcomScene::Shutdown()
{
	m_pkRootScene->autorelease();
	autorelease();

	return true;
}

bool CWelcomScene::BeginScene()
{
	if (!g_pGame->RunOrRepeaceScene(m_pkRootScene))
	{
		return false;
	}

	return true;
}

bool CWelcomScene::EndScene()
{
	return true;
}

bool CWelcomScene::init()
{
	return true;
}

bool CWelcomScene::InitialiseUI()
{
	m_pkStartBtn = CCMenuItemImage::itemFromNormalImage(
		"start_common.png","start_press.png",
		this,menu_selector(CWelcomScene::StartButtonCallback));

	m_pkExitBtn = CCMenuItemImage::itemFromNormalImage(
		"exit_common.png","exit_press.png",this,
		menu_selector(CWelcomScene::ExitButtonCallback));

	m_pkCredits = CCMenuItemImage::itemFromNormalImage(
		"credits_common.png","credits_press.png",this,
		menu_selector(CWelcomScene::CreditsButtonCallback));

	m_pkStartBtn->setPosition( ccp(CCDirector::sharedDirector()->
		getWinSize().width / 2, 360) );
	m_pkExitBtn->setPosition( ccp(CCDirector::sharedDirector()->
		getWinSize().width / 2, 300) );
	m_pkCredits->setPosition( ccp(CCDirector::sharedDirector()->
		getWinSize().width / 2, 240) );

	m_pkStartMenu = CCMenu::menuWithItems(m_pkStartBtn,m_pkExitBtn,m_pkCredits,0);

	m_pkStartMenu->setPosition(CCPointZero);

	addChild(m_pkStartMenu,1);

	return true;
}

void CWelcomScene::ExitButtonCallback( CCObject* pSender )
{
	g_pGame->ExitGame();
}

void CWelcomScene::StartButtonCallback( CCObject* pSender )
{
	if (!pSender)
	{
		return;
	}

	g_pGame->LoadGame("GameScene");
	//g_pGame->UnloadGame(g_pszName);
}

void CWelcomScene::CreditsButtonCallback( CCObject* pSender )
{
	if (m_pkStartMenu)
	{
		m_pkStartMenu->setIsVisible(false);
	}

	CCLabelTTF* pkCreditsLable = CCLabelTTF::labelWithString("Credits", "Arial", 64);
	CCLabelTTF* pkProgramerListLable = CCLabelTTF::labelWithString("Programer:", "Consolas", 35);
	CCLabelTTF* pkGuoHaoLable = CCLabelTTF::labelWithString("Hao Guo", "Consolas", 32);
	CCLabelTTF* pkLiuYunLable = CCLabelTTF::labelWithString("Yun Liu", "Consolas", 32);
	CCLabelTTF* pkYangChunlongLable = CCLabelTTF::labelWithString("Chun long Yang", "Consolas", 32);

	pkCreditsLable->setPosition( ccp(CCDirector::sharedDirector()->
		getWinSize().width / 2, 480) );
	pkProgramerListLable->setPosition( ccp(CCDirector::sharedDirector()->
		getWinSize().width / 2 - 100, 360) );
	pkGuoHaoLable->setPosition( ccp(CCDirector::sharedDirector()->
		getWinSize().width / 2, 280) );
	pkLiuYunLable->setPosition( ccp(CCDirector::sharedDirector()->
		getWinSize().width / 2, 240) );
	pkYangChunlongLable->setPosition( ccp(CCDirector::sharedDirector()->
		getWinSize().width / 2, 200) );

	addChild(pkCreditsLable);
	addChild(pkProgramerListLable);
	addChild(pkGuoHaoLable);
	addChild(pkLiuYunLable);
	addChild(pkYangChunlongLable);
}