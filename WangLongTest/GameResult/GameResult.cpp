#include "stdafx.h"
#include "GameResult.h"

CGameResult::CGameResult():
m_pszName(0),
m_pkRootScene(0),
m_pkBackground(0),
m_pkMenu(0),
m_pkRestartButton(0)
{
	m_pszName = new char[MAX_PATH];
	
	memset(m_pszName,0,sizeof(char) * MAX_PATH);
	memset(&m_kResultInfo,0,sizeof(ResultInfo));

	strcpy_s(m_pszName,MAX_PATH,"GameResult");
}

CGameResult::~CGameResult()
{
	SafeDeleteArray(m_pszName);
}

const char* CGameResult::GetName() const
{
	return m_pszName;
}

bool CGameResult::Initialise()
{
	m_pkRootScene = CCScene::node();

	if (0 == m_pkRootScene)
	{
		return false;
	}

	m_pkRootScene->addChild(this);

	if (!g_pGame->GetLastResultFromVector(m_kResultInfo))
	{
		return false;
	}

	if (!InitialiseUI())
	{
		return false;
	}

	return true;
}

bool CGameResult::Shutdown()
{
	return true;
}

bool CGameResult::BeginScene()
{
	SceneChangeType eType = Scene_None;

	if (m_kResultInfo.bWin)
	{
		eType = Scene_RotoZoom;
	}
	else
	{
		eType = Scene_FadeTR;
	}

	if (!g_pGame->RunOrRepeaceScene(m_pkRootScene,eType,1.0f))
	{
		return false;
	}

	return true;
}

bool CGameResult::EndScene()
{
	removeAllChildrenWithCleanup(true);
	m_pkRootScene->removeAllChildrenWithCleanup(true);

	return true;
}

bool CGameResult::InitialiseUI()
{
	if (m_kResultInfo.bWin)
	{
		m_pkBackground = CCSprite::spriteWithFile("succeeded_background.jpg");
	}
	else
	{
		m_pkBackground = CCSprite::spriteWithFile("faild_background.jpg");
	}

	m_pkRestartButton = CCMenuItemImage::itemFromNormalImage(
		"button\\restart_common.png","button\\restart_pressed.png",
		this,menu_selector(CGameResult::RestartButtonCallback));

	m_pkMenu = CCMenu::menuWithItem(m_pkRestartButton);

	if (0 == m_pkMenu)
	{
		return false;
	}

	addChild(m_pkBackground,0);
	addChild(m_pkMenu,1);

	CCSize kWinSize = g_pGame->GetWindowSize();

	m_pkMenu->setPosition(ccp(0,0));

	m_pkRestartButton->setScale(0.2f);
	m_pkRestartButton->setPosition(ccp(70,70));
	m_pkBackground->setPosition(ccp(kWinSize.width / 2.0f,
		kWinSize.height / 2.0f));

	return true;
}

void CGameResult::RestartButtonCallback( CCObject* pkSender )
{
	CC_ASSERT(pkSender);

	g_pGame->LoadGame("GameScene");
}

bool CGameResult::InitialiseAnimation()
{
	CCSpriteFrameCache* pkCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	if (0 == pkCache)
	{
		return false;
	}

	pkCache->addSpriteFramesWithFile("animation\\lose\\animation.plist");

	CCSpriteBatchNode* pkSheet = 0;

	return true;
}