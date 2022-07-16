#include "pch.h"
#include "RfLinearLayout.h"

void RfLinearLayout::MeasureH(MeasureEvent e)
{
	float wrapHeight =0;
	float wrapWidth = pad.l + pad.r;
	float availableWidth = measuredWidth - pad.l - pad.r;
	float pageWidth_ = pad.l + pad.r;
	for (auto c : childs) {
		//width
		if (height != SIZE_WRAP)
		{
			//child
			if (c->height == SIZE_MATCH) {
				c->measuredHeight = measuredHeight -
					(pad.t + pad.b + c->margin.t + c->margin.b);
			}
		}
		//height
		if (width != SIZE_WRAP)
		{
			//child
			if (c->width == SIZE_MATCH) {
				c->measuredWidth = availableWidth -
					(c->margin.t + c->margin.b);
			}
		}
		c->Measure(e);
		availableWidth -= c->measuredWidth + c->margin.l + c->margin.r;
		/*-------------------------------------------------*/
		//wrap 
		wrapWidth += c->margin.l + c->measuredWidth + c->margin.r;

		float childH = c->margin.t + c->measuredHeight + c->margin.b;
		if (wrapHeight < childH)
			wrapHeight = childH;

		pageWidth_ += c->measuredWidth + c->margin.l + c->margin.r;
	}
	if (height == SIZE_WRAP)
		measuredHeight = wrapHeight;

	if (width == SIZE_WRAP)
		measuredWidth = wrapWidth ;

	//sum of all child height +pad+ margin
	pageWidth = pageWidth_ - measuredWidth;
}

void RfLinearLayout::MeasureV(MeasureEvent e)
{
	float wrapHeight = pad.t+pad.b;
	float wrapWidth = 0;
	float availableHeight = measuredHeight-pad.t-pad.b;
	float pageHeight_ = pad.t + pad.b;
	for (auto c : childs) {
		//width
		if (width != SIZE_WRAP)
		{
			//child
			if (c->width == SIZE_MATCH) {
				c->measuredWidth = measuredWidth -
					(pad.l + pad.r + c->margin.l + c->margin.r);
			}
		}
		//height
		if (height != SIZE_WRAP)
		{
			//child
			if (c->height == SIZE_MATCH) {
				c->measuredHeight = availableHeight -
					( c->margin.l + c->margin.r);
			}
		}
		c->Measure(e);
		availableHeight -= c->measuredHeight + c->margin.t + c->margin.b;
		/*-------------------------------------------------*/
		//wrap 
		wrapHeight += c->margin.t+c->measuredHeight+c->margin.b;
		
		float childW = c->margin.l + c->measuredWidth + c->margin.r;
		if (wrapWidth < childW)
			wrapWidth = childW;

		pageHeight_ += c->measuredHeight + c->margin.t + c->margin.b;
	}
	if (height == SIZE_WRAP)
		measuredHeight = wrapHeight;

	if (width == SIZE_WRAP)
		measuredWidth = wrapWidth+pad.l+pad.r;

	//sum of all child height +pad+ margin
	pageHeight = pageHeight_-measuredHeight;
}

void RfLinearLayout::LayoutV(LayoutEvent e)
{
	float nextY = pad.t+scrollY;
	for (size_t i = 0; i < childs.size(); i++)
	{
		auto child = childs[i];
		auto lparam = (RfLinearLayout::LayoutParams*)child->lparam;
		auto cwidth = child->GetMeasuredWidth();
		auto cheight = child->GetMeasuredHeight();
		nextY += child->margin.t;
		//set
		{
			//ALIGN
			{
				if (lparam->align == ALIGN_LEFT)
					child->x = pad.l + child->margin.l;
				else if (lparam->align == ALIGN_RIGHT)
					child->x = measuredWidth - (child->measuredWidth + pad.r + child->margin.r);
				else if (lparam->align == ALIGN_CENTER)
					child->x = measuredWidth * 0.5f - child->measuredWidth * 0.5f;
			}
			child->y = nextY;
			child->Layout(e);
		}
		nextY += cheight + child->margin.b;

	}
}

void RfLinearLayout::LayoutH(LayoutEvent e)
{
	float nextW = pad.l ;
	for (size_t i = 0; i < childs.size(); i++)
	{
		auto child = childs[i];
		auto lparam = (RfLinearLayout::LayoutParams*)child->lparam;
		auto cwidth = child->GetMeasuredWidth();
		auto cheight = child->GetMeasuredHeight();
		nextW += child->margin.l;
		//set
		{
			//ALIGN
			{
				if (lparam->align == ALIGN_TOP)
					child->y = pad.t + child->margin.t;
				else if (lparam->align == ALIGN_BOTTOM)
					child->y = measuredHeight - (child->measuredHeight + pad.b + child->margin.b);
				else if (lparam->align == ALIGN_CENTER)
					child->y = measuredHeight * 0.5f - child->measuredHeight * 0.5f;
			}
			child->x = nextW;
			child->Layout(e);
		}
		nextW += cwidth + child->margin.r;

	}
}

RfLinearLayout::RfLinearLayout(Context ctx, int orientation)
	:RfLayout(ctx)
{
	this->orientation = orientation;
	pad = { 3,3 };
	margin = { 3,3 };
	bgColor = RfColor::White;
}

void RfLinearLayout::AddView(RfView* view, LayoutParams *lparam)
{
	RfLayout::AddView(view, lparam);
}

void RfLinearLayout::OnMeasure(MeasureEvent e)
{


	if (orientation == O_HORIZONTAL)
	{
		MeasureH(e);
	}
	else
	{
		MeasureV(e);
	}
}

void RfLinearLayout::OnLayout(LayoutEvent e)
{

	if (orientation == O_HORIZONTAL)
	{
		LayoutH(e);
	}
	else
	{
		LayoutV(e);
	}
}

void RfLinearLayout::OnMouseScroll(MouseEvent e)
{
	RfLayout::OnMouseScroll(e);

	/*if (e.scollDir>0) {
		scrollY += 10;
	}else{
		scrollY -= 10;
	}
	Layout();
	Repaint();*/
}

void RfLinearLayout::OnPageScroll(float ratio)
{
	scrollY = -(pageHeight) * ratio;
	Layout();
	Repaint();
}
