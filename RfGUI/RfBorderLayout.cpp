#include "pch.h"
#include "RfBorderLayout.h"

RfBorderLayout::RfBorderLayout(Context ctx)
	:RfLayout(ctx)
{
	bgColor = RfColor::Chocolate;
}

void RfBorderLayout::AddView(RfView* view, LayoutParams lparam)
{
	RfLayout::AddView(view, lparam);
}

void RfBorderLayout::OnMeasure(MeasureEvent e)
{
	std::cout << "RfBorderLayout::OnMeasure \n";
	for (auto c : childs) 
	{
		c->Measure(e);
	}
}

void RfBorderLayout::OnLayout(LayoutEvent e)
{
	RfLTRB space;
	for (size_t i = 0; i < childs.size(); i++)
	{
		auto child = childs[i];
		auto lparam = (RfBorderLayout*)lparams[i];
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


