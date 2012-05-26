#include "stdafx.h"
#include "GameResult.h"

CGameResult::CGameResult():
m_pszName(0),
m_pkRootScene(0),
m_pkBackground(0)
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

	addChild(m_pkBackground,0);

	CCSize kWinSize = g_pGame->GetWindowSize();
	m_pkBackground->setPosition(ccp(kWinSize.width / 2.0f,
		kWinSize.height / 2.0f));

	return true;
}