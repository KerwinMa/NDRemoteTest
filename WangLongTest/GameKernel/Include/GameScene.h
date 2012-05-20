/*
*
*/

#ifndef GAMESCENE_H
#define GAMESCENE_H

BEGIN_KERNEL

class IGameScene
{
public:

	IGameScene():m_bIsInit(false){}
	virtual ~IGameScene(){}

	virtual const char* GetName() const = 0;
	virtual bool Initialise() = 0;
	virtual bool Shutdown() = 0;
	virtual bool BeginScene() = 0;
	virtual bool EndScene() = 0;
	virtual CCScene* GetRootScene() const = 0;

protected:

	INLINE_READONLY(bool,m_bIsInit,Initialised);

private:
};

END_KERNEL

#endif