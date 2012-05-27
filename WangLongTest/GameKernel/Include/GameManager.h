/*
*
*/

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "GameKernelDefine.h"
#include "GameScene.h"

BEGIN_KERNEL

class KERNEL_DLL CGameManager
{
public:

	typedef vector<IGameScene*> SceneVector,*SceneVectorPtr;
	typedef vector<ResultInfo> ResultVector,*ResultVectorPtr;
	
	CGameManager();
	virtual ~CGameManager();

	static bool Create(const char* pszGameModulePath);
	static void Destroy();

	static CCPoint GetTilePositionFromLocation(CCPoint kLocation,
		CCTMXTiledMap* pkTiledMap);
	static CCPoint GetLocationFromTilePosition(CCPoint kMapPosition,
		CCTMXTiledMap* pkTiledMap);
	static CCPoint GetFixedLocationFromTilePosition(CCPoint kPosition,
		CCTMXTiledMap* pkTiledMap);
	static bool ProcessNumberString(string& strOutString,unsigned int uiCount,int nValue);

	virtual bool LoadGame(const char* pszGameName);
	virtual bool UnloadGame(const char* pszGameName);
	virtual bool InitialiseScene(IGameScene* pkGameScene);
	virtual bool UninitialiseScene(IGameScene* pkGameScene);
	virtual bool RunOrRepeaceScene(CCScene* pkScene,
		SceneChangeType eType,float fTime);
	virtual bool StopScene(CCScene* pkScene);
	virtual void ExitGame();
	virtual bool InsertResultToVector(ResultInfo kInfo);
	virtual bool GetLastResultFromVector(ResultInfo& kInfo);

protected:

	bool Initialise(const char* pszGameModulePath);
	bool InitialiseDirector();
	bool InitialiseFileEngine();
	void ClearScene(SceneVectorPtr pkScene);

	INLINE_CONST_READONLY(char*,m_pszGamePath,GameModulePath);
	INLINE_READONLY(IGameScene*,m_pkCurrentScene,CurrentScene);
	INLINE_READONLY(bool,m_bIsInit,Initialised);
	INLINE_READONLY(CCDirector*,m_pkGameDirector,GameDirector);
	INLINE_READONLY(CCSize,m_kWindowSize,WindowSize);
	STATIC_READONLY(CGameManager*,ms_pkGameManager,GameManager);

	SceneVectorPtr m_pkScenes;
	ResultVectorPtr m_pkResults;

private:
};

#define g_pGame CGameManager::GetGameManager()

END_KERNEL

#endif