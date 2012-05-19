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
	
	CGameManager();
	virtual ~CGameManager();

	static bool Create(const char* pszGameModulePath);
	static void Destroy();

	virtual bool LoadGame(const char* pszGameName);
	virtual void UnloadGame();
	virtual bool InitialiseScene(IGameScene* pkGameScene);
	virtual bool UninitialiseScene(IGameScene* pkGameScene);

protected:

	virtual bool Initialise(const char* pszGameModulePath);
	void ClearScene(SceneVectorPtr pkScene);

	INLINE_CONST_READONLY(char*,m_pszGamePath,GameModulePath);
	INLINE_READONLY(IGameScene*,m_pkCurrentScene,CurrentScene);
	INLINE_READONLY(bool,m_bIsInit,Initialised);
	STATIC_READONLY(CGameManager*,ms_pkGameManager,GameManager);

	SceneVectorPtr m_pkScenes;

private:
};

#define g_pGame CGameManager::GetGameManager()

END_KERNEL

#endif