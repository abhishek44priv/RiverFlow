
#include"pch.h"
#include "RfD2HWNDRender.h"
#define D2_RENDER ((ID2D1HwndRenderTarget*)info.n_d2Render)

void RfD2HWNDRender::Resize(int w, int h)
{
	D2_RENDER->Resize(SizeU(w, h));
}
