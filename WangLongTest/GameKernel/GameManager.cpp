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
m_pkResults(0),
m_pkGameDirector(0)
{
	m_pszGamePath = new char[MAX_PATH];
	m_pkScenes = new SceneVector;
	m_pkResults = new ResultVector;

	memset(m_pszGamePath,0,sizeof(char) * MAX_PATH);
}

CGameManager::~CGameManager()
{
	SafeDeleteArray(m_pszGamePath);

// 	ClearScene(m_pkScenes);
// 	SafeDelete(m_pkScenes);

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

bool CGameManager::UnloadGame(const char* pszGameName)
{
	if (0 == pszGameName || !*pszGameName)
	{
		return false;
	}

	CDynamicLibrary* pkLib = 0;

	if (0 == (pkLib = g_pDynLib->GetLibrary(pszGameName)))
	{
		return false;
	}

	DLL_STOP_PLUGIN pFunc = (DLL_STOP_PLUGIN)pkLib->
		GetSysbol("StopPlugin");

	if (!pFunc)
	{
		return false;
	}

	pFunc();

	//g_pDynLib->UnloadDynamicLibrary(pszGameName);

	return true;
}

void CGameManager::ClearScene( SceneVectorPtr pkScene )
{
	if (0 == pkScene)
	{
		return;
	}

	StringVector kStringVector;

	for (unsigned uiIndex = 0;uiIndex < pkScene->size();uiIndex++)
	{
		IGameScene* pkTempScene = (*pkScene)[uiIndex];

		if (0 == pkTempScene)
		{
			continue;
		}

		string strName = pkTempScene->GetName();
		kStringVector.push_back(strName);
	}

	for (unsigned int i = 0;i < kStringVector.size();i++)
	{
		string strName = kStringVector[i];

		if (!UnloadGame(strName.c_str()))
		{
			continue;
		}
	}

	kStringVector.clear();
	m_pkScenes->clear();
}

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

	pkGameScene->EndScene();
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
	m_kWindowSize = m_pkGameDirector->getWinSize();

	return true;
}

bool CGameManager::InitialiseFileEngine()
{
	CCFileUtils::setResourcePath("data\\");

	return true;
}

bool CGameManager::RunOrRepeaceScene( CCScene* pkScene,
									 SceneChangeType eType,
									 float fTime)
{
	CCScene* pkRunningScene = 0;

	pkRunningScene = m_pkGameDirector->getRunningScene();

	if (0 == pkRunningScene)
	{
		m_pkGameDirector->runWithScene(pkScene);
	}
	else
	{
		ccColor3B kColor = {255,255,255};

		switch (eType)
		{
		case Scene_None:
			{
				Sleep(static_cast<unsigned int>(fTime * 1000.0f));
				m_pkGameDirector->replaceScene(pkScene);
			}
			break;
		case Scene_PageTurn:
			{
				CCTransitionPageTurn* pkTrans = 
					CCTransitionPageTurn::transitionWithDuration(fTime,pkScene,true);

				m_pkGameDirector->replaceScene(pkTrans);
			}
			break;
		case Scene_Fade:
			{
				ccColor3B kColor = {255,255,255};

				CCTransitionFade* pkTrans = 
					CCTransitionFade::transitionWithDuration(fTime,pkScene,kColor);

				m_pkGameDirector->replaceScene(pkTrans);
			}
			break;
		case Scene_SpriteCols:
			{
				CCTransitionSplitCols* pkTrans = 
					CCTransitionSplitCols::transitionWithDuration(fTime,pkScene);

				m_pkGameDirector->replaceScene(pkTrans);
			}
			break;
		case Scene_FadeTR:
			{
				CCTransitionFadeTR* pkTrans = 
					CCTransitionFadeTR::transitionWithDuration(fTime,pkScene);

				m_pkGameDirector->replaceScene(pkTrans);
			}
			break;
		case Scene_RotoZoom:
			{
				CCTransitionRotoZoom* pkTrans = 
					CCTransitionRotoZoom::transitionWithDuration(fTime,pkScene);

				m_pkGameDirector->replaceScene(pkTrans);
			}
			break;
		default:
			break;
		}
	}

	return true;
}

bool CGameManager::StopScene( CCScene* pkScene )
{
	if (0 == pkScene)
	{
		return false;
	}

	m_pkGameDirector->popScene();

	return true;
}

void CGameManager::ExitGame()
{
	CCDirector::sharedDirector()->end();
}

CCPoint CGameManager::GetTilePositionFromLocation( CCPoint kLocation,
												  CCTMXTiledMap* pkTiledMap )
{
	CCAssert(pkTiledMap,"Null map");

	CCPoint kTildPosDiv;
	CCPoint kPosition;
	CCSize kSize;
	CCSize kTiledSize;

	float fHalfMapWidth = 0.0f;
	float fMapHeight = 0.0f;
	float fTileWidth = 0.0f;
	float fTileHeight = 0.0f;
	float fMapHeightDiff = 0.0f;
	float fPositionX = 0.0f;
	float fPositionY = 0.0f;

	kPosition = ccpSub(kLocation,pkTiledMap->getPosition());
	kSize = pkTiledMap->getMapSize();
	kTiledSize = pkTiledMap->getTileSize();

	fHalfMapWidth = kSize.width * 0.5f;
	fMapHeight = kSize.height;
	fTileWidth = kTiledSize.width;
	fTileHeight = kTiledSize.height;

	kTildPosDiv = CCPointMake(kPosition.x / fTileWidth,kPosition.y / fTileHeight);

	fMapHeightDiff = fMapHeight - kTildPosDiv.y;

	fPositionX = fMapHeightDiff + kTildPosDiv.x - fHalfMapWidth;
	fPositionY = fMapHeightDiff - kTildPosDiv.x + fHalfMapWidth;

	return CCPointMake(fPositionX,fPositionY);
}

CCPoint CGameManager::GetLocationFromTilePosition( CCPoint kMapPosition,
												  CCTMXTiledMap* pkTiledMap )
{
	float fHalfMapWidth = 0.0f;
	float fMapHeight = 0.0f;
	float fTileWidth = 0.0f;
	float fTileHeight = 0.0f;
	float fMapHeightDiff = 0.0f;
	float fPositionX = 0.0f;
	float fPositionY = 0.0f;
	float fAdd = 0.0f;
	float fSub = 0.0f;

	CCPoint kTildPosDiv;
	CCPoint kPosition;
	CCSize kSize;
	CCSize kTiledSize;

	kSize = pkTiledMap->getMapSize();
	kTiledSize = pkTiledMap->getTileSize();

	fHalfMapWidth = kSize.width * 0.5f;
	fMapHeight = kSize.height;
	fTileWidth = kTiledSize.width;
	fTileHeight = kTiledSize.height;

	fAdd = kMapPosition.x + fHalfMapWidth;
	fSub = kMapPosition.y - fHalfMapWidth;

	fMapHeightDiff = (fSub + fAdd) * 0.5f;
	kTildPosDiv.y = fMapHeight - fMapHeightDiff;
	kTildPosDiv.x = fAdd - fMapHeightDiff;
	kPosition.x = kTildPosDiv.x * fTileWidth;
	kPosition.y = kTildPosDiv.y * fTileHeight;

	return ccpAdd(kPosition,pkTiledMap->getPosition());
}

CCPoint CGameManager::GetFixedLocationFromTilePosition( CCPoint kPosition,
													   CCTMXTiledMap* pkTiledMap )
{
	CCPoint kConvertPosition;
	CCPoint kTilePosition;

	kTilePosition = GetTilePositionFromLocation(kPosition,pkTiledMap);
	kConvertPosition = GetLocationFromTilePosition(kTilePosition,pkTiledMap);

	return kConvertPosition;
}

bool CGameManager::InsertResultToVector( ResultInfo kInfo )
{
	if (0 == m_pkResults)
	{
		return false;
	}

	m_pkResults->push_back(kInfo);

	return true;
}

bool CGameManager::GetLastResultFromVector( ResultInfo& kInfo )
{
	if (0 == m_pkResults || 0 == m_pkResults->size())
	{
		return false;
	}

	ResultVector::iterator it = m_pkResults->end() - 1;

	kInfo = *it;

	return true;
}

bool CGameManager::ProcessNumberString( string& strOutString,
									   unsigned int uiCount,
									   int nValue)
{
	strOutString = "";

	if (uiCount < 1)
	{
		return false;
	}

	if (nValue > (int)(pow(10,(double)uiCount)))
	{
		return false;
	}

	for (unsigned int i = uiCount;i > 1;i--)
	{
		int nMax = (int)(pow(10,(double)i));

		if ((nValue * 10) < nMax)
		{
			strOutString += "0";
		}
	}

	char szTemp[100] = {0};
	itoa(nValue,szTemp,10);
	strOutString += szTemp;

	return true;
}

END_KERNEL