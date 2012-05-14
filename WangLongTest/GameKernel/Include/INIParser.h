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

	CINIParser(const char* pszFilename);
	virtual ~CINIParser();

protected:

	virtual bool Initialise();

	INLINE_CONST_READONLY(char*,m_pszFilename,Filename);
	INLINE_READONLY(bool,m_bIsInit,Initialised);

private:
};

END_KERNEL

#endif