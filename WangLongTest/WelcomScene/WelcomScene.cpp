#include "stdafx.h"
#include "WelcomScene.h"

static const char* g_pszName = "WelcomeScene";
CWelcomScene::CWelcomScene():m_pkRootScene(0){}
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

bool CWelcomScene::BeginScene()
{
	return true;
}

bool CWelcomScene::EndScene()
{
	return true;
}

bool CWelcomScene::init()
{
	return true;
}