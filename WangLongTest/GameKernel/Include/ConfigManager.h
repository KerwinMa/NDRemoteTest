/*
*
*/

#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "GameKernelDefine.h"

BEGIN_KERNEL

class KERNEL_DLL CConfigManager
{
public:

	CConfigManager();
	virtual ~CConfigManager();

	static bool Create(const char* pszConfigPath);
	static void Destroy();

protected:

	virtual bool Initialise(const char* pszConfigPath);

	STATIC_READONLY(CConfigManager*,ms_pkConfigManager,ConfigManager);
	INLINE_CONST_READONLY(char*,m_pszConfigPath,ConfigPath);

private:
};

#define g_pConfig CConfigManager::GetConfigManager()

END_KERNEL

#endif