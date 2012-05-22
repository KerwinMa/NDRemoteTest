/*
*
*/

#pragma once

#include "GameKernelDefine.h"

BEGIN_KERNEL

class CAlphaKernel
{
public:

	CAlphaKernel(const char* pszConfigFile);
	virtual ~CAlphaKernel();

	INLINE_CONST_READONLY(char*,m_pszConfigFile,ConfigFile);
	INLINE_READONLY(ULONG_PTR,m_pulGDIToken,GDIToken);
	INLINE_READONLY(ConfigInfo,m_kConfigInfo,ConfigInfo);
	INLINE_READONLY(bool,m_bIsInit,Initialised);

protected:

	virtual bool InitialiseConfigFile();
	virtual bool InitialiseGDIPlus();

private:
};

END_KERNEL