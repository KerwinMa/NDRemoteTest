/*
*
*/

#ifndef WELCOMSCENE_H
#define WELCOMSCENE_H

#include <GameManager.h>

using namespace GameKernel;

class CWelcomScene:
	public IGameScene,
	public CCLayer
{
public:

	CWelcomScene();
	virtual ~CWelcomScene();

	virtual const char* GetName() const;
	virtual bool init();
	virtual bool Initialise();
	virtual bool Shutdown();
	virtual bool BeginScene();
	virtual bool EndScene();

protected:

	SYNTHESIZE_READONLY(CCScene*,m_pkRootScene,RootScene);

private:
};

#endif