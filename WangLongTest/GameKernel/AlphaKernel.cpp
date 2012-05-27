#include "stdafx.h"
#include "AlphaKernel.h"

BEGIN_KERNEL

CAlphaKernel::CAlphaKernel():
m_pszConfigFile(0),
m_pulGDIToken(0),
m_bIsInit(false)
{
	m_pszConfigFile = new char[MAX_PATH];

	memset(&m_kConfigInfo,0,sizeof(ConfigInfo));
	memset(m_pszConfigFile,0,sizeof(char) * MAX_PATH);

	if (InitialiseConfigFile())
	{
		if (InitialiseGDIPlus())
		{
			m_bIsInit = true;
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

	if (Ok != GdiplusStartup(&m_pulGDIToken,&kGdiInput,0))
	{
		return false;
	}

	return true;
}

bool CAlphaKernel::InitialiseConfigFile()
{
	if (0 == m_pszConfigFile)
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

bool CAlphaKernel::BeginConvert(const wchar_t* pszFilename,
								const wchar_t* pszOutFilename)
{
	if (0 == pszFilename || !*pszFilename ||
		0 == pszOutFilename || !*pszOutFilename)
	{
		return false;
	}

	Bitmap* pkImage = Bitmap::FromFile(pszFilename);
	unsigned int uiWidth = 0;
	unsigned int uiHeight = 0;
	CLSID kClsid;

	memset(&kClsid,0,sizeof(CLSID));

	if (0 == pkImage)
	{
		return false;
	}

	uiWidth = pkImage->GetWidth();
	uiHeight = pkImage->GetHeight();

	for (unsigned int y = 0;y < uiHeight;y++)
	{
		for (unsigned int x = 0;x < uiWidth;x++)
		{
			Color kColor;
			pkImage->GetPixel(x,y,&kColor);

			if (kColor.GetR() == m_kConfigInfo.kColor.btAlphaRed &&
				kColor.GetG() == m_kConfigInfo.kColor.btAlphaGreen &&
				kColor.GetB() == m_kConfigInfo.kColor.btAlphaBlue)
			{
				kColor = Color(m_kConfigInfo.kColor.btAlphaValue,
					m_kConfigInfo.kColor.btAlphaRed,
					m_kConfigInfo.kColor.btAlphaGreen,
					m_kConfigInfo.kColor.btAlphaBlue);

				pkImage->SetPixel(x,y,kColor);
			}
		}
	}

	GetEncoderClsid(L"image/png",&kClsid);

	pkImage->Save(pszOutFilename,&kClsid,0);

	return true;
}

int CAlphaKernel::GetEncoderClsid( const wchar_t* pszFormat,
								  CLSID* pClsid )
{
	unsigned int uiNum = 0;
	unsigned int uiSize = 0;
	ImageCodecInfo* pkImageInfo = 0;

	GetImageEncodersSize(&uiNum,&uiSize);

	if (0 == uiSize)
	{
		return -1;
	}

	pkImageInfo = (ImageCodecInfo*)(malloc(uiSize));

	if (0 == pkImageInfo)
	{
		return -1;
	}

	GetImageEncoders(uiNum,uiSize,pkImageInfo);

	for (unsigned int uiIndex = 0;uiIndex < uiNum;uiIndex++)
	{
		if (0 == wcscmp(pkImageInfo[uiIndex].MimeType,pszFormat))
		{
			*pClsid = pkImageInfo[uiIndex].Clsid;
			SafeDelete(pkImageInfo);

			return uiIndex;
		}
	}

	return -1;
}

END_KERNEL