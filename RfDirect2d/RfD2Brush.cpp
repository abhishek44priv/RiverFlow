#include"pch.h"
#include "RfD2Brush.h"
#include"RfD2Render.h"
#define D2_BRUSH ((ID2D1Brush*)info.n_brush)
RfD2Brush::RfD2Brush()
{
	
}

RfD2Brush::RfD2Brush(RfD2Render* render)
{
	
}

RfD2Brush::~RfD2Brush()
{
	Destroy();
}

void* RfD2Brush::GetNativeBrush()
{
	return info.n_brush;
}

void RfD2Brush::Destroy()
{
	if (info.n_brush!=nullptr) {
		D2_BRUSH->Release();
		info.n_brush = nullptr;
	}
}
