/*
*
*/

#ifndef WELCOMSCENE_H
#define WELCOMSCENE_H

class CWelcomScene:public IGameScene
{
public:
	CWelcomScene();
	virtual ~CWelcomScene();

	virtual const char* GetName() const;
	virtual bool Initialise();
	virtual bool Shutdown();
	virtual bool Install();
	virtual bool Uninstall();

protected:
private:
};

#endif