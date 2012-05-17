#include "stdafx.h"
#include "GameManager.h"
#include "DynamicLibraryManager.h"
#include <algorithm>

BEGIN_KERNEL

CGameManager* CGameManager::ms_pkGameManager = 0;

CGameManager::CGameManager():
m_pszGamePath(0),
m_bIsInit(false),
m_pkCurrentScene(0)
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

	return true;
}

void CGameManager::UnloadGame()
{

}

bool CGameManager::InstallPlugin( IGameScene* pkPlugin )
{
	if (0 == pkPlugin)
	{
		return false;
	}

	if (!pkPlugin->Install())
	{
		return false;
	}

	if (find(m_pkScenes->begin(),m_pkScenes->end(),pkPlugin) ==
		m_pkScenes->end())
	{
		m_pkScenes->push_back(pkPlugin);

		if (!pkPlugin->Initialise())
		{
			return false;
		}
	}

	return true;
}

bool CGameManager::UninstallPlugin( IGameScene* pkPlugin )
{
	if (0 == pkPlugin)
	{
		return false;
	}

	SceneVector::iterator it = find(m_pkScenes->begin(),
		m_pkScenes->end(),pkPlugin);

	if (m_pkScenes->end() == it)
	{
		return false;
	}

	pkPlugin->Shutdown();
	pkPlugin->Uninstall();

	m_pkScenes->erase(it);

	return true;
}

void CGameManager::ClearScene( SceneVectorPtr pkScene )
{

}

END_KERNEL