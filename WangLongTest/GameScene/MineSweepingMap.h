/*
*
*/

#ifndef MINESWEEPINGMAP_H
#define MINESWEEPINGMAP_H

#include <GameManager.h>
#include "GameSceneDefine.h"

using namespace GameKernel;

class CMineSweepingMap
{
public:

	typedef vector<MineNodePtr> MineList,*MineListPtr;

	CMineSweepingMap(unsigned int uiWidth,unsigned int uiHeight,
		unsigned int uiMineCount);
	virtual ~CMineSweepingMap();
	
	bool PassedAddAndCheckWin();
	bool IsRange(int x,int y);
	MineNodePtr GetMineNode(int x,int y);
	MineNodePtr GetMineNode(CCPoint kPosition);

protected:

	virtual bool InitliaseMap();
	virtual bool InitialiseMine();
	virtual bool InitialiseNumber();

	void ClearDoubleMineVecotr(DoubleMineNodeVector& kDbVector);
	bool CheckAroundMine(MineNode* pkNode);

	INLINE_WRITEANDREAD(unsigned int,m_uiPassedNode,PassedNode);
	INLINE_READONLY(unsigned int,m_uiTotalNodeCount,TotalNodeCount);
	INLINE_READONLY(unsigned int,m_uiMapWidth,MapWidth);
	INLINE_READONLY(unsigned int,m_uiMapHeight,MapHeight);
	INLINE_READONLY(unsigned int,m_uiMineCount,MineCount);
	INLINE_READONLY(CCSize,m_kMapSize,MapSize);
	INLINE_READONLY(bool,m_bIsInit,Initialised);

	MineList m_kMineList;
	DoubleMineNodeVector m_kNodeVector;

private:
};

#endif