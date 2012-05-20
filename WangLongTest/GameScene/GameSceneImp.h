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
	virtual bool Initialise();
	virtual bool Shutdown();
	virtual bool BeginScene();
	virtual bool EndScene();

	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

protected:

	bool InitialiseUI();
	bool InitialiseMap();

	SYNTHESIZE_READONLY(CCScene*,m_pkRootScene,RootScene);
	INLINE_READONLY(CCTMXTiledMap*,m_pkTiledMap,TiledMap);
	INLINE_READONLY(CCTMXLayer*,m_pkBackgroundLayer,BackgroundLayer);

private:
};

#endif