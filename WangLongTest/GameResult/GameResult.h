/*
*
*/

#ifndef GAMERESULT_H
#define GAMERESULT_H

#include <GameManager.h>

using namespace GameKernel;

class CGameResult:public IGameScene
{
public:
	CGameResult();
	virtual ~CGameResult();

	virtual const char* GetName() const;
	virtual bool Initialise();
	virtual bool Shutdown();
	virtual bool BeginScene();
	virtual bool EndScene();
	virtual CCScene* GetRootScene() const;

	LAYER_NODE_FUNC(CGameResult);

protected:

	CCScene* m_pkRootScene;
	char* m_pszName;

private:
};

#endif