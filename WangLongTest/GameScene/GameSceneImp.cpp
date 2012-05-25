#include "stdafx.h"
#include "GameSceneImp.h"

static const char* g_pszName = "GameScene";

CGameSceneImp::CGameSceneImp():
m_pkRootScene(0),
m_pkTiledMap(0),
m_bStartTime(false),
m_pkBackgroundLayer(0),
m_pkMineMap(0),
m_pkBatchMine(0),
m_pkBatchNoMine(0),
m_pkBatchFlag(0),
m_pkRestartBtn(0),
m_pkMenu(0),
m_bIsFlaged(false),
m_pkFollowMouseFlag(0),
m_pkBackgroundUI(0),
m_bIsWin(false),
m_pkTimeLabel(0),
m_fTimeCost(0.0f)
{
	m_kScrollPoint.x = -750.0f;
	m_kScrollPoint.y = -600.0f;

	m_kMineOffset = ccp(7,20);
	m_kMineSize = CCSize(12,14);

	m_pkMineMap = new CMineSweepingMap((unsigned int)m_kMineSize.width,
		(unsigned int)m_kMineSize.height,10);
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

	schedule(schedule_selector(CGameSceneImp::Update));

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
	setIsTouchEnabled(false);
	SafeDelete(m_pkMineMap);

	removeAllChildrenWithCleanup(true);

	g_pGame->StopScene(m_pkRootScene);

	return true;
}

bool CGameSceneImp::BeginScene()
{
	setIsTouchEnabled(true);

	srand((unsigned int)time(0));

	SceneChangeType eType = (SceneChangeType)((rand() %
		(int)(Scene_TransCount - 1)) + 1);

	if (!g_pGame->RunOrRepeaceScene(m_pkRootScene,eType,2.0f))
	{
		return false;
	}

	return true;
}

bool CGameSceneImp::EndScene()
{
	removeAllChildrenWithCleanup(true);

	return true;
}

bool CGameSceneImp::InitialiseUI()
{
	if (m_bIsInit)
	{
		return false;
	}

	m_pkBackgroundUI = CCSprite::spriteWithFile("jiemian.png");
	m_pkBackgroundUI->setPosition(ccp(400,75));

	m_pkTimeLabel = CCLabelTTF::labelWithString("0", "Arial", 64);

	if (0 == m_pkTimeLabel)
	{
		return false;
	}

	m_pkFollowMouseFlag->setScale(3.0f);
	m_pkFollowMouseFlag->setPosition(ccp(75,50));

	m_pkRestartBtn = CCMenuItemImage::itemFromNormalImage(
		"button\\restart_common.png","button\\restart_pressed.png",
		this,menu_selector(CGameSceneImp::RestartButtonCallback));

	if (0 == m_pkRestartBtn)
	{
		return false;
	}

	m_pkMenu = CCMenu::menuWithItem(m_pkRestartBtn);

	addChild(m_pkTimeLabel,2);
	addChild(m_pkMenu,2);
	addChild(m_pkBackgroundUI,1);

	m_pkTimeLabel->setPosition(ccp(700,80));
	m_pkRestartBtn->setPosition(400,75);
	m_pkRestartBtn->setScale(0.2f);

	m_pkMenu->setPosition(ccp(0,0));

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
	MineNodePtr pkNode = 0;

	kLocation = pkTouch->locationInView(pkTouch->view());
	kConvertedLocation = CCDirector::sharedDirector()->convertToGL(kLocation);
	kTilePosition = g_pGame->GetTilePositionFromLocation(
		kConvertedLocation,m_pkTiledMap);

	pkNode = GetMineNodeFromTilePosition(kTilePosition);

	if (0 == pkNode)
	{
		return;
	}

	if (ParseNode(pkNode) && !m_bStartTime)
	{
		m_bStartTime = true;
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
	CCRect kFlagRect(0,0,64,64);

	m_pkFollowMouseFlag = new CDragSprite(3.0f);
	m_pkFollowMouseFlag->initWithFile("RedFlag.png");

	m_pkBatchFlag->addChild(m_pkFollowMouseFlag);

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

			if (m_pkMineMap->PassedAddAndCheckWin())
			{
				m_bIsWin = true;
			}

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
			MessageBox(0,L"踩到雷了！",L"ERROR",MB_ICONHAND);
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

void CGameSceneImp::RestartButtonCallback( CCObject* pSender )
{
	g_pGame->LoadGame(g_pszName);
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

void CGameSceneImp::Update( ccTime fTime )
{
	if (m_bIsWin)
	{
		MessageBox(0,TEXT("你赢了！人类已经无法阻止你了！"),TEXT("WINNER~~~"),MB_OK);
		m_bIsWin = false;
	}

	if (m_bStartTime)
	{
		m_fTimeCost += fTime;
		char szTempTime[200] = {0};

		itoa((int)m_fTimeCost,szTempTime,10);

		if (*szTempTime)
		{
			m_pkTimeLabel->setString(szTempTime);
		}
	}

	if (m_pkFollowMouseFlag->GetReleased())
	{
		m_pkFollowMouseFlag->SetReleased(false);

		CCPoint kPoint;
		CCPoint kTilePosition;
		CCPoint kConvertPosition;
		MineNodePtr pkNode = 0;

		kPoint = m_pkFollowMouseFlag->GetLastReleasePosition();

		if (0 == kPoint.x && 0 == kPoint.y)
		{
			return;
		}

		kTilePosition = g_pGame->GetTilePositionFromLocation(kPoint,
			m_pkTiledMap);

		pkNode = GetMineNodeFromTilePosition(kTilePosition);

		if (0 == pkNode)
		{
			return;
		}
		else if(0 == pkNode->pkSprite)
		{
			CCRect kRect = CCRectMake(0,0,64,64);
			kConvertPosition = g_pGame->
				GetFixedLocationFromTilePosition(kPoint,m_pkTiledMap);

			pkNode->pkParent = m_pkBatchFlag;
			pkNode->pkSprite = CCSprite::spriteWithTexture(
				pkNode->pkParent->getTexture(),kRect);
			pkNode->pkSprite->setPosition(kConvertPosition);

			pkNode->pkParent->addChild(pkNode->pkSprite);
		}
	}
}

MineNodePtr CGameSceneImp::GetMineNodeFromTilePosition( CCPoint kTilePosition )
{
	MineNodePtr pkMineNode = 0;
	CCPoint kFixedPosition;

	kFixedPosition.x = static_cast<float>((int)(kTilePosition.x + 0.5f));
	kFixedPosition.y = static_cast<float>((int)(kTilePosition.y + 0.5f));

	pkMineNode = m_pkMineMap->GetMineNode(
		(int)(kFixedPosition.x - m_kMineOffset.x),
		(int)(kFixedPosition.y - m_kMineOffset.y));

	return pkMineNode;
}