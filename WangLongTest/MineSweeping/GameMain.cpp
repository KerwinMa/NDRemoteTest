#include "stdafx.h"
#include <INIParser.h>

using namespace GameKernel;

int WINAPI _tWinMain (HINSTANCE hInstance, 
					  HINSTANCE hPrevInstance, 
					  LPTSTR szCmdLine, 
					  int iCmdShow)
{
	CINIParser kParser(DEF_CONFIG_FILE);

	return 1;
}