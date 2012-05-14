/*
*
*/

#ifndef INIPARSER_H
#define INIPARSER_H

#include "GameKernelDefine.h"

BEGIN_KERNEL

class KERNEL_DLL CINIParser
{
public:

	typedef vector<string> StringVector,*StringVectorPtr;

	CINIParser();
	virtual ~CINIParser();

	virtual bool LoadFile(const char* pszFilename);

protected:

	StringVectorPtr m_pkDataVector;

	INLINE_CONST_READONLY(char*,m_pszFilename,Filename);
	INLINE_READONLY(bool,m_bIsInit,Initialised);

private:
};

END_KERNEL

#endif