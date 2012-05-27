#include "stdafx.h"
#include "DynamicLibrary.h"
#include <memory.h>
#include <string.h>
#include <windows.h>

BEGIN_KERNEL

CDynamicLibrary::CDynamicLibrary(const char* pszName):
m_pszName(0),
m_hDynamicLib(0)
{
	m_pszName = new char[MAX_PATH];
	memset(m_pszName,0,sizeof(char) * MAX_PATH);

	strcpy_s(m_pszName,MAX_PATH,pszName);
}

CDynamicLibrary::~CDynamicLibrary()
{
	SafeDeleteArray(m_pszName);	
}

bool CDynamicLibrary::Load()
{
	if (!*m_pszName)
	{
		return false;
	}

	m_hDynamicLib = LoadLibraryExA(m_pszName,
		0,LOAD_WITH_ALTERED_SEARCH_PATH);

	if (0 == m_hDynamicLib)
	{
		return false;
	}

	return true;
}

bool CDynamicLibrary::Unload()
{
	if (0 == m_hDynamicLib)
	{
		return false;
	}

	if (FreeLibrary((HMODULE)m_hDynamicLib))
	{
		return false;
	}

	return true;
}

void* CDynamicLibrary::GetSysbol(const char* pszSysbolName)
{
	return (void*)GetProcAddress((HMODULE)m_hDynamicLib,pszSysbolName);
}

END_KERNEL