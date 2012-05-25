#include "stdafx.h"
#include "GameResult.h"

CGameResult::CGameResult():
m_pszName(0),
m_pkRootScene(0)
{
	m_pszName = new char[MAX_PATH];
	memset(m_pszName,0,sizeof(char) * MAX_PATH);

	strcpy_s(m_pszName,MAX_PATH,"GameResult");
}

CGameResult::~CGameResult()
{
	SafeDeleteArray(m_pszName);
}

const char* CGameResult::GetName() const
{
	return m_pszName;
}

bool CGameResult::Initialise()
{
	return true;
}

bool CGameResult::Shutdown()
{
	return true;
}

bool CGameResult::BeginScene()
{
	return true;
}

bool CGameResult::EndScene()
{
	return true;
}

CCScene* CGameResult::GetRootScene() const
{
	return m_pkRootScene;
}