#include "pch.h"
#include"RfD2Render.h"
#include "RfD2Bitmap.h"
#define D2_NRENDER ((ID2D1RenderTarget*)render->GetNativeRender())
#define D2_NATIVE ((ID2D1Bitmap*)n_native)
RfD2Bitmap::RfD2Bitmap()
{
}

RfD2Bitmap::RfD2Bitmap(RfD2Render* render, int w, int h, void* pixels)
{
	Create(render, w, h, pixels);
}

void RfD2Bitmap::Create(RfD2Render* render, int w, int h, void* pixels)
{
	if (n_native)
		Destroy();
	ID2D1Bitmap* bitmap;
	auto pixelFormat = D2D1::PixelFormat(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		D2D1_ALPHA_MODE_PREMULTIPLIED
	);
	auto prop = D2D1::BitmapProperties(
		pixelFormat,
		96,
		96);
	D2_NRENDER->CreateBitmap(SizeU(w, h), pixels, w * 4, prop, &bitmap);
	n_native = bitmap;
}

RfD2Bitmap::~RfD2Bitmap()
{
	Destroy();
}

void* RfD2Bitmap::GetNative()
{
	return n_native;
}

void RfD2Bitmap::Destroy()
{
	if (n_native)
	{
		D2_NATIVE->Release();
		n_native = nullptr;
	}
}
