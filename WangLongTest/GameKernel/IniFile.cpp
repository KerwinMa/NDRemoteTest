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
	ClearStringMap(&m_kTitleMap);
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
	ClearStringMap(&m_kTitleMap);
}

char* CIniFile::GetString( const char* pszTitle,
								const char* pszSubTitle ) const
{
	if (0 == pszTitle || !*pszTitle || 0 == pszSubTitle || !*pszSubTitle)
	{
		return 0;
	}

	char* pszReturn = 0;
	string strTitle = pszTitle;
	string strSubTitle = pszSubTitle;
	string strValue = "";

	SubTitleMapPtr pkSubMap = 0;
	SubTitleMap::iterator itSubMap;

	if (m_kTitleMap.end() == m_kTitleMap.find(strTitle))
	{
		return 0;
	}

	pkSubMap = m_kTitleMap.find(strTitle)->second;

	if (0 == pkSubMap->size())
	{
		return false;
	}

	itSubMap = pkSubMap->find(strSubTitle);

	if (pkSubMap->end() == itSubMap)
	{
		return 0;
	}

	strValue = itSubMap->second;

	pszReturn = new char[strValue.length() + 1];
	memset(pszReturn,0,sizeof(char) * strValue.length());
	strcpy_s(pszReturn,strValue.length() + 1,strValue.c_str());

	return pszReturn;
}

bool CIniFile::GetInt( const char* pszTitle,
					  const char* pszSubTitle,
					  int& nData ) const
{
	if (0 == pszTitle || !*pszTitle || 0 == pszSubTitle || !*pszSubTitle)
	{
		return false;
	}

	char* pszTemp = GetString(pszTitle,pszSubTitle);

	if (0 == pszTemp || !*pszTemp)
	{
		SafeDeleteArray(pszTemp);
		return false;
	}

	nData = atoi(pszTemp);
	SafeDeleteArray(pszTemp);

	return true;
}

bool CIniFile::GetFloat( const char* pszTitle,
						const char* pszSubTitle,
						float& fData ) const
{
	if (0 == pszTitle || !*pszTitle || 0 == pszSubTitle || !*pszSubTitle)
	{
		return false;
	}

	char* pszTemp = GetString(pszTitle,pszSubTitle);

	if (0 == pszTemp || !*pszTemp)
	{
		SafeDeleteArray(pszTemp);
		return false;
	}

	fData = static_cast<float>(atof(pszTemp));
	SafeDeleteArray(pszTemp);

	return true;
}

bool CIniFile::ParseData( StringVector kStringVector )
{
	if (0 == kStringVector.size())
	{
		return false;
	}

	SubTitleMapPtr pkSubMap = 0;

	for (unsigned int uiIndex = 0;uiIndex < kStringVector.size(); uiIndex++)
	{
		string strText = kStringVector[uiIndex];

		if (CheckComment(strText) || CheckVersion(strText))
		{
			continue;
		}

		if (ParseTitle(strText))
		{
			SafeDelete(pkSubMap);
			pkSubMap = new SubTitleMap;
			m_kTitleMap.insert(make_pair(strText,pkSubMap));
			continue;
		}

		if (0 != m_kTitleMap.size())
		{
			if (!ParseSubTitle(strText,pkSubMap))
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

	strText = strText.substr(1,strText.length() - 1).
		substr(0,strText.length() - 2);

	return true;
}

bool CIniFile::ParseSubTitle( string strText,
							 SubTitleMapPtr pkTitleMap )
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

	pkTitleMap->insert(make_pair(strSubTitle,strTitleValue));

	return true;
}

bool CIniFile::ClearStringMap( TitleMap* pkVector )
{
	if (0 == pkVector)
	{
		return false;
	}

	for (TitleMap::iterator it = pkVector->begin();
		pkVector->end() != it;it++)
	{
		SubTitleMapPtr pkSub = it->second;
		SafeDelete(pkSub);
	}

	pkVector->clear();

	return true;
}

END_KERNEL