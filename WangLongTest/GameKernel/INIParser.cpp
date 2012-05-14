#include "stdafx.h"
#include "INIParser.h"
#include <fstream>

BEGIN_KERNEL

CINIParser::CINIParser(const char* pszFilename):
m_bIsInit(false),
m_pszFilename(0)
{
	CCAssert(pszFilename,"传进来的字符串地址为空");
	
	if (pszFilename && *pszFilename)
	{
		m_pszFilename = new char[MAX_PATH];

		memset(m_pszFilename,0,sizeof(char) * MAX_PATH);

		strcpy_s(m_pszFilename,MAX_PATH,pszFilename);

		if (Initialise())
		{
			m_bIsInit = true;
		}
	}
}

CINIParser::~CINIParser()
{
	SafeDeleteArray(m_pszFilename);
}

bool CINIParser::Initialise()
{
	if (0 == m_pszFilename || !*m_pszFilename)
	{
		return false;
	}

	fstream kReadStream(m_pszFilename);

	return true;
}

END_KERNEL