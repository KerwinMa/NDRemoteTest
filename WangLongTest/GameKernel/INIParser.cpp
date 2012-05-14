#include "stdafx.h"
#include "INIParser.h"
#include <fstream>

BEGIN_KERNEL

CINIParser::CINIParser():
m_bIsInit(false),
m_pszFilename(0)
{
	m_pkDataVector = new StringVector;
	m_pszFilename = new char[MAX_PATH];

	memset(m_pszFilename,0,sizeof(char) * MAX_PATH);
	m_bIsInit = true;
}

CINIParser::~CINIParser()
{
	SafeDeleteArray(m_pszFilename);

	m_pkDataVector->clear();
	SafeDelete(m_pkDataVector);
}

bool CINIParser::LoadFile(const char* pszFilename)
{
	CCAssert(pszFilename,"传进来的字符串地址为空");

	if (0 == pszFilename || !*pszFilename)
	{
		return false;
	}

	strcpy_s(m_pszFilename,MAX_PATH,pszFilename);

	fstream kReadStream(m_pszFilename);

	while (!kReadStream.eof())
	{
		string strData = "";

		kReadStream >> strData;

		if (0 == strData.size())
		{
			continue;
		}

		m_pkDataVector->push_back(strData);
	}

	return true;
}

END_KERNEL