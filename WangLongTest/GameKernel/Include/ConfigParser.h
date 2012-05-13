/*
*
*/

#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include "GameKernelDefine.h"

BEGIN_KERNEL

class KERNEL_DLL IConfigParser
{
public:

	IConfigParser();
	virtual ~IConfigParser();

	static IConfigParser* CreateConfigParser(ConfigType eType,const char* pszConfigFile);

protected:
private:
};

END_KERNEL

#endif