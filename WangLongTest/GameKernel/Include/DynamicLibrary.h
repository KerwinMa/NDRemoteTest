/*
*
*/

#ifndef DYNAMICLIBRARY_H
#define DYNAMICLIBRARY_H

#include "GameKernelDefine.h"

BEGIN_KERNEL

class KERNEL_DLL CDynamicLibrary
{
public:

	CDynamicLibrary(const char* pszName);
	virtual ~CDynamicLibrary();

	virtual bool Load();
	virtual bool Unload();

	void* GetSysbol(const char* pszSysbolName);

protected:

	INLINE_CONST_READONLY(char*,m_pszName,Name);

	void* m_hDynamicLib;

private:
};

END_KERNEL

#endif