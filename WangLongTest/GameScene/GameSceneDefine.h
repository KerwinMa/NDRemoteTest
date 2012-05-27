/*
*
*/

#ifndef GAMESCENEDEFINE_H
#define GAMESCENEDEFINE_H

typedef enum
{
	St_Common = 0,
	St_Mine
}NodeState;

typedef enum
{
	Dir_Left = 0,
	Dir_LeftDown,
	Dir_Down,
	Dir_RightDown,
	Dir_Right,
	Dir_RightUp,
	Dir_Up,
	Dir_LeftUp
}MineDirection;

typedef struct __tagMineNode
{
	NodeState eState;

	CCSprite* pkSprite;
	CCSpriteBatchNode* pkParent;

	unsigned int uiX;
	unsigned int uiY;
	unsigned int uiCount;

}MineNode,*MineNodePtr;

typedef vector<MineNodePtr> MineNodeVector,*MineNodeVectorPtr;
typedef vector<MineNodeVector> DoubleMineNodeVector,*DoubleMineNodeVectorPtr;

#endif