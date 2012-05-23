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

protected:

	bool InitialiseUI();
	bool InitialiseMap();
	bool InitialiseSprite();

	SYNTHESIZE_READONLY(CCScene*,m_pkRootScene,RootScene);
	INLINE_READONLY(CCTMXTiledMap*,m_pkTiledMap,TiledMap);
	INLINE_READONLY(CCTMXLayer*,m_pkBackgroundLayer,BackgroundLayer);
	INLINE_READONLY(CMineSweepingMap*,m_pkMineMap,MineSweepingMap);
	INLINE_READONLY(CCPoint,m_kScrollPoint,ScrollPoint);

	CCSpriteBatchNode* m_pkBatchNoMine;
	CCSpriteBatchNode* m_pkBatchFlag;
	CCSpriteBatchNode* m_pkBatchMine;

	CCPoint m_kMineOffset;

private:
};

#endif