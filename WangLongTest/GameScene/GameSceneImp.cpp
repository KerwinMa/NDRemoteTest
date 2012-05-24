#include "stdafx.h"
#include "GameSceneImp.h"

static const char* g_pszName = "GameScene";

CGameSceneImp::CGameSceneImp():
m_pkRootScene(0),
m_pkTiledMap(0),
m_pkBackgroundLayer(0),
m_pkMineMap(0),
m_pkBatchMine(0),
m_pkBatchNoMine(0),
m_pkBatchFlag(0),
m_pkMenuFlag(0),
m_pkMenu(0),
m_bIsFlaged(false),
m_pkFollowMouseFlag(0),
m_pkBackgroundUI(0)
{
	setIsTouchEnabled(true);

	m_kScrollPoint.x = -750.0f;
	m_kScrollPoint.y = -600.0f;

	m_kMineOffset = ccp(7,20);
	m_kMineSize = CCSize(11,15);

	m_pkMineMap = new CMineSweepingMap((unsigned int)m_kMineSize.width,
		(unsigned int)m_kMineSize.height,20);
}

CGameSceneImp::~CGameSceneImp()
{
	SafeDelete(m_pkMineMap);
}

const char* CGameSceneImp::GetName() const
{
	return g_pszName;
}

bool CGameSceneImp::Initialise()
{
	m_pkRootScene = CCScene::node();
	m_pkRootScene->addChild(this);

	if (0 == m_pkRootScene)
	{
		return false;
	}

	if (!InitialiseMap())
	{
		return false;
	}

	if (!InitialiseSprite())
	{
		return false;
	}

	if (!InitialiseUI())
	{
		return false;
	}

	m_bIsInit = true;

	return true;
}

bool CGameSceneImp::Shutdown()
{
	return true;
}

bool CGameSceneImp::BeginScene()
{
	if (!g_pGame->RunOrRepeaceScene(m_pkRootScene))
	{
		return false;
	}

	return true;
}

bool CGameSceneImp::EndScene()
{
	return true;
}

bool CGameSceneImp::InitialiseUI()
{
	if (m_bIsInit)
	{
		return false;
	}

	CCSprite* pkFlagSprite_Common = CCSprite::spriteWithFile("RedFlag.png");
	CCSprite* pkFlagSprite_Selected = CCSprite::spriteWithFile("RedFlag_Selected.png");
	m_pkBackgroundUI = CCSprite::spriteWithFile("jiemian.png");

	if (0 == pkFlagSprite_Common || 0 == pkFlagSprite_Selected)
	{
		return false;
	}

	m_pkMenuFlag = CCMenuItemSprite::itemFromNormalSprite(
		pkFlagSprite_Common,pkFlagSprite_Selected,this,
		menu_selector(CGameSceneImp::FlagButtonCallback));

	m_pkBackgroundUI->setPosition(ccp(400,75));
	m_pkMenuFlag->setPosition(80,50);
	m_pkMenuFlag->setScale(3.0f);

	m_pkMenu = CCMenu::menuWithItem(m_pkMenuFlag);
	m_pkMenu->setPosition(ccp(0,0));

	addChild(m_pkBackgroundUI,1);
	addChild(m_pkMenu,2);

	return true;
}

bool CGameSceneImp::InitialiseMap()
{
	m_pkTiledMap = CCTMXTiledMap::tiledMapWithTMXFile("gamemap.tmx");

	if (0 == m_pkTiledMap)
	{
		return false;
	}

	m_pkBackgroundLayer = m_pkTiledMap->layerNamed("Background");

	if (0 == m_pkBackgroundLayer)
	{
		return false;
	}

	addChild(m_pkTiledMap,-1);

	m_pkTiledMap->setPosition(m_kScrollPoint);

	return true;
}

void CGameSceneImp::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
	CCPoint kLocation;
	CCPoint kTilePosition;
	CCPoint kConvertedLocation;
	CCSetIterator it = pTouches->begin();
	CCTouch* pkTouch = (CCTouch*)(*it);

	kLocation = pkTouch->locationInView(pkTouch->view());
	kConvertedLocation = CCDirector::sharedDirector()->convertToGL(kLocation);
	kTilePosition = g_pGame->GetTilePositionFromLocation(
		kConvertedLocation,m_pkTiledMap);

	kTilePosition.x = static_cast<float>((int)(kTilePosition.x + 0.5f));
	kTilePosition.y = static_cast<float>((int)(kTilePosition.y + 0.5f));

	MineNodePtr pkNode = m_pkMineMap->GetMineNode(
		(int)(kTilePosition.x - m_kMineOffset.x),
		(int)(kTilePosition.y - m_kMineOffset.y));

	if (!ParseNode(pkNode))
	{
		return;
	}
}

bool CGameSceneImp::InitialiseSprite()
{
	if (m_bIsInit)
	{
		return false;
	}

	m_pkBatchNoMine = CCSpriteBatchNode::batchNodeWithFile("passed.png");
	m_pkBatchFlag = CCSpriteBatchNode::batchNodeWithFile("RedFlag.png");

	m_pkFollowMouseFlag = CCSprite::spriteWithFile("RedFlag.png");

	addChild(m_pkFollowMouseFlag,4);
	addChild(m_pkBatchFlag,3);
	addChild(m_pkBatchNoMine,2);

	return true;
}

bool CGameSceneImp::ParseNode( MineNodePtr pkNode)
{
	if (0 == pkNode)
	{
		return false;
	}

	CCPoint kPosition = ccpAdd(m_kMineOffset,ccp(pkNode->uiX,pkNode->uiY));

	if (0 != pkNode->pkSprite)
	{
		return false;
	}

	switch (pkNode->eState)
	{
	case St_Common:
		{
			MineNodePtr pkTempNode = 0;
			bool bCheckContinue = true;

			if (0 < pkNode->uiCount)
			{
				RenderNumber(pkNode->uiCount,kPosition);
				bCheckContinue = false;
			}

			CCPoint kWorld = g_pGame->GetLocationFromTilePosition(kPosition,m_pkTiledMap);

			pkNode->pkSprite = CCSprite::spriteWithFile("passed.png");
			pkNode->pkParent = m_pkBatchNoMine;
			pkNode->pkParent->addChild(pkNode->pkSprite);
			pkNode->pkSprite->setPosition(kWorld);

			if (!bCheckContinue)
			{
				return true;
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

				pkTempNode = m_pkMineMap->GetMineNode(x,y);

				if (0 == pkTempNode)
				{
					continue;
				}

				ParseNode(pkTempNode);
			}
		}
		break;
	case St_Mine:
		{
			MessageBox(0,L"²Èµ½À×ÁË£¡",L"ERROR",MB_ICONHAND);
		}
		break;
	default:
		break;
	}

	return true;
}

bool CGameSceneImp::RenderNumber( unsigned int uiNumber,CCPoint kTilePos )
{
	if (1 > uiNumber || m_pkMineMap->GetMineCount() < uiNumber || 8 < uiNumber)
	{
		return false;
	}

	char szTemp[200] = {0};

	itoa((int)uiNumber,szTemp,10);

	CCLabelTTF* pkNumber = CCLabelTTF::labelWithString(szTemp, "Consolas", 25);
	CCPoint kLocation = g_pGame->GetLocationFromTilePosition(kTilePos,m_pkTiledMap);
	CCPoint kStringPosition = ccpAdd(ccp(0,7),kLocation);

	pkNumber->setPosition(kStringPosition);
	
	switch (uiNumber)
	{
	case 1:
		{
			pkNumber->setColor(ccc3(255,255,255));
		}
		break;
	case 2:
		{
			pkNumber->setColor(ccc3(0,255,0));
		}
		break;
	case 3:
		{
			pkNumber->setColor(ccc3(100,0,255));
		}
		break;
	default:
		pkNumber->setColor(ccc3(255,0,0));
		break;
	}

	addChild(pkNumber,4);

	return true;
}

void CGameSceneImp::FlagButtonCallback( CCObject* pSender )
{
	if (!m_bIsFlaged)
	{
		m_bIsFlaged = true;
	}
}

void CGameSceneImp::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent )
{
	if (m_bIsFlaged)
	{
		CCPoint kLocation;
		CCPoint kConvertedLocation;
		CCSetIterator it = pTouches->begin();
		CCTouch* pkTouch = (CCTouch*)(*it);

		kLocation = pkTouch->locationInView(pkTouch->view());
		kConvertedLocation = CCDirector::sharedDirector()->convertToGL(kLocation);

		if (m_pkFollowMouseFlag)
		{
			m_pkFollowMouseFlag->setPosition(kConvertedLocation);
		}
	}
}

void CGameSceneImp::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
{
	CCSetIterator it = pTouches->begin();
	CCTouch* pkTouch = (CCTouch*)(*it);
}