/*
*
*/

#ifndef DRAGSPRITE_H
#define DRAGSPRITE_H

#include "MineSweepingMap.h"

class CDragSprite:
	public CCSprite,
	public CCTargetedTouchDelegate
{
public:

	CDragSprite(float fDefScale);
	virtual ~CDragSprite();

	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
	virtual void ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent );
	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );
	virtual void OnEnter();
	virtual void OnExit();

	bool IsTouchInSprite(CCTouch* pkTouch);
	CCRect GetTouchRect();

	virtual bool init( void );

protected:

	INLINE_READONLY(CCPoint,m_kInitPosition,InitPosition);
	INLINE_WRITEANDREAD(float,m_fInitScale,InitScale);

private:
};

#endif