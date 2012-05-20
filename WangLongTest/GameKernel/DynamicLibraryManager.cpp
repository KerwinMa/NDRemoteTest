#include "stdafx.h"
#include "DynamicLibraryManager.h"
#include <memory.h>
#include <string.h>

BEGIN_KERNEL

CDynamicLibraryManager* CDynamicLibraryManager::ms_pkDynLib = 0;

CDynamicLibraryManager::CDynamicLibraryManager():
m_pszDefaultPath(0),
m_pkDynamicLibraryMap(0)
{
	m_pkDynamicLibraryMap = new DynamicLibraryMap;

	m_pszDefaultPath = new char[MAX_PATH];
	memset(m_pszDefaultPath,0,sizeof(char) * MAX_PATH);
}

CDynamicLibraryManager::~CDynamicLibraryManager()
{
	SafeDeleteArray(m_pszDefaultPath);
}

bool CDynamicLibraryManager::Create(const char* pszDefPath)
{
	bool bSucceeded = false;
	CDynamicLibraryManager* pkDLM = 0;

	if (CDynamicLibraryManager::ms_pkDynLib)
	{
		return bSucceeded;
	}

	pkDLM = new CDynamicLibraryManager;
	bSucceeded = pkDLM->Initialise(pszDefPath);

	if (bSucceeded && pkDLM)
	{
		CDynamicLibraryManager::ms_pkDynLib = pkDLM;
	}

	return bSucceeded;
}

void CDynamicLibraryManager::Destroy()
{
	SafeDelete(CDynamicLibraryManager::ms_pkDynLib);
}

bool CDynamicLibraryManager::Initialise(const char* pszDefPath)
{
	if (0 == pszDefPath || !*pszDefPath)
	{
		return false;
	}

	strcpy_s(m_pszDefaultPath,MAX_PATH,pszDefPath);

	return true;
}

CDynamicLibrary* CDynamicLibraryManager::LoadDynamicLibrary( const char* pszName )
{
	if (0 == pszName || !*pszName)
	{
		return 0;
	}

	CDynamicLibrary* pkLibrary = 0;
	string strKey = pszName;

	DynamicLibraryMap::iterator itIndex = m_pkDynamicLibraryMap->find(strKey);

	if (m_pkDynamicLibraryMap->end() == itIndex)
	{
		string strDefPath = m_pszDefaultPath;
		string strName = pszName;
		string strFull = strDefPath + "\\" + strName + ".dll";;

		pkLibrary = new CDynamicLibrary(strFull.c_str());

		if (!pkLibrary->Load())
		{
			return 0;
		}

		m_pkDynamicLibraryMap->insert(make_pair(strKey,pkLibrary));
	}

	return pkLibrary;
}

bool CDynamicLibraryManager::UnloadDynamicLibrary( const char* pszName )
{
	if (0 == pszName || !*pszName)
	{
		return false;
	}

	CDynamicLibrary* pkDynLib = 0;
	string strKey = pszName;

	DynamicLibraryMap::iterator itIndex = m_pkDynamicLibraryMap->find(strKey);

	if (m_pkDynamicLibraryMap->end() == itIndex)
	{
		return false;
	}

	pkDynLib = itIndex->second;

	if (!pkDynLib->Unload())
	{
		return false;
	}

	SafeDelete(pkDynLib);
	m_pkDynamicLibraryMap->erase(itIndex);

	return true;
}

CDynamicLibrary* CDynamicLibraryManager::GetLibrary( const char* pszName ) const
{
	if (0 == pszName || !*pszName)
	{
		return 0;
	}

	CDynamicLibrary* pkLib = 0;
	string strName = pszName;

	DynamicLibraryMap::iterator it = m_pkDynamicLibraryMap->find(strName);

	if (m_pkDynamicLibraryMap->end() == it)
	{
		return pkLib;
	}

	pkLib = it->second;

	return pkLib;
}

END_KERNEL