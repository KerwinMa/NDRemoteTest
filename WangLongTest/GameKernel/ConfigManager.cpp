#include "stdafx.h"
#include "ConfigManager.h"

BEGIN_KERNEL

CConfigManager* CConfigManager::ms_pkConfigManager = 0;

CConfigManager::CConfigManager():
m_pszConfigPath(0)
{
	m_pszConfigPath = new char[MAX_PATH];
	memset(m_pszConfigPath,0,sizeof(char) * MAX_PATH);
}

CConfigManager::~CConfigManager()
{
	SafeDeleteArray(m_pszConfigPath);
}

bool CConfigManager::Create( const char* pszConfigPath )
{
	CConfigManager* pkCM = 0;
	bool bSucceeded = false;

	if (0 != CConfigManager::ms_pkConfigManager)
	{
		return bSucceeded;
	}

	pkCM = new CConfigManager;
	bSucceeded = pkCM->Initialise(pszConfigPath);

	if (bSucceeded && pkCM)
	{
		CConfigManager::ms_pkConfigManager = pkCM;
	}

	return bSucceeded;
}

void CConfigManager::Destroy()
{
	SafeDelete(CConfigManager::ms_pkConfigManager);
}

bool CConfigManager::Initialise( const char* pszConfigPath )
{
	if (0 == pszConfigPath || !*pszConfigPath)
	{
		return false;
	}

	strcpy_s(m_pszConfigPath,MAX_PATH,pszConfigPath);

	return true;
}

END_KERNEL