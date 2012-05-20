#pragma once

#define WIN32_LEAN_AND_MEAN

#ifdef GAMESCENE_EXPORTS
#define GAMESCENE_DLL __declspec(dllexport)
#else
#define GAMESCENE_DLL __declspec(dllimport)
#endif

#include <tchar.h>
#include <cocos2d.h>
#include <vector>
#include <map>
#include <hash_map>
#include <string>

using namespace stdext;
using namespace std;
using namespace cocos2d;