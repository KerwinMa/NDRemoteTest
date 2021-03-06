/*
*
*/

#ifndef INIPARSER_H
#define INIPARSER_H

#include "GameKernelDefine.h"

BEGIN_KERNEL

class KERNEL_DLL CIniFile
{
public:

	typedef map<string,string> SubTitleMap,*SubTitleMapPtr;
	typedef map<string,SubTitleMapPtr> TitleMap;

	CIniFile();
	virtual ~CIniFile();

	virtual bool LoadFile(const char* pszFilename);
	virtual void Unload();
	char* GetString(const char* pszTitle,const char* pszSubTitle) const;
	bool GetInt(const char* pszTitle,const char* pszSubTitle,int& nData) const;
	bool GetFloat(const char* pszTitle,const char* pszSubTitle,float& fData) const;

protected:

	bool ClearStringMap(TitleMap* pkVector);
	virtual bool ParseData(StringVector kStringVector);
	virtual bool CheckComment(string strText);
	virtual bool CheckVersion(string strText);
	virtual bool ParseTitle(string& strText);
	virtual bool ParseSubTitle(string strText,SubTitleMapPtr pkTitleMap);

	TitleMap m_kTitleMap;

	INLINE_CONST_READONLY(char*,m_pszFilename,Filename);
	INLINE_READONLY(bool,m_bIsInit,Initialised);
	INLINE_READONLY(int,m_nVersion,Version);

private:
};

END_KERNEL

#endif