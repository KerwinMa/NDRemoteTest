#include "stdafx.h"
#include "GameResult.h"
#include <GameManager.h>

CGameResult* g_pkPlugin = 0;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern "C" void RESULTCENE_DLL StartPlugin()
{
	g_pkPlugin = CGameResult::node();

	g_pGame->InitialiseScene(g_pkPlugin);
}
extern "C" void RESULTCENE_DLL StopPlugin()
{
	g_pGame->UninitialiseScene(g_pkPlugin);
	g_pkPlugin = 0;
}