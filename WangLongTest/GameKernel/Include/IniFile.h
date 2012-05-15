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

	typedef vector<string> StringVector,*StringVectorPtr;
	typedef hash_map<string,string> SubTitleMap;
	typedef hash_map<string,SubTitleMap> TitleMap;

	CIniFile();
	virtual ~CIniFile();

	virtual bool LoadFile(const char* pszFilename);
	virtual void Unload();
	const char* GetString(const char* pszTitle,const char* pszSubTitle) const;
	bool GetInt(const char* pszTitle,const char* pszSubTitle,int& nData) const;
	bool GetFloat(const char* pszTitle,const char* pszSubTitle,float& fData) const;
	int GetVersion() const;

protected:

	virtual void TrimSpace(string& strText);
	virtual bool ParseData(StringVector kStringVector);
	virtual bool CheckComment(string strText);

	TitleMap m_kTitleMap;

	INLINE_CONST_READONLY(char*,m_pszFilename,Filename);
	INLINE_READONLY(bool,m_bIsInit,Initialised);

private:
};

END_KERNEL

#endif