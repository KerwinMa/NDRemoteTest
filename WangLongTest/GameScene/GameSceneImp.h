/*
*
*/

#ifndef GAMESCENEIMP_H
#define GAMESCENEIMP_H

#include "MineSweepingMap.h"

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
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

protected:

	bool InitialiseUI();
	bool InitialiseMap();
	bool InitialiseSprite();
	bool ParseNode(MineNodePtr pkNode);
	bool RenderNumber(unsigned int uiNumber,CCPoint kTilePos);

	virtual void FlagButtonCallback(CCObject* pSender);

	SYNTHESIZE_READONLY(CCScene*,m_pkRootScene,RootScene);
	INLINE_READONLY(CCTMXTiledMap*,m_pkTiledMap,TiledMap);
	INLINE_READONLY(CCTMXLayer*,m_pkBackgroundLayer,BackgroundLayer);
	INLINE_READONLY(CMineSweepingMap*,m_pkMineMap,MineSweepingMap);
	INLINE_READONLY(CCPoint,m_kScrollPoint,ScrollPoint);

	bool m_bIsFlaged;

	CCSpriteBatchNode* m_pkBatchNoMine;
	CCSpriteBatchNode* m_pkBatchFlag;
	CCSpriteBatchNode* m_pkBatchMine;

	CCMenuItemSprite* m_pkMenuFlag;
	CCSprite* m_pkBackgroundUI;
	CCSprite* m_pkFollowMouseFlag;

	CCMenu* m_pkMenu;

	CCPoint m_kMineOffset;
	CCSize m_kMineSize;

private:
};

#endif