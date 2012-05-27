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

	LAYER_NODE_FUNC(CGameResult);

protected:

	bool InitialiseUI();
	bool InitialiseAnimation();

	virtual void RestartButtonCallback(CCObject* pkSender);

	SYNTHESIZE_READONLY(CCScene*,m_pkRootScene,RootScene);
	INLINE_READONLY(ResultInfo,m_kResultInfo,ResultInfo);

	CCSprite* m_pkLoseAnimation;
	CCSprite* m_pkBackground;
	CCMenu* m_pkMenu;
	CCMenuItemImage* m_pkRestartButton;
	char* m_pszName;

private:
};

#endif