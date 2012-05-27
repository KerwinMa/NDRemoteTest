#include "stdafx.h"
#include <AlphaKernel.h>

using namespace GameKernel;

int main(int argc,char** argv)
{
	CAlphaKernel kConvert;

	if (!kConvert.BeginConvert(L"test.bmp",L"test.png"))
	{
		return 0;
	}

	return 1;
}