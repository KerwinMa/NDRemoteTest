// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "GameSceneImp.h"
#include <GameManager.h>

CGameSceneImp* g_pkPlugin = 0;

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

extern "C" void GAMESCENE_DLL StartPlugin()
{
	g_pkPlugin = CGameSceneImp::node();

	g_pGame->InitialiseScene(g_pkPlugin);
}
extern "C" void GAMESCENE_DLL StopPlugin()
{
	g_pGame->UninitialiseScene(g_pkPlugin);
	g_pkPlugin = 0;
}