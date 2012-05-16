#include "stdafx.h"
#include <IniFile.h>

using namespace GameKernel;

int WINAPI _tWinMain (HINSTANCE hInstance, 
					  HINSTANCE hPrevInstance, 
					  LPTSTR szCmdLine, 
					  int iCmdShow)
{
	CIniFile kParser;
	
	if (!kParser.LoadFile(DEF_CONFIG_FILE))
	{
		return 0;
	}

	char* strValue = kParser.GetString("title0","subtitle0");

	return 1;
}