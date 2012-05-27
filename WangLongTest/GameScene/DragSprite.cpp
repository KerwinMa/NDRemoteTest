#include "stdafx.h"
#include "DragSprite.h"

CDragSprite::CDragSprite(float fDefScale):
m_fInitScale(fDefScale),
m_bIsReleased(false)
{
	CC_ASSERT(fDefScale > 0.00001f);
	m_fInitScale = fDefScale;
}

CDragSprite::~CDragSprite()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
}

bool CDragSprite::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if (!IsTouchInSprite(pTouch))
	{
		return false;
	}

	m_kInitPosition = getPosition();

	return true;
}

void CDragSprite::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint kLocation;
	CCPoint kConvertedLocation;

	setScale(1.0f);

	kLocation = pTouch->locationInView(pTouch->view());
	kConvertedLocation = CCDirector::sharedDirector()->convertToGL(kLocation);

	setPosition(kConvertedLocation);
}

void CDragSprite::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	m_kLastRelease = getPosition();

	setScale(m_fInitScale);
	setPosition(m_kInitPosition);
	m_bIsReleased = true;
}

void CDragSprite::OnEnter()
{
	CCSprite::onEnter();
}

void CDragSprite::OnExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}

CCRect CDragSprite::GetTouchRect()
{
	const CCSize& kSize = getTextureRect().size;
	const CCPoint& kPosition = getAnchorPointInPixels();

	return CCRectMake(-kPosition.x,-kPosition.y,kSize.width,kSize.height);
}

bool CDragSprite::IsTouchInSprite(CCTouch* pkTouch)
{
	return CCRect::CCRectContainsPoint(GetTouchRect(),
		convertTouchToNodeSpaceAR(pkTouch));
}

bool CDragSprite::init( void )
{
	if (!CCSprite::init())
	{
		return false;
	}

	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);

	return true;
}