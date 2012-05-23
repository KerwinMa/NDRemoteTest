/*
*
*/

#pragma once

#include "GameKernelDefine.h"

BEGIN_KERNEL

class KERNEL_DLL CAlphaKernel
{
public:

	CAlphaKernel(const char* pszConfigFile);
	virtual ~CAlphaKernel();

	virtual bool BeginConvert(const wchar_t* pszFilename,const wchar_t* pszOutFilename);

	INLINE_CONST_READONLY(char*,m_pszConfigFile,ConfigFile);
	INLINE_READONLY(ULONG_PTR,m_pulGDIToken,GDIToken);
	INLINE_READONLY(ConfigInfo,m_kConfigInfo,ConfigInfo);
	INLINE_READONLY(bool,m_bIsInit,Initialised);

protected:

	virtual bool InitialiseConfigFile();
	virtual bool InitialiseGDIPlus();
	int GetEncoderClsid(const wchar_t* pszFormat,CLSID* pClsid);

private:
};

END_KERNEL