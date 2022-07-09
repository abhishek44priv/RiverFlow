#include"pch.h"
#include "RfD2Window.h"
#include"RfD2Factory.h"
RfD2Window::RfD2Window(InitParams p)
{
	d2HWNDRender = RfD2Factory::CreateHWNDRender(GetHandle());
}

void RfD2Window::OnSize(RfSizeEvent& e)
{
	d2HWNDRender->Resize(e.width, e.height);
}

void RfD2Window::OnPaint()
{
	d2HWNDRender->Begin();
	{
		d2HWNDRender->Clear(RfColor(RfColor::BlanchedAlmond));
	}
	d2HWNDRender->End();
}

RfD2HWNDRender* RfD2Window::GetHWNDRender()
{
	return d2HWNDRender;
}
