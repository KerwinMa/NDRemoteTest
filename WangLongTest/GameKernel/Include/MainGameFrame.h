/*
*
*/

#ifndef MAINGAMEFRAME_H
#define MAINGAMEFRAME_H

#include "GameKernelDefine.h"

BEGIN_KERNEL

class KERNEL_DLL CMainGameFrame:public CCApplication
{
public:
	
	CMainGameFrame(LPTSTR pszGameName);
	virtual ~CMainGameFrame();

	virtual bool initInstance();
	virtual bool applicationDidFinishLaunching();
	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();

protected:

	virtual bool InitialiseLogSystem(const char* pszLoggingFile);

	INLINE_CONST_READONLY(char*,m_pszGameName,GameName);
	INLINE_READONLY(bool,m_bBoostLog,BoostLog);

private:
};

END_KERNEL

#endif