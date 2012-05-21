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

	CMineSweepingMap(unsigned int uiWidth,unsigned int uiHeight,
		unsigned int uiMineCount);
	virtual ~CMineSweepingMap();

protected:

	virtual bool InitliaseMap();

	INLINE_READONLY(unsigned int,m_uiMapWidth,MapWidth);
	INLINE_READONLY(unsigned int,m_uiMapHeight,MapHeight);
	INLINE_READONLY(unsigned int,m_uiMineCount,MineCount);
	INLINE_READONLY(CCSize,m_kMapSize,MapSize);
	INLINE_READONLY(bool,m_bIsInit,Initialised);

	DoubleMineNodeVector m_kNodeVector;

private:
};

#endif