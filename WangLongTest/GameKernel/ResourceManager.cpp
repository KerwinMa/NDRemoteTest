#include "stdafx.h"
#include "ResourceManager.h"

BEGIN_KERNEL

CResourceManager* CResourceManager::ms_pkResourceManager = 0;

CResourceManager::CResourceManager():
m_pszDefaultPath(0)
{
	m_pszDefaultPath = new char[MAX_PATH];
	memset(m_pszDefaultPath,0,sizeof(char) * MAX_PATH);
}

CResourceManager::~CResourceManager()
{
	SafeDeleteArray(m_pszDefaultPath);
}

bool CResourceManager::Create( const char* pszDefResPath )
{
	CResourceManager* pkRM = 0;
	bool bSucceeded = false;

	if (CResourceManager::ms_pkResourceManager)
	{
		return bSucceeded;
	}

	pkRM = new CResourceManager;
	bSucceeded = pkRM->Initialise(pszDefResPath);

	if (bSucceeded && pkRM)
	{
		CResourceManager::ms_pkResourceManager = pkRM;
	}

	return bSucceeded;
}

void CResourceManager::Destroy()
{
	SafeDelete(CResourceManager::ms_pkResourceManager);
}

bool CResourceManager::Initialise( const char* pszDefResPath )
{
	if (0 == pszDefResPath || !*pszDefResPath)
	{
		return false;
	}

	strcpy_s(m_pszDefaultPath,MAX_PATH,pszDefResPath);

	return true;
}

END_KERNEL