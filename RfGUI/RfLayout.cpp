#include "pch.h"
#include "RfLayout.h"
#include"RfGUIWindow.h"
RfLayout::RfLayout(Context ctx)
	:RfView(ctx)
{
}

void RfLayout::AddView(RfView* view, LayoutParams lparam)
{
	view->parent = this;
	childs.push_back(view);
	lparams.push_back(new LayoutParams(lparam));
	//measure layout repaint
}


void RfLayout::RemoveView(RfView* view)
{
}

void RfLayout::RemoveViewAt(int index)
{
}

void RfLayout::OnMeasure(MeasureEvent e)
{
}

void RfLayout::OnLayout(LayoutEvent e)
{
}

void RfLayout::OnSize(SizeEvent e)
{
}

void RfLayout::OnDraw(DrawEvent e)
{
	RfView::OnDraw(e);
	OnDrawChilds(e);
}

void RfLayout::OnDrawChilds(DrawEvent e)
{
	auto off = e.render->GetOffset();
	auto lcDirRec = RfRect(e.clipRect.x-x,e.clipRect.y-y,e.clipRect.width,e.clipRect.height);
	for (auto c : childs)
	{
		if (lcDirRec.IntersectsWith(c->GetLocalRect()))
		{
			e.render->PlusOffest(c->x, c->y);
			c->OnDraw(e);
			e.render->PlusOffest(-c->x, -c->y);
		}
		
	}
}

void RfLayout::OnMouseEnter()
{
}

void RfLayout::OnMouseExit()
{

}

void RfLayout::OnMouseUp(MouseEvent e)
{
	RfPoint pt = { (float)e.x,(float)e.y };
	RfView::MouseEvent ee{ e.x,e.y };
	for (int i = childs.size() - 1; i >= 0; i--)
	{
		auto v = childs[i];
		ee.x = e.x -(int)v->x;
		ee.y = e.y - (int)v->y;
		bool res = v->GetLocalRect().Contains(pt);
		if (res)
		{
			v->OnMouseUp(ee);
		}
	}
}

void RfLayout::OnMouseDown(MouseEvent e)
{
	RfPoint pt = { (float)e.x,(float)e.y };
	RfView::MouseEvent ee{ e.x,e.y };
	for (int i = childs.size() - 1; i >= 0; i--)
	{
		auto v = childs[i];
		ee.x = e.x -(int)v->x;
		ee.y = e.y - (int)v->y;
		bool res = v->GetLocalRect().Contains(pt);
		if (res)
		{
			v->OnMouseDown(ee);
		}
	}
}

void RfLayout::OnMouseMove(MouseEvent e)
{
	RfView::MouseEvent ee{ e.x,e.y };
	auto& mouseEnterView = ctx.guiwindow->mouseEnterView;
	RfPoint pt = { (float)e.x,(float)e.y };
	
	for (int i = childs.size() - 1; i >= 0; i--)
	{
		auto v = childs[i];
		bool res = v->GetLocalRect().Contains(pt);
		ee.x = e.x - (int)v->x;
		ee.y = e.y - (int)v->y;
		if (res)
		{
			if (mouseEnterView != v)
			{
				mouseEnterView->OnMouseExit();
				mouseEnterView = v;
				mouseEnterView->OnMouseEnter();
			}
			else v->OnMouseMove(ee);
			return;
		}
	}
	if (mouseEnterView != this)
	{
		mouseEnterView->OnMouseExit();
		mouseEnterView = nullptr;
	}
}

void RfLayout::OnMouseScroll(MouseEvent e)
{
	RfPoint pt = { (float)e.x,(float)e.y };
	RfView::MouseEvent ee{ e.x,e.y };
	for (int i = childs.size() - 1; i >= 0; i--)
	{
		auto v = childs[i];
		ee.x = e.x -(int)v->x;
		ee.y = e.y - (int)v->y;
		bool res = v->GetLocalRect().Contains(pt);
		if (res)
		{
			v->OnMouseScroll(ee);
		}
	}
}
