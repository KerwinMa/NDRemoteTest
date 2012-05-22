#include "stdafx.h"
#include "GameSceneImp.h"

static const char* g_pszName = "GameScene";

CGameSceneImp::CGameSceneImp():
m_pkRootScene(0),
m_pkTiledMap(0),
m_pkBackgroundLayer(0),
m_pkMineMap(0)
{
	setIsTouchEnabled(true);

	m_kScrollPoint.x = -750.0f;
	m_kScrollPoint.y = -600.0f;

	m_pkMineMap = new CMineSweepingMap(10,10,2);
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

	if (!InitialiseUI())
	{
		return false;
	}

	if (!InitialiseMap())
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

// 	CCPoint kPPP = m_pkBackgroundLayer->positionAt(ccp(7,20));
// 	CCSprite* pkTemp = CCSprite::spriteWithFile("passed.PNG");
// 	m_pkTiledMap->addChild(pkTemp);
// 	pkTemp->setPosition(kPPP);

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

	CCRect kRect(0.0f,0.0f,64.0f,64.0f);
	CCSprite* pkSprite = CCSprite::spriteWithFile("passed.png",kRect);

	if (pkSprite)
	{
		addChild(pkSprite,2);
		CCPoint kWorld = g_pGame->GetLocationFromTilePosition(kTilePosition,m_pkTiledMap);

		pkSprite->setPosition(kWorld);
	}
}