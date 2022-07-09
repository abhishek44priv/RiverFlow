#pragma once
#include"RfD2Render.h"
class RfD2HWNDRender:public RfD2Render
{
public:
	void Resize(int w, int h);
	friend class RfD2Factory;
};

