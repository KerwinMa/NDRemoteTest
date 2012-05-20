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

	SYNTHESIZE_READONLY(CCScene*,m_pkRootScene,RootScene);

private:
};

#endif