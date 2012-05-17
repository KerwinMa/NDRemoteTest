/*
*
*/

#ifndef DYNAMICLIBRARYMANAGER_H
#define DYNAMICLIBRARYMANAGER_H

#include "DynamicLibrary.h"

BEGIN_KERNEL

class CDynamicLibraryManager
{
public:

	typedef hash_map<string,CDynamicLibrary*>
		DynamicLibraryMap,*DynamicLibraryMapPtr;

	CDynamicLibraryManager();
	virtual ~CDynamicLibraryManager();

	static bool Create(const char* pszDefPath);
	static void Destroy();

	virtual CDynamicLibrary* LoadDynamicLibrary(const char* pszName);
	virtual bool UnloadDynamicLibrary(const char* pszName);

protected:

	virtual bool Initialise(const char* pszDefPath);

	STATIC_READONLY(CDynamicLibraryManager*,ms_pkDynLib,DynamicLibraryManager);

	char* m_pszDefaultPath;
	DynamicLibraryMapPtr m_pkDynamicLibraryMap;

private:
};

#define g_pDynLib CDynamicLibraryManager::GetDynamicLibraryManager()

END_KERNEL

#endif