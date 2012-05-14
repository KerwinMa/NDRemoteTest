#include "stdafx.h"
#include <INIParser.h>

using namespace GameKernel;

int WINAPI _tWinMain (HINSTANCE hInstance, 
					  HINSTANCE hPrevInstance, 
					  LPTSTR szCmdLine, 
					  int iCmdShow)
{
	CINIParser kParser;
	
	if (!kParser.LoadFile(DEF_CONFIG_FILE))
	{
		return 0;
	}

	return 1;
}