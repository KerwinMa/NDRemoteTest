/*
*
*/

#ifndef GAMESCENE_H
#define GAMESCENE_H

class IGameScene
{
public:

	IGameScene(){}
	virtual ~IGameScene(){}

	virtual const char* GetName() const = 0;
	virtual bool Initialise() = 0;
	virtual bool Shutdown() = 0;
	virtual bool Install() = 0;
	virtual bool Uninstall() = 0;

protected:
private:
};

#endif