#include "pch.h"
#include "RfScrollView.h"

void RfScrollView::AddView(RfView* view, LayoutParams *lparam)
{
	RfLayout::AddView(view, lparam);
}

RfScrollView::RfScrollView(Context ctx)
	:RfLayout(ctx)
{
	mScrollbar = new RfScrollBar(ctx);
	AddView(mScrollbar, {});
	width = SIZE_MATCH;
	height = SIZE_MATCH;
}

void RfScrollView::SetMainView(RfView* view)
{

	AddView(view, {});
}

void RfScrollView::OnMeasure(MeasureEvent e)
{
	//resize height of scrollbar
	auto scrollbar = childs[0];
	scrollbar->measuredHeight = measuredHeight;
	scrollbar->Measure();
	//mainview
	{
		if (childs.size() > 1)
		{
			auto v = childs[1];
			v->measuredWidth = measuredWidth - scrollbar->measuredWidth;
			v->measuredHeight = measuredHeight;
			v->Measure({});
		}
	}
}

void RfScrollView::OnLayout(LayoutEvent e)
{
	//position scrollbar
	auto scrollbar = childs[0];
	scrollbar->x = measuredWidth - scrollbar->measuredWidth;
	//mainview
	{
		if (childs.size() > 1)
		{
			auto v = childs[1];
			v->x = 0;
			v->y = 0;
			v->Layout({});
		}
	}

}

void RfScrollView::OnMouseScroll(MouseEvent e)
{
	RfLayout::OnMouseScroll(e);
}
void RfScrollView::OnPageScroll(float ratio)
{
	if (childs.size() > 1)
	{
		auto v = childs[1];
		v->OnPageScroll(ratio);
	}
}
/*--------------------RfScrollBar-----------------------------*/

float RfScrollBar::MaxScrollPos()
{
	return measuredHeight - thumbRect.height;
}
void RfScrollBar::OnValueChange()
{
	if (parent)
		parent->OnPageScroll(scrollPos);
}
RfScrollBar::RfScrollBar(Context ctx)
	:RfWidget(ctx)
{
	width = SIZE_FIXED;
	height = SIZE_MATCH;
	measuredWidth = 20;
	bgColor = RfColor::AntiqueWhite;
}

void RfScrollBar::OnMeasure(MeasureEvent e)
{
	thumbRect.width = measuredWidth - 4;
	thumbRect.x = 2;
	thumbRect.height = 100;
	print("ratio {}\n", scrollPos);
	OnValueChange();
}

void RfScrollBar::OnDraw(DrawEvent e)
{
	RfWidget::OnDraw(e);
	//draw thumb
	RfColor thumbColor = RfColor::Gray;
	thumbRect.y = scrollPos * MaxScrollPos();
	e.render->FillRect(thumbRect, thumbColor);
}

void RfScrollBar::OnMouseEnter()
{
	bgColor = bgColor.rgba & 0xffffffdd;
	Repaint();
}

void RfScrollBar::OnMouseExit()
{
	bgColor = bgColor.rgba | 0x000000ff;
	Repaint();

}

void RfScrollBar::OnMouseUp(MouseEvent e)
{
	isGrab = false;
	ReleaseMouseCapture();
}

void RfScrollBar::OnMouseDown(MouseEvent e)
{
	if (thumbRect.Contains(RfPoint(e.x, e.y)))
	{
		isGrab = true;
	}
	CaptureMouse();
}

void RfScrollBar::OnMouseMove(MouseEvent e)
{
	if(e.isMouseDown && isGrab){
		auto offset =( e.y - lastMove.y)/MaxScrollPos();
		scrollPos += offset;
		if (scrollPos < 0)
			scrollPos = 0.f;
		if (scrollPos >1)
			scrollPos = 1.f;
		OnValueChange();
		Repaint();
	}
	lastMove.y = e.y;

}

void RfScrollBar::OnMouseScroll(MouseEvent e)
{

	scrollPos += 0.01*e.scollDir;
	print("scrollpos {}\n", scrollPos);
	if (scrollPos < 0)
		scrollPos = 0.f;
	if (scrollPos > 1)
		scrollPos = 1.f;
	OnValueChange();
	Repaint();
}
