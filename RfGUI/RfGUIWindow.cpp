#include"pch.h"

#include "RfGUIWindow.h"
#include<RfD2Factory.h>
//view
#include"RfLayout.h"
void RfGUIWindow::OnPaint(int l, int t, int r, int b)
{
    hwndRender->Begin();
    RfPaintParams e;
    e.render = hwndRender;
    e.dirtyRect.SetLTRB((float)l, (float)t, (float)r, (float)b);
	e.render->FillRect(e.dirtyRect, 0xaaaaaaff);
    OnPaint(e);
    hwndRender->End();
}

RfGUIWindow::RfGUIWindow(InitParams p)
{
    hwndRender = RfD2Factory::CreateHWNDRender(GetHandle());;
}

void RfGUIWindow::OnSize(RfSizeEvent& e)
{
    hwndRender->Resize(e.width, e.height);
    Measure();
    Layout();
}

void RfGUIWindow::OnPaint(RfPaintParams e)
{
	for (auto vw : childs)
	{
		auto clip = vw->GetClipRect();
		//dirty check
		if (e.dirtyRect.IntersectsWith({ vw->x,vw->y,clip.width,clip.height }))
		{
			if (clip.IntersectsWith({ 0,0,(float)GetWidth(),(float)GetHeight() }))
			{
				RfRect drect;
				RfRect::Intersect(drect, e.dirtyRect, vw->GetLocalRect());
				e.render->PushClipRect(drect);
				e.render->PlusOffest(vw->x, vw->y);
				vw->OnDraw({ e.render,e.dirtyRect });
				e.render->PlusOffest(-vw->x, -vw->y);
				e.render->PopClipRect();
			}
		}
		/*e.render->PlusOffest(vw->x, vw->y);
		vw->OnDraw({ e.render,e.dirtyRect });
		e.render->PlusOffest(-vw->x, -vw->y);*/
	}
}

void RfGUIWindow::OnMouseMove(RfMouseEvent& e)
{
	RfView::MouseEvent ee{ e.x,e.y };
	ee.isMouseDown = IsMouseDown();
	if (mouseCaptureView)
	{
		auto sr = mouseCaptureView->GetScreenRect();
		ee.x = e.x - (int)sr.x;
		ee.y = e.y - (int)sr.y;
		mouseCaptureView->OnMouseMove(ee);
		return;
	}
	RfPoint pt = { (float)e.x,(float)e.y };
	for (int i = childs.size() - 1; i >= 0; i--)
	{
		auto v = childs[i];
		ee.x = e.x - (int)v->x;
		ee.y = e.y - (int)v->y;
		bool res = v->GetLocalRect().Contains(pt);
		if (res) {
			if (mouseEnterView == nullptr)
			{
				mouseEnterView = v;
				mouseEnterView->OnMouseEnter();
			}
			else v->OnMouseMove(ee);
			return;
		}
	}
	if (mouseEnterView)
	{
		mouseEnterView->OnMouseExit();
		mouseEnterView = nullptr;

	}
}

void RfGUIWindow::OnMouseEnter()
{
   
}

void RfGUIWindow::OnMouseExit()
{
	if (mouseEnterView)
	{
		mouseEnterView->OnMouseExit();
		mouseEnterView = nullptr;
	}
}

void RfGUIWindow::OnMouseUp(RfMouseEvent& e)
{
	if (mouseCaptureView)
	{
		RfView::MouseEvent ee{ e.x,e.y };

		auto sr = mouseCaptureView->GetScreenRect();
		ee.x = e.x - (int)sr.x;
		ee.y = e.y - (int)sr.y;
		mouseCaptureView->OnMouseUp(ee);
		return;
	}
	RfPoint pt = { (float)e.x,(float)e.y };
	RfView::MouseEvent ee{ e.x,e.y };
	for (int i = childs.size() - 1; i >= 0; i--)
	{
		auto v = childs[i];
		ee.x = e.x - (int)v->x;
		ee.y = e.y - (int)v->y;
		bool res = v->GetLocalRect().Contains(pt);
		if (res)
		{
			v->OnMouseUp(ee);
			return;

		}
	}
}

void RfGUIWindow::OnMouseDown(RfMouseEvent& e)
{
	RfPoint pt = { (float)e.x,(float)e.y };
	RfView::MouseEvent ee{ e.x,e.y };
	for (int i = childs.size() - 1; i >= 0; i--)
	{
		auto v = childs[i];
		ee.x = e.x - (int)v->x;
		ee.y = e.y - (int)v->y;
		bool res = v->GetLocalRect().Contains(pt);
		if (res)
		{
			v->OnMouseDown(ee);
			return;
		}
	}
}

void RfGUIWindow::OnMouseWheel(RfMouseEvent& e)
{
	RfPoint pt = { (float)e.x,(float)e.y };
	RfView::MouseEvent ee{ e.x,e.y };
	for (int i = childs.size() - 1; i >= 0; i--)
	{
		auto v = childs[i];
		ee.x = e.x - (int)v->x;
		ee.y = e.y - (int)v->y;
		if (e.delta == e.SCROLL_DOWN) {
			ee.scollDir = -1;
		}
		if (e.delta == e.SCROLL_UP)
		{
			ee.scollDir = 1;
		}
		bool res = v->GetLocalRect().Contains(pt);
		if (res)
		{
			v->OnMouseScroll(ee);
		}
	}
}

void RfGUIWindow::OnKeyDown(RfKeyEvent& e)
{
}

void RfGUIWindow::OnKeyUp(RfKeyEvent& e)
{
}

RfD2HWNDRender* RfGUIWindow::GetHWNDRender()
{
    return hwndRender;
}

void RfGUIWindow::SetMainLayout(RfLayout* layout)
{
	childs.insert(childs.begin() + 0,layout);
	Measure();
	Layout();
	Repaint({});
}

void RfGUIWindow::AddLayout(RfLayout* layout)
{
    childs.push_back(layout);
	Measure();
	Layout();
	Repaint({});

}

void RfGUIWindow::RemoveLayout(RfLayout* layout)
{
}

void RfGUIWindow::Repaint(RfRect dirty)
{
	if (dirty.IsEmptyArea()) {
		dirty.SetXYWH(0, 0, (float)GetWidth(), (float)GetHeight());
	}
	RfBaseWindow::Repaint(
		(int)dirty.x,(int)dirty.y,
		(int)dirty.GetRight(),(int)dirty.GetBottom()
	);
}

void RfGUIWindow::Measure()
{
    OnMeasure();
}

void RfGUIWindow::Layout()
{
    OnLayout();
}

void RfGUIWindow::OnMeasure()
{

	for (size_t i = 0; i < childs.size(); i++)
	{
		auto v = childs[i];
		RfView::MeasureEvent e{};
		if (v->width == SIZE_MATCH)
			v->measuredWidth = (float)GetWidth();

		if (v->height == SIZE_MATCH)
			v->measuredHeight = (float)GetHeight();

		v->OnMeasure(e);
	}
}

void RfGUIWindow::OnLayout()
{
	for (size_t i = 0; i < childs.size(); i++)
    {
		auto v = childs[i];
		/*if (i == 0)
		{
			v->x = v->margin.l;
			v->y = v->margin.t;
		}*/
			
        v->OnLayout({});
    }
}


