#include "stdafx.h"
#include "AlphaKernel.h"

BEGIN_KERNEL

CAlphaKernel::CAlphaKernel(const char* pszConfigFile):
m_pszConfigFile(0),
m_pulGDIToken(0),
m_bIsInit(false)
{
	m_pszConfigFile = new char[MAX_PATH];

	memset(&m_kConfigInfo,0,sizeof(ConfigInfo));
	memset(m_pszConfigFile,0,sizeof(char) * MAX_PATH);

	if (pszConfigFile && *pszConfigFile)
	{
		strcpy_s(m_pszConfigFile,MAX_PATH,pszConfigFile);

		if (InitialiseConfigFile())
		{
			if (InitialiseGDIPlus())
			{
				m_bIsInit = true;
			}
		}
	}
}

CAlphaKernel::~CAlphaKernel()
{
	GdiplusShutdown(m_pulGDIToken);
	SafeDeleteArray(m_pszConfigFile);
}

bool CAlphaKernel::InitialiseGDIPlus()
{
	GdiplusStartupInput kGdiInput;

	GdiplusStartup(&m_pulGDIToken,&kGdiInput,0);

	if (Ok != m_pulGDIToken)
	{
		return false;
	}

	return true;
}

bool CAlphaKernel::InitialiseConfigFile()
{
	if (0 == m_pszConfigFile || !*m_pszConfigFile)
	{
		return false;
	}

	//ptree kReadTree;

	//read_ini(m_pszConfigFile,kReadTree);

// 	m_kConfigInfo.kColor.btAlphaRed = kReadTree.get<unsigned char>("Color.AlphaRed");
// 	m_kConfigInfo.kColor.btAlphaGreen = kReadTree.get<unsigned char>("Color.AlphaGreen");
// 	m_kConfigInfo.kColor.btAlphaBlue = kReadTree.get<unsigned char>("Color.AlphaBlue");
// 	m_kConfigInfo.kColor.btAlphaValue = kReadTree.get<unsigned char>("Color.AlphaValue");
// 
// 	strcpy_s(m_kConfigInfo.kPath.szPathFolder,MAX_PATH,kReadTree.get<string>("Path.PathFolder").c_str());
// 	strcpy_s(m_kConfigInfo.kPath.szSaveFolder,MAX_PATH,kReadTree.get<string>("Path.SaveFolder").c_str());

	m_kConfigInfo.kColor.btAlphaRed = 255;
	m_kConfigInfo.kColor.btAlphaGreen = 255;
	m_kConfigInfo.kColor.btAlphaBlue = 255;
	m_kConfigInfo.kColor.btAlphaValue = 0;

	strcpy_s(m_kConfigInfo.kPath.szPathFolder,MAX_PATH,"data");
	strcpy_s(m_kConfigInfo.kPath.szSaveFolder,MAX_PATH,"data");


	return true;
}

END_KERNEL