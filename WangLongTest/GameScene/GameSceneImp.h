/*
*
*/

#ifndef GAMESCENEIMP_H
#define GAMESCENEIMP_H

#include <GameManager.h>

using namespace GameKernel;

class CGameSceneImp:public IGameScene
{
public:

	CGameSceneImp();
	virtual ~CGameSceneImp();

	virtual const char* GetName() const;
	virtual bool init();
	virtual bool Initialise();
	virtual bool Shutdown();
	virtual bool BeginScene();
	virtual bool EndScene();

protected:

	bool InitialiseUI();
	bool InitialiseMap();

	SYNTHESIZE_READONLY(CCScene*,m_pkRootScene,RootScene);
	INLINE_READONLY(CCTMXTiledMap*,m_pkTiledMap,TiledMap);
	INLINE_READONLY(CCLayer*,m_pkBackgroundLayer,BackgroundLayer);

private:
};

#endif