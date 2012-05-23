/*
*
*/

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "GameKernelDefine.h"

BEGIN_KERNEL

class KERNEL_DLL CResourceManager
{
public:

	CResourceManager();
	virtual ~CResourceManager();

	static bool Create(const char* pszDefResPath);
	static void Destroy();

protected:

	virtual bool Initialise(const char* pszDefResPath);

	STATIC_READONLY(CResourceManager*,ms_pkResourceManager,ResourceManager);
	INLINE_CONST_READONLY(char*,m_pszDefaultPath,DefaultPath);

private:
};

END_KERNEL

#endif