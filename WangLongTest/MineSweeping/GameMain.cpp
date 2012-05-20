#include "stdafx.h"
#include <IniFile.h>
#include <MainGameFrame.h>

using namespace GameKernel;

int WINAPI _tWinMain (HINSTANCE hInstance, 
					  HINSTANCE hPrevInstance, 
					  LPTSTR szCmdLine, 
					  int iCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(szCmdLine);

	CIniFile kParser;
	
	if (!kParser.LoadFile(DEF_CONFIG_FILE))
	{
		return 0;
	}

	char* strValue = kParser.GetString("title0","subtitle0");

	CMainGameFrame kGameFrame(TEXT("Mine Sweeping"));

	kParser.Unload();

	return CCApplication::sharedApplication().run();
}