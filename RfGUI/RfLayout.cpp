#include "pch.h"
#include "RfLayout.h"
#include"RfGUIWindow.h"
#include"RfWidget.h"
RfLayout::RfLayout(Context ctx)
	:RfView(ctx)
{
	bgColor = RfRandom::RangeInt(RfColor::Red, RfColor::Blue) | 0x000000ff;
	d_name = "layout";
}

void RfLayout::AddView(RfView* view, LayoutParams *lparam)
{
	view->parent = this;
	childs.push_back(view);
	view->lparam = lparam;
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
	for (auto c : childs) {
		c->Measure(e);
	}
}

void RfLayout::OnLayout(LayoutEvent e)
{
	for (auto c : childs) {
		c->Layout(e);
	}
}

void RfLayout::OnSize(SizeEvent e)
{
}

void RfLayout::OnDraw(DrawEvent e)
{
	e.render->PushClipRect({ 0,0,measuredWidth,measuredHeight });
	RfView::OnDraw(e);
	OnDrawChilds(e);
	//border
	//e.render->DrawRect({ 0,0,measuredWidth,measuredHeight }, borderColor,1.5f);
	e.render->PopClipRect();
}

void RfLayout::OnDrawChilds(DrawEvent e)
{
	auto off = e.render->GetOffset();
	auto lcDirRec = RfRect(e.clipRect.x-off.x,e.clipRect.y-off.y,e.clipRect.width,e.clipRect.height);
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
	borderColor = borderColor.rgba & 0xffffff88;
	//Repaint();
}

void RfLayout::OnMouseExit()
{
	borderColor = borderColor.rgba | 0x000000ff;
	//Repaint();
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
		if (res)
		{
			ee.x = e.x - (int)v->x;
			ee.y = e.y - (int)v->y;
			
			if (mouseEnterView == this)
			{
				mouseEnterView->OnMouseExit();
				mouseEnterView = v;
				v->OnMouseEnter();
			}
			else
			{
				auto widget = dynamic_cast<RfWidget*>(v);
				if (widget)
				{
					if (mouseEnterView != v)
					{
						mouseEnterView->OnMouseExit();
						mouseEnterView = v;
						v->OnMouseEnter();
						return;
					}

				}
				v->OnMouseMove(ee);
			}
			return;
		}
	}
	if (mouseEnterView != this)
	{
		mouseEnterView->OnMouseExit();
		mouseEnterView = this;
		OnMouseEnter();
	}
}

void RfLayout::OnMouseScroll(MouseEvent e)
{
	RfPoint pt = { (float)e.x,(float)e.y };
	RfView::MouseEvent ee = e;
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
