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

typedef struct __tagMineNode
{
	NodeState eState;
}MineNode,*MineNodePtr;

typedef vector<MineNode> MineNodeVector,*MineNodeVectorPtr;
typedef vector<MineNodeVector> DoubleMineNodeVector,*DoubleMineNodeVectorPtr;

#endif