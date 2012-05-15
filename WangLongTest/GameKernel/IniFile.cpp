#include "stdafx.h"
#include "IniFile.h"
#include <fstream>
#include <algorithm>

BEGIN_KERNEL

CIniFile::CIniFile():
m_bIsInit(false),
m_pszFilename(0)
{
	m_pszFilename = new char[MAX_PATH];

	memset(m_pszFilename,0,sizeof(char) * MAX_PATH);
	m_bIsInit = true;
}

CIniFile::~CIniFile()
{
	SafeDeleteArray(m_pszFilename);
}

bool CIniFile::LoadFile(const char* pszFilename)
{
	StringVector kDataVector;

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

		kDataVector.push_back(strData);
	}

	kReadStream.close();

	return true;
}

void CIniFile::Unload()
{
	SafeDeleteArray(m_pszFilename);
}

const char* CIniFile::GetString( const char* pszTitle,const char* pszSubTitle ) const
{
	return 0;
}

bool CIniFile::GetInt( const char* pszTitle,const char* pszSubTitle,int& nData ) const
{
	return true;
}

bool CIniFile::GetFloat( const char* pszTitle,const char* pszSubTitle,float& fData ) const
{
	return true;
}

int CIniFile::GetVersion() const
{
	return 0;
}

bool CIniFile::ParseData( StringVector kStringVector )
{
	if (0 == kStringVector.size())
	{
		return false;
	}

	for (unsigned int uiIndex = 0;uiIndex < kStringVector.size(); uiIndex++)
	{
		string strText = kStringVector[uiIndex];

		TrimSpace(strText);

		if (CheckComment(strText))
		{
			continue;
		}
	}

	return true;
}

bool CIniFile::CheckComment( string strText )
{
	if (0 == strText.size())
	{
		return false;
	}

	if (';' != strText[0])
	{
		return false;
	}

	return true;
}

void CIniFile::TrimSpace( string& strText )
{
	strText.erase(find_if(strText.rbegin(),
		strText.rend(),not1(ptr_fun(::isspace))).base(),
		strText.end());
}

END_KERNEL