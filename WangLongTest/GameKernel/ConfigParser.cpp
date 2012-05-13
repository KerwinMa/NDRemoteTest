#include "stdafx.h"
#include "ConfigParser.h"

BEGIN_KERNEL

IConfigParser::IConfigParser(){}
IConfigParser::~IConfigParser(){}

IConfigParser* IConfigParser::CreateConfigParser( ConfigType eType,const char* pszConfigFile)
{
	IConfigParser* pkParser = 0;

	if (0 == pszConfigFile || !*pszConfigFile)
	{
		return 0;
	}

	switch (eType)
	{
	case CON_INI:
		{

		}
		break;
	case CON_XML:
		{

		}
		break;
	case CON_NONE:
	default:
		return 0;
	}

	return pkParser;
}

END_KERNEL