#include "stdafx.h"
#include "GameManager.h"
#include "DynamicLibraryManager.h"
#include <algorithm>

BEGIN_KERNEL

CGameManager* CGameManager::ms_pkGameManager = 0;

CGameManager::CGameManager():
m_pszGamePath(0),
m_bIsInit(false),
m_pkCurrentScene(0),
m_pkGameDirector(0)
{
	m_pszGamePath = new char[MAX_PATH];
	m_pkScenes = new SceneVector;

	memset(m_pszGamePath,0,sizeof(char) * MAX_PATH);
}

CGameManager::~CGameManager()
{
	SafeDeleteArray(m_pszGamePath);

	CDynamicLibraryManager::Destroy();
}

bool CGameManager::Create( const char* pszGameModulePath )
{
	CGameManager* pkGM = 0;
	bool bSucceeded = false;

	if (CGameManager::ms_pkGameManager)
	{
		return bSucceeded;
	}

	pkGM = new CGameManager;
	bSucceeded = pkGM->Initialise(pszGameModulePath);

	if (bSucceeded && pkGM)
	{
		CGameManager::ms_pkGameManager = pkGM;
	}

	return bSucceeded;
}

void CGameManager::Destroy()
{
	SafeDelete(CGameManager::ms_pkGameManager);
}

bool CGameManager::Initialise( const char* pszGameModulePath )
{
	if (0 == pszGameModulePath || !*pszGameModulePath)
	{
		return false;
	}

	strcpy_s(m_pszGamePath,MAX_PATH,pszGameModulePath);

	if (!CDynamicLibraryManager::Create(m_pszGamePath))
	{
		return false;
	}

	if (!InitialiseFileEngine())
	{
		return false;
	}

	if (!InitialiseDirector())
	{
		return false;
	}

	m_bIsInit = true;
	return true;
}

bool CGameManager::LoadGame( const char* pszGameName )
{
	if (0 == pszGameName || !*pszGameName)
	{
		return false;
	}

	CDynamicLibrary* pkLibrary = g_pDynLib->
		LoadDynamicLibrary(pszGameName);

	if (0 == pkLibrary)
	{
		return false;
	}

	DLL_START_PLUGIN pFunc = (DLL_START_PLUGIN)pkLibrary->
		GetSysbol("StartPlugin");

	if (!pFunc)
	{
		return false;
	}

	pFunc();

	if (0 == m_pkCurrentScene)
	{
		return false;
	}

	if (!m_pkCurrentScene->BeginScene())
	{
		return false;
	}

	return true;
}

void CGameManager::UnloadGame(){}
void CGameManager::ClearScene( SceneVectorPtr pkScene ){}

bool CGameManager::InitialiseScene( IGameScene* pkGameScene )
{
	if (0 == pkGameScene)
	{
		return false;
	}

	if (find(m_pkScenes->begin(),m_pkScenes->end(),pkGameScene) ==
		m_pkScenes->end())
	{
		m_pkScenes->push_back(pkGameScene);

		if (!pkGameScene->Initialise())
		{
			return false;
		}
		else
		{
			m_pkCurrentScene = pkGameScene;
		}
	}

	return true;
}

bool CGameManager::UninitialiseScene( IGameScene* pkGameScene )
{
	if (0 == pkGameScene)
	{
		return false;
	}

	SceneVector::iterator it = find(m_pkScenes->begin(),
		m_pkScenes->end(),pkGameScene);

	if (m_pkScenes->end() == it)
	{
		return false;
	}

	pkGameScene->Shutdown();

	m_pkScenes->erase(it);

	return true;
}

bool CGameManager::InitialiseDirector()
{
	m_pkGameDirector = CCDirector::sharedDirector();

	if (0 == m_pkGameDirector)
	{
		return false;
	}

	m_pkGameDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());
	m_pkGameDirector->setDisplayFPS(true);
	m_pkGameDirector->setAnimationInterval(1.0f / 30.0f);

	return true;
}

bool CGameManager::InitialiseFileEngine()
{
	CCFileUtils::setResourcePath("data\\");

	return true;
}

bool CGameManager::RunOrRepeaceScene( CCScene* pkScene )
{
	CCScene* pkRunningScene = 0;

	pkRunningScene = m_pkGameDirector->getRunningScene();

	if (0 == pkRunningScene)
	{
		m_pkGameDirector->runWithScene(pkScene);
	}
	else
	{
		if (pkRunningScene == pkScene)
		{
			return false;
		}
		else
		{
			m_pkGameDirector->replaceScene(pkScene);
		}
	}

	return true;
}

END_KERNEL