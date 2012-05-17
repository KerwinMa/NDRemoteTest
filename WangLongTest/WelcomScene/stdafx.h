#pragma once

#define WIN32_LEAN_AND_MEAN

#ifdef WELCOMSCENE_EXPORTS
#define WELCOMSCENE_DLL __declspec(dllexport)
#else
#define WELCOMSCENE_DLL __declspec(dllimport)
#endif

#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <vector>
#include <map>
#include <string>

#include <GameKernelDefine.h>
#include <GameScene.h>

using namespace std;
using namespace GameKernel;