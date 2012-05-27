/*
*
*/

#ifndef WELCOMSCENE_H
#define WELCOMSCENE_H

#include <GameManager.h>

using namespace GameKernel;

class CWelcomScene:public IGameScene
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

	virtual void ExitButtonCallback(CCObject* pSender);
	virtual void StartButtonCallback(CCObject* pSender);
	virtual void CreditsButtonCallback(CCObject* pSender);

	LAYER_NODE_FUNC(CWelcomScene);

protected:

	bool InitialiseUI();

	SYNTHESIZE_READONLY(CCScene*,m_pkRootScene,RootScene);

	CCMenuItemImage* m_pkStartBtn;
	CCMenuItemImage* m_pkExitBtn;
	CCMenuItemImage* m_pkCredits;

	CCMenu* m_pkStartMenu;

private:
};

#endif