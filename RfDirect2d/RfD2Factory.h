#pragma once
#include"RfD2HWNDRender.h"
class RfD2Factory
{
public:
	static RfD2HWNDRender* CreateHWNDRender(void* hwnd);
	static void* n_factory ;
};

