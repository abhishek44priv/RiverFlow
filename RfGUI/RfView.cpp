#include"pch.h"
#include"RfGUIWindow.h"
#include "RfView.h"

RfView::RfView(Context ctx)
{
	this->ctx = ctx;
}

RfView::~RfView()
{
}

void RfView::SetWidth(int width)
{
	if(width==SIZE_FIXED)
	{
		this->width = SIZE_FIXED;
		this->measuredWidth = (float)width;
	}
	else
	{
		this->width = width;
	}
	//update
}

void RfView::SetHeight(int height)
{
	if(height==SIZE_FIXED)
	{
		this->height = SIZE_FIXED;
		this->measuredHeight = (float)height;
	}
	else
	{
		this->height = height;
	}
	//update
}

float RfView::GetMeasuredWidth()
{
	return measuredWidth;
}

float RfView::GetMeasuredHeight()
{
	return measuredHeight;
}

void RfView::SetX(int x, bool update)
{
	this->x = (float)x;
}

void RfView::SetY(int y, bool update)
{
	this->y = (float)y;
}

void RfView::Measure(MeasureEvent e)
{
	OnMeasure(e);
}

void RfView::Layout(LayoutEvent e)
{
	OnLayout(e);
}





void RfView::Repaint()
{
	auto srn = GetScreenRect();
	auto clip = GetClipRect();
	this->ctx.guiwindow->Repaint({ srn.x+(x<0?-x:0), srn.y+(y < 0 ? -y : 0), clip.width, clip.height});
}

RfRect RfView::GetLocalRect()
{
	return RfRect
	(
		this->x,this->y,
		this->measuredWidth,this->measuredHeight
	);

}

RfRect RfView::GetClipRect()
{
	if (this->parent)
	{
		RfRect out;
		auto p = this->parent->GetClipRect();
		RfRect::Intersect(out, { 0,0,p.width,p.height }, GetLocalRect());
		return out;
	}
	RfRect win(0, 0,(float)ctx.guiwindow->GetWidth(), (float)ctx.guiwindow->GetHeight());
	RfRect out;
	RfRect::Intersect(out, win, GetLocalRect());
	return out;
}

RfRect RfView::GetScreenRect()
{
	RfPoint xy(this->x, this->y);
	RfView* v = this->parent;
	while (v)
	{
		xy.x += v->x;
		xy.y += v->y;
		v = v->parent;
	}
	return RfRect(xy.x, xy.y, this->measuredWidth, this->measuredHeight);
}

void RfView::SetParent(RfView* p)
{
	this->parent = p;
}

void RfView::OnVisibility(bool isVisible)
{
}

void RfView::OnMeasure(MeasureEvent e)
{
}

void RfView::OnLayout(LayoutEvent e)
{
}

void RfView::OnSize(SizeEvent e)
{
}

void RfView::OnDraw(DrawEvent e)
{
	e.render->FillRect(
		{ 0,0,this->measuredWidth,this->measuredHeight },
		this->bgColor
	);

}

void RfView::OnMouseEnter()
{
}

void RfView::OnMouseExit()
{
}

void RfView::OnMouseUp(MouseEvent e)
{
}

void RfView::OnMouseDown(MouseEvent e)
{
	GetClipRect().Print("clip ");
	GetScreenRect().Print("screen ");
}

void RfView::OnMouseMove(MouseEvent e)
{

}

void RfView::OnMouseScroll(MouseEvent e)
{
}
