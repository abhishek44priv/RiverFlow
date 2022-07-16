#include "pch.h"
#include "RfTextView.h"
#include<RfRandom.h>
#include<thread>
RfTextView::RfTextView(Context ctx)
	:RfWidget(ctx)
{
	bgColor = RfColor::White;
}

RfTextView::RfTextView(Context ctx, std::wstring text)
	:RfWidget(ctx)
{
	this->text = text;
	pad = { 4,4 };
	margin = { 1,1 };
	width = SIZE_WRAP;
	height= SIZE_WRAP;
	bgColor = RfColor::CornflowerBlue;
	
}

void RfTextView::OnMeasure(MeasureEvent e)
{
	if ((width == SIZE_WRAP || height == SIZE_WRAP) && isMeasureNeeded) {
		auto msize = RfTextLayout(this->text.c_str(), textStyle).GetSize();
		if (width == SIZE_WRAP) {
			measuredWidth = msize.width + pad.l + pad.r;
		}
		if (height == SIZE_WRAP) {
			measuredHeight = msize.height + pad.t + pad.b;

		}
		isMeasureNeeded = false;
	}

}

void RfTextView::OnDraw(DrawEvent e)
{
	//std::wcout << "painted " << text << "\n";
	//RfWidget::OnDraw(e);
	e.render->DrawString(
		text.c_str(),
		{0,0,GetMeasuredWidth(),GetMeasuredHeight()},
		textStyle,textColor);

}

void RfTextView::OnMouseEnter()
{
	RfWidget::OnMouseEnter();
}

void RfTextView::OnMouseExit()
{

	RfWidget::OnMouseExit();

}

void RfTextView::OnMouseUp(MouseEvent e)
{
	RfWidget::OnMouseUp(e);

}

void RfTextView::OnMouseDown(MouseEvent e)
{
	RfWidget::OnMouseDown(e);

}

void RfTextView::OnMouseMove(MouseEvent e)
{
}

void RfTextView::OnMouseScroll(MouseEvent e)
{
}
