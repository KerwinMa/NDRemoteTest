#include "stdafx.h"
#include "MineSweepingMap.h"

CMineSweepingMap::CMineSweepingMap(unsigned int uiWidth,
								   unsigned int uiHeight,
								   unsigned int uiMineCount):
m_uiMapWidth(uiWidth),
m_uiMapHeight(uiHeight),
m_uiMineCount(uiMineCount)
{
	if ((uiWidth * uiHeight) > uiMineCount)
	{
		m_kMapSize = CCSize((float)uiWidth,(float)uiHeight);

		if (InitliaseMap())
		{
			if (InitialiseMine())
			{
				if (InitialiseNumber())
				{
					m_bIsInit = true;
				}
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
			MineNodePtr pkNode = new MineNode;
			memset(pkNode,0,sizeof(MineNode));

			pkNode->eState = St_Common;
			pkNode->uiX = x;
			pkNode->uiY = y;

			kVector.push_back(pkNode);
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

		MineNodePtr pkNode = m_kNodeVector[y][x];

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

bool CMineSweepingMap::InitialiseNumber()
{
	if (0 == m_kMineList.size())
	{
		return false;
	}

	for (unsigned int i = 0;i < m_kMineList.size();i++)
	{
		MineNodePtr pkNode = 0;
		pkNode = m_kMineList[i];

		CheckAroundMine(pkNode);
	}

	return true;
}

bool CMineSweepingMap::CheckAroundMine( MineNode* pkNode )
{
	if (0 == pkNode)
	{
		return false;
	}

	for (unsigned int i = 0;i < 8;i++)
	{
		int x = 0;
		int y = 0;

		MineNodePtr pkTempNode = 0;

		switch ((MineDirection)i)
		{
		case Dir_Left:
			{
				x = (int)(pkNode->uiX - 1);
				y = (int)(pkNode->uiY);
			}
			break;
		case Dir_LeftDown:
			{
				x = (int)(pkNode->uiX - 1);
				y = (int)(pkNode->uiY - 1);
			}
			break;
		case Dir_Down:
			{
				x = (int)(pkNode->uiX);
				y = (int)(pkNode->uiY - 1);
			}
			break;
		case Dir_RightDown:
			{
				x = (int)(pkNode->uiX + 1);
				y = (int)(pkNode->uiY - 1);
			}
			break;
		case Dir_Right:
			{
				x = (int)(pkNode->uiX + 1);
				y = (int)(pkNode->uiY);
			}
			break;
		case Dir_RightUp:
			{
				x = (int)(pkNode->uiX + 1);
				y = (int)(pkNode->uiY + 1);
			}
			break;
		case Dir_Up:
			{
				x = (int)(pkNode->uiX);
				y = (int)(pkNode->uiY + 1);
			}
			break;
		case Dir_LeftUp:
			{
				x = (int)(pkNode->uiX - 1);
				y = (int)(pkNode->uiY + 1);
			}
			break;
		default:
			break;
		}

		if (IsRange(x,y))
		{
			pkTempNode = m_kNodeVector[y][x];

			if (0 == pkTempNode)
			{
				break;
			}

			if (St_Mine != pkTempNode->eState)
			{
				pkTempNode->uiCount++;
			}
		}
	}

	return true;
}

bool CMineSweepingMap::IsRange( int x,int y )
{
	if (x < 0 || y < 0 || x >= (int)m_uiMapWidth || y >= (int)m_uiMapHeight)
	{
		return false;
	}

	return true;
}

void CMineSweepingMap::ClearDoubleMineVecotr( DoubleMineNodeVector& kDbVector )
{
	for (int y = 0;y < (int)kDbVector.size();y++)
	{
		for (int x = 0;x < (int)kDbVector[y].size();x++)
		{
			MineNodePtr pkNode = kDbVector[y][x];

			SafeDelete(pkNode);
		}

		kDbVector[y].clear();
	}

	kDbVector.clear();
}