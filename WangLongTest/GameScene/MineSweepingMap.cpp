#include "stdafx.h"
#include "MineSweepingMap.h"

CMineSweepingMap::CMineSweepingMap(unsigned int uiWidth,
								   unsigned int uiHeight,
								   unsigned int uiMineCount):
m_uiMapWidth(uiWidth),
m_uiMapHeight(uiHeight)
{
	if ((uiWidth * uiHeight) > uiMineCount)
	{
		m_kMapSize = CCSize((float)uiWidth,(float)uiHeight);
	}
}

CMineSweepingMap::~CMineSweepingMap()
{
	m_uiMapWidth = 0;
	m_uiMapHeight = 0;
}

bool CMineSweepingMap::InitliaseMap()
{
	if (0 == m_uiMapWidth || 0 == m_uiMapHeight || 0 == m_uiMineCount)
	{
		return false;
	}

	return true;
}