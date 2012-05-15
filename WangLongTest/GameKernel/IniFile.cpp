#include "stdafx.h"
#include "IniFile.h"
#include <fstream>
#include <algorithm>

BEGIN_KERNEL

CIniFile::CIniFile():
m_bIsInit(false),
m_pszFilename(0),
m_nVersion(0)
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

	if (!ParseData(kDataVector))
	{
		return false;
	}

	kReadStream.close();

	return true;
}

void CIniFile::Unload()
{
	SafeDeleteArray(m_pszFilename);
	m_nVersion = 0;
	m_kTitleMap.clear();
}

const char* CIniFile::GetString( const char* pszTitle,const char* pszSubTitle ) const
{
	if (0 == pszTitle || !*pszTitle || 0 == pszSubTitle || !*pszSubTitle)
	{
		return 0;
	}

	string strTitle = pszTitle;
	string strSubTitle = pszSubTitle;
	string strValue = "";

	SubTitleMap kSubMap;
	SubTitleMap::iterator itSubMap;

	if (m_kTitleMap.end() == m_kTitleMap.find(strTitle))
	{
		return 0;
	}

	kSubMap = m_kTitleMap.find(strTitle)->second;

	if (0 == kSubMap.size())
	{
		return false;
	}

	itSubMap = kSubMap.find(strSubTitle);

	if (kSubMap.end() == itSubMap)
	{
		return 0;
	}

	strValue = itSubMap->second;

	return strValue.c_str();
}

bool CIniFile::GetInt( const char* pszTitle,const char* pszSubTitle,int& nData ) const
{
	if (0 == pszTitle || !*pszTitle || 0 == pszSubTitle || !*pszSubTitle)
	{
		return false;
	}

	return true;
}

bool CIniFile::GetFloat( const char* pszTitle,const char* pszSubTitle,float& fData ) const
{
	return true;
}

bool CIniFile::ParseData( StringVector kStringVector )
{
	if (0 == kStringVector.size())
	{
		return false;
	}

	SubTitleMap kSubMap;

	for (unsigned int uiIndex = 0;uiIndex < kStringVector.size(); uiIndex++)
	{
		string strText = kStringVector[uiIndex];

		if (CheckComment(strText) || CheckVersion(strText))
		{
			continue;
		}

		if (ParseTitle(strText))
		{
			kSubMap.clear();
			m_kTitleMap.insert(make_pair(strText,kSubMap));
			continue;
		}

		if (0 != m_kTitleMap.size())
		{
			if (!ParseSubTitle(strText,kSubMap))
			{
				continue;
			}
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

bool CIniFile::CheckVersion( string strText )
{
	if (strlen("version") > strText.size() || 0 != m_nVersion)
	{
		return false;
	}

	int nPos = strText.find_first_of("version");
	string strValue = "";

	if (0 != nPos)
	{
		return false;
	}

	int nIndex = strText.find_first_of('=',nPos);

	if (-1 == nIndex)
	{
		return false;
	}

	strValue = strText.substr(nIndex + 1,strText.length() - 1);

	m_nVersion = atoi(strValue.c_str());

	return true;
}

bool CIniFile::ParseTitle( string& strText )
{
	if (3 > strText.size())
	{
		return false;
	}

	if ('[' != strText[0] || ']' != strText[strText.length() - 1])
	{
		return false;
	}

	strText = strText.substr(1,strText.length() - 1).substr(0,strText.length() - 2);

	return true;
}

bool CIniFile::ParseSubTitle( string strText,SubTitleMap& kTitleMap )
{
	if (0 == strText.length())
	{
		return false;
	}

	int nPos = strText.find_first_of('=');

	if (-1 == nPos || strText.find_last_of('=') != nPos)
	{
		return false;
	}

	string strSubTitle = strText.substr(0,nPos);
	string strTitleValue = strText.substr(nPos + 1,strText.length() - 1);

	kTitleMap.insert(make_pair(strSubTitle,strTitleValue));

	return true;
}

END_KERNEL