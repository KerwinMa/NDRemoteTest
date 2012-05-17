#include "stdafx.h"
#include "WelcomScene.h"

static const char* g_pszName = "WelcomeScene";
CWelcomScene::CWelcomScene(){}
CWelcomScene::~CWelcomScene(){}

const char* CWelcomScene::GetName() const
{
	return g_pszName;
}

bool CWelcomScene::Initialise()
{
	return true;
}

bool CWelcomScene::Shutdown()
{
	return true;
}

bool CWelcomScene::Install()
{
	return true;
}

bool CWelcomScene::Uninstall()
{
	return true;
}