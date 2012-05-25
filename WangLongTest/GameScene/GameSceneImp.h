/*
*
*/

#ifndef GAMESCENEIMP_H
#define GAMESCENEIMP_H

#include "DragSprite.h"

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
	virtual void Update( ccTime fTime );

	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

	LAYER_NODE_FUNC(CGameSceneImp);

protected:

	bool InitialiseUI();
	bool InitialiseMap();
	bool InitialiseSprite();
	bool ParseNode(MineNodePtr pkNode);
	bool RenderNumber(unsigned int uiNumber,CCPoint kTilePos);
	MineNodePtr GetMineNodeFromTilePosition(CCPoint kTilePosition);

	virtual void RestartButtonCallback(CCObject* pSender);

	SYNTHESIZE_READONLY(CCScene*,m_pkRootScene,RootScene);
	INLINE_READONLY(CCTMXTiledMap*,m_pkTiledMap,TiledMap);
	INLINE_READONLY(CCTMXLayer*,m_pkBackgroundLayer,BackgroundLayer);
	INLINE_READONLY(CMineSweepingMap*,m_pkMineMap,MineSweepingMap);
	INLINE_READONLY(CCPoint,m_kScrollPoint,ScrollPoint);
	INLINE_READONLY(bool,m_bIsWin,Win);
	INLINE_READONLY(unsigned int,m_uiTimeCost,TimeCost);

	bool m_bIsFlaged;

	CCSpriteBatchNode* m_pkBatchNoMine;
	CCSpriteBatchNode* m_pkBatchFlag;
	CCSpriteBatchNode* m_pkBatchMine;

	CCLabelTTF* m_pkTimeLabel;

	CCMenuItemSprite* m_pkRestartBtn;
	CCSprite* m_pkBackgroundUI;
	CDragSprite* m_pkFollowMouseFlag;

	CCMenu* m_pkMenu;

	CCPoint m_kMineOffset;
	CCSize m_kMineSize;

private:
};

#endif