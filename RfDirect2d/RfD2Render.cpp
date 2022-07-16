#include"pch.h"
#include "RfD2Render.h"
#include"RfD2Brush.h"
#include"RfD2Bitmap.h"
#define D2_RENDER ((ID2D1RenderTarget*)info.n_d2Render)
#define _D2Rect(r) RectF(r.x+info.offset.x,r.y+info.offset.y,r.x+r.width+info.offset.x,r.y+r.height+info.offset.y)

#define _PointF(p) Point2F(p.x+info.offset.x,p.y+info.offset.y)
static ComPtr<ID2D1SolidColorBrush> CreateSolidBrush(
	ID2D1RenderTarget* render,
	D2D1_COLOR_F color = ColorF(ColorF::Chocolate)
) {
	ComPtr<ID2D1SolidColorBrush> brush;
	render->CreateSolidColorBrush(color, &brush);
	return brush;
}

static D2D1_DRAW_TEXT_OPTIONS TO_DRAW_TEXT_OPTIONS(RfTxtOverFlow of)
{
	switch (of)
	{
	case RfTxtOverFlow::CLIP:
		return D2D1_DRAW_TEXT_OPTIONS_CLIP;
	case RfTxtOverFlow::NOT_CLIP:
		return D2D1_DRAW_TEXT_OPTIONS_NONE;
	}
	return D2D1_DRAW_TEXT_OPTIONS_NONE;


}

RfD2Render::RfD2Render()
{
	
}

RfD2Render::~RfD2Render()
{
	if (D2_RENDER)
		D2_RENDER->Release();
}

RfPoint RfD2Render::GetOffset()
{
	return info.offset;
}

void RfD2Render::PlusOffest(float offx, float offy)
{
	info.offset.x += offx;
	info.offset.y += offy;
}


void RfD2Render::ResetOffset()
{
	info.offset.Set(0.f, 0.f);
}

void RfD2Render::PushClipRect(RfRect rect)
{
	D2_RENDER->PushAxisAlignedClip(_D2Rect(rect),
		D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
}

void RfD2Render::PopClipRect()
{
	D2_RENDER->PopAxisAlignedClip();
}
RfSize RfD2Render::GetSize()
{
	auto ss = D2_RENDER->GetSize();
	return RfSize(ss.width,ss.height);
}
#define D2_STYLE ((ID2D1StrokeStyle*)style.Native())
void RfD2Render::DrawRect(RfRect rect, RfColor color, float width, RfD2Style style)
{
	auto drect = _D2Rect(rect);
	auto brush =
		CreateSolidBrush(D2_RENDER, _D2ColorF(color));
	auto dstyle = D2_STYLE;
	D2_RENDER->DrawRectangle(drect, brush.Get(), width, dstyle); if (dstyle)dstyle->Release();
}


void RfD2Render::FillRect(RfRect rect, RfColor color)
{
	auto drect = _D2Rect(rect);
	auto brush =
		CreateSolidBrush(D2_RENDER, _D2ColorF(color));
	D2_RENDER->FillRectangle(drect, brush.Get());
}

void RfD2Render::DrawRRect(RfRect rect, float xRad, float yRad, RfColor color, float width, RfD2Style style)
{
	auto drect = _D2Rect(rect);
	auto brush =
		CreateSolidBrush(D2_RENDER, _D2ColorF(color));
	auto dstyle = D2_STYLE;
	D2_RENDER->DrawRoundedRectangle(RoundedRect(
		drect, xRad, yRad
	), brush.Get(), width, dstyle); if (dstyle)dstyle->Release();
}

void RfD2Render::FillRRect(RfRect rect, float xRad, float yRad, RfColor color)
{
	auto drect = _D2Rect(rect);
	auto brush =
		CreateSolidBrush(D2_RENDER, _D2ColorF(color));
	D2_RENDER->FillRoundedRectangle(RoundedRect(
		drect, xRad, yRad
	), brush.Get());
}

void RfD2Render::DrawEllipse(RfPoint center, float xRad, float yRad, RfColor color, float width, RfD2Style style)
{

	auto brush =
		CreateSolidBrush(D2_RENDER, _D2ColorF(color));
	auto dstyle = D2_STYLE;
	D2_RENDER->DrawEllipse(Ellipse(
		_PointF(center), xRad, yRad
	), brush.Get(), width, dstyle); if (dstyle)dstyle->Release();
}

void RfD2Render::FillEllipse(RfPoint center, float xRad, float yRad, RfColor color)
{
	auto brush =
		CreateSolidBrush(D2_RENDER, _D2ColorF(color));
	D2_RENDER->FillEllipse(Ellipse(
		_PointF(center), xRad, yRad
	), brush.Get());
}
void RfD2Render::DrawLine(RfPoint p1, RfPoint p2, RfColor color, float width, RfD2Style style)
{
	auto brush =
		CreateSolidBrush(D2_RENDER, _D2ColorF(color));
	auto dstyle = D2_STYLE;
	D2_RENDER->DrawLine(_PointF(p1), _PointF(p2),
		brush.Get(), width, dstyle); if (dstyle)dstyle->Release();
}
#define _N_BRUSH ((ID2D1Brush*)brush.GetNativeBrush())


void RfD2Render::DrawRect(RfRect rect, RfD2Brush& brush, float width, RfD2Style style)
{
	auto drect = _D2Rect(rect);
	auto dstyle = D2_STYLE;
	D2_RENDER->DrawRectangle(drect, _N_BRUSH, width, dstyle); if (dstyle)dstyle->Release();
}


void RfD2Render::FillRect(RfRect rect, RfD2Brush& brush)
{
	auto drect = _D2Rect(rect);


	D2_RENDER->FillRectangle(drect, _N_BRUSH);
}

void RfD2Render::DrawRRect(RfRect rect, float xRad, float yRad, RfD2Brush& brush, float width, RfD2Style style)
{
	auto drect = _D2Rect(rect);

	auto dstyle = D2_STYLE;
	D2_RENDER->DrawRoundedRectangle(RoundedRect(
		drect, xRad, yRad
	), _N_BRUSH, width, dstyle); if (dstyle)dstyle->Release();

}

void RfD2Render::FillRRect(RfRect rect, float xRad, float yRad, RfD2Brush& brush)
{
	auto drect = _D2Rect(rect);


	D2_RENDER->FillRoundedRectangle(RoundedRect(
		drect, xRad, yRad
	), _N_BRUSH);
}

void RfD2Render::DrawEllipse(RfPoint center, float xRad, float yRad, RfD2Brush& brush, float width, RfD2Style style)
{


	auto dstyle = D2_STYLE;
	D2_RENDER->DrawEllipse(Ellipse(
		_PointF(center), xRad, yRad
	), _N_BRUSH, width, dstyle); if (dstyle)dstyle->Release();
}

void RfD2Render::FillEllipse(RfPoint center, float xRad, float yRad, RfD2Brush& brush)
{


	D2_RENDER->DrawEllipse(Ellipse(
		_PointF(center), xRad, yRad
	), _N_BRUSH);
}



void RfD2Render::DrawLine(RfPoint p1, RfPoint p2, RfD2Brush& brush, float width, RfD2Style style)
{
	auto dstyle = D2_STYLE;
	D2_RENDER->DrawLine(_PointF(p1), _PointF(p2),
		_N_BRUSH, width, dstyle); if (dstyle)dstyle->Release();
}
#define WRITE_FORMAT ((IDWriteTextFormat*)txtStyle.Native())
void RfD2Render::DrawString(const wchar_t* text, RfRect rect, RfTextStyle txtStyle,
	RfD2Brush& brush)
{
	auto format = WRITE_FORMAT;
	D2_RENDER->DrawTextW(text, lstrlenW(text), format, _D2Rect(rect),
		_N_BRUSH);
	if (format)format->Release();
}

void RfD2Render::DrawString(const wchar_t* text, RfRect rect, RfTextStyle txtStyle, RfColor color)
{
	auto brush =
		CreateSolidBrush(D2_RENDER, _D2ColorF(color));
	auto format = WRITE_FORMAT;
	D2_RENDER->DrawTextW(text, lstrlenW(text), format, _D2Rect(rect),
		brush.Get(), TO_DRAW_TEXT_OPTIONS(txtStyle.overflow));
	if (format)format->Release();
}

void RfD2Render::DrawTextLayout(RfTextLayout& txtLayout, RfPoint xy, RfColor color)
{
	
	auto brush =
		CreateSolidBrush(D2_RENDER, _D2ColorF(color));
	auto layout = ((IDWriteTextLayout*)txtLayout.info.n_layout);
	D2_RENDER->DrawTextLayout(_PointF(xy), layout, brush.Get(),
		TO_DRAW_TEXT_OPTIONS(txtLayout.info.style.overflow));

}


void RfD2Render::DrawBitmap(RfD2Bitmap* bitmap, RfRect rect)
{
	auto dbitmap = (ID2D1Bitmap*)bitmap->GetNative();
	D2_RENDER->DrawBitmap(dbitmap, _D2Rect(rect));
}

void RfD2Render::Begin()
{
	D2_RENDER->BeginDraw();
}

void RfD2Render::End()
{
	D2_RENDER->EndDraw();
}

void RfD2Render::Clear(RfColor color, RfRect rect)
{
	if (rect.IsEmptyArea()) {
		auto ss = this->GetSize();
		rect = { 0,0,ss.width,ss.height };
	}
	this->FillRect(rect, color);

}


void* RfD2Render::GetNativeRender()
{
	return info.n_d2Render;
}


