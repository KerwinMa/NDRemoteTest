#include "stdafx.h"
#include "MainGameFrame.h"
#include "GameManager.h"

BEGIN_KERNEL

CMainGameFrame::CMainGameFrame(LPTSTR pszGameName):
m_pszGameName(0),
m_bBoostLog(false)
{
	m_pszGameName = new char[MAX_PATH];
	memset(m_pszGameName,0,sizeof(char) * MAX_PATH);

	if (pszGameName && *pszGameName)
	{
		wcstombs(m_pszGameName,pszGameName,MAX_PATH);
	}
}

CMainGameFrame::~CMainGameFrame()
{
	SafeDeleteArray(m_pszGameName);

	CGameManager::Destroy();
}

bool CMainGameFrame::initInstance()
{
	CCEGLView* pkMainWindow = new CCEGLView;
	wchar_t szTempName[MAX_PATH] = {0};
	size_t stCount = 0;

 	if (!InitialiseLogSystem("game.log"))
 	{
 		return false;
 	}

// 	if (!ReadConfigInfo("config.ini",m_kConfigInfo))
// 	{
// 		return false;
// 	}

	if (0 == pkMainWindow || !pkMainWindow->Create(szTempName,800,600))
	{
		return false;
	}

	if (!CGameManager::Create("GameScene"))
	{
		return false;
	}

	return true;
}

bool CMainGameFrame::applicationDidFinishLaunching()
{
	if (!g_pGame->LoadGame("WelcomScene"))
	{
		return 0;
	}

	return true;
}

void CMainGameFrame::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->pause();
}

void CMainGameFrame::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->resume();
}

bool CMainGameFrame::InitialiseLogSystem( const char* pszLoggingFile )
{
	if (0 == pszLoggingFile || !*pszLoggingFile)
	{
		return false;
	}

#ifdef BOOST_1_49

	logging::init_log_to_console(std::clog, keywords::format = "%TimeStamp%: %_%");
	logging::init_log_to_file(pszLoggingFile,keywords::filter = flt::attr< severity_level >
		("Severity", std::nothrow) >= normal,keywords::format = fmt::format("%1% [%2%] <%3%> %4%")%
		fmt::date_time("TimeStamp", std::nothrow)% fmt::time_duration("Uptime", std::nothrow)%
		fmt::attr< severity_level >("Severity", std::nothrow)% fmt::message());
	logging::add_common_attributes();

	m_bBoostLog = true;

#endif

	return true;
}

END_KERNEL