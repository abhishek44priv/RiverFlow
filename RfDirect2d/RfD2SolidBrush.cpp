#include"pch.h"
#include "RfD2SolidBrush.h"
#include"RfD2Render.h"
#define D2_BRUSH ((ID2D1SolidColorBrush*)info.n_brush)
#define D2_NRENDER ((ID2D1RenderTarget*)render->GetNativeRender())
RfD2SolidBrush::RfD2SolidBrush()
{
}

RfD2SolidBrush::RfD2SolidBrush(RfD2Render* render, RfColor color)
{
	Create(render, color);
}

void RfD2SolidBrush::Create(RfD2Render* render, RfColor color)
{
	Destroy();
	{
		ID2D1SolidColorBrush* brush;
		D2_NRENDER->CreateSolidColorBrush(_D2ColorF(color), &brush);
		info.n_brush = brush;
	}
}

void RfD2SolidBrush::SetColor(RfColor color)
{
	D2_BRUSH->SetColor(_D2ColorF(color));
}
