#include "stdafx.h"
#include <IniFile.h>
#include <GameManager.h>

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

	if (!CGameManager::Create("GameScene"))
	{
		return false;
	}

	char* strValue = kParser.GetString("title0","subtitle0");

	if (!g_pGame->LoadGame("WelcomScene"))
	{
		return 0;
	}

	return 1;
}