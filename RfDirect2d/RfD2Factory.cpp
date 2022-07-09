#include"pch.h"
#include "RfD2Factory.h"
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"Dwrite.lib")
#include"RfWriteFactory.h"
void* RfD2Factory::n_factory = nullptr;
void * RfWriteFactory::n_factory = nullptr;

#define D2_FACTORY ((ID2D1Factory*)RfD2Factory::n_factory)
#define WRITE_FACTORY ((IDWriteFactory*)RfWriteFactory::n_factory)
static void CreateFactory()
{
	ID2D1Factory* fff=nullptr;
	IDWriteFactory* www = nullptr;
	if (D2_FACTORY == nullptr)
	{
		auto result = CoInitialize(NULL);
		//direct2d factory
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
			&fff);
		RfD2Factory::n_factory = fff;
	}
	if(WRITE_FACTORY == nullptr)
	{
		//directWrite factory
		DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&www)
		);
		RfWriteFactory::n_factory = www;
	}
	
}

RfD2HWNDRender* RfD2Factory::CreateHWNDRender(void* hwnd)
{
	CreateFactory();
	auto winHWND = (HWND)hwnd;
	ID2D1HwndRenderTarget* render = nullptr;
	{
		RECT rc;
		::GetClientRect(winHWND, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);
		if (D2_FACTORY && winHWND)
			D2_FACTORY->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE),
				D2D1::HwndRenderTargetProperties(winHWND, size),
				&render
			);
		auto rfd2Render = new RfD2HWNDRender();
		rfd2Render->info.n_d2Render = render;
		return rfd2Render;

	}
	return nullptr;
}
