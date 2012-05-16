/*
*
*/

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "GameKernelDefine.h"

BEGIN_KERNEL

class KERNEL_DLL CGameManager
{
public:

	CGameManager();
	virtual ~CGameManager();

	static bool Create(const char* pszGameModulePath);
	static void Destroy();

protected:

	virtual bool Initialise(const char* pszGameModulePath);

	INLINE_CONST_READONLY(char*,m_pszGamePath,GameModulePath);
	INLINE_READONLY(bool,m_bIsInit,Initialised);
	STATIC_READONLY(CGameManager*,ms_pkGameManager,GameManager);

private:
};

END_KERNEL

#endif