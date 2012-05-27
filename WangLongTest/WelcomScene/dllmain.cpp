// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "WelcomScene.h"
#include <GameManager.h>

CWelcomScene* g_pkPlugin = 0;

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

extern "C" void WELCOMSCENE_DLL StartPlugin()
{
	g_pkPlugin = CWelcomScene::node();

	g_pGame->InitialiseScene(g_pkPlugin);
}
extern "C" void WELCOMSCENE_DLL StopPlugin()
{
	g_pGame->UninitialiseScene(g_pkPlugin);
}