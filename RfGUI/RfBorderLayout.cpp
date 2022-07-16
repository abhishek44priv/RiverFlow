#include "pch.h"
#include "RfBorderLayout.h"

RfBorderLayout::RfBorderLayout(Context ctx)
	:RfLayout(ctx)
{
	bgColor = RfColor::Chocolate;
}

void RfBorderLayout::AddView(RfView* view, LayoutParams* lparam)
{
	RfLayout::AddView(view, lparam);
}

void RfBorderLayout::OnMeasure(MeasureEvent e)
{
	std::cout << "RfBorderLayout::OnMeasure \n";
	//width and height must not WRAP
	for (auto c : childs) 
	{
		if (width == SIZE_MATCH || width == SIZE_FIXED) {
			if (c->width == SIZE_MATCH) {
				c->measuredWidth = measuredWidth - (pad.l + pad.r + c->margin.l + c->margin.r);
			}
		}
		
		if (height == SIZE_MATCH || height == SIZE_FIXED) {
			if (c->height == SIZE_MATCH) {
				c->measuredHeight = measuredHeight - (pad.t + pad.b + c->margin.t + c->margin.b);
			}
		}
		c->Measure(e);
	}
}

void RfBorderLayout::OnLayout(LayoutEvent e)
{
	RfLTRB space;
	for (size_t i = 0; i < childs.size(); i++)
	{
		auto child = childs[i];
		auto cwidth = child->GetMeasuredWidth();
		auto cheight = child->GetMeasuredHeight();
		
		//child->x = pad.l + child->margin.l;
	}
}

void RfBorderLayout::OnSize(SizeEvent e)
{
}

void RfBorderLayout::OnDraw(DrawEvent e)
{
	std::cout << "RfBorderLayout::OnDraw \n";
	RfLayout::OnDraw(e);

}


