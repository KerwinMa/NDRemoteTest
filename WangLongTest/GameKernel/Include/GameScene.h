/*
*
*/

#ifndef GAMESCENE_H
#define GAMESCENE_H

BEGIN_KERNEL

class IGameScene
{
public:

	IGameScene(){}
	virtual ~IGameScene(){}

	virtual const char* GetName() const = 0;
	virtual bool Initialise() = 0;
	virtual bool Shutdown() = 0;
	virtual bool BeginScene() = 0;
	virtual bool EndScene() = 0;
	virtual CCScene* GetRootScene() const = 0;

protected:
private:
};

END_KERNEL

#endif