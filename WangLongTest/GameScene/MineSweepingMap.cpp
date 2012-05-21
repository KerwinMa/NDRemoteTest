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

		if (InitliaseMap())
		{
			if (InitialiseMine())
			{
				m_bIsInit = true;
			}
		}
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

	for (unsigned int y = 0;y < m_uiMapHeight;y++)
	{
		MineNodeVector kVector;

		for (unsigned int x = 0;x < m_uiMapWidth;x++)
		{
			MineNode kNode;
			memset(&kNode,0,sizeof(MineNode));

			kNode.eState = St_Common;

			kVector.push_back(kNode);
		}

		m_kNodeVector.push_back(kVector);
	}

	return true;
}

bool CMineSweepingMap::InitialiseMine()
{
	if (0 == m_kNodeVector.size())
	{
		return false;
	}

	srand((unsigned int)time(0));

	for (unsigned int uiIndex = 0;uiIndex < m_uiMineCount;uiIndex++)
	{
		unsigned int x = rand() % m_uiMapWidth;
		unsigned int y = rand() % m_uiMapHeight;

		MineNodePtr pkNode = &(m_kNodeVector[y][x]);

		if (0 == pkNode)
		{
			continue;
		}

		if (St_Mine == pkNode->eState)
		{
			uiIndex--;
			continue;
		}

		pkNode->eState = St_Mine;
		m_kMineList.push_back(pkNode);
	}

	return true;
}