#include "pch.h"
#include "RfTextView.h"

RfTextView::RfTextView(Context ctx)
	:RfWidget(ctx)
{
	bgColor = RfColor::Red;
}

RfTextView::RfTextView(Context ctx, const wchar_t* text)
	:RfWidget(ctx)
{
	this->text = text;
	pad = { 5,5 };
	width = SIZE_WRAP;
	height= SIZE_WRAP;
}

void RfTextView::OnMeasure(MeasureEvent e)
{
	if (width == SIZE_WRAP || height == SIZE_WRAP) {
		auto msize = RfTextLayout(this->text, textStyle).GetSize();
		if (width == SIZE_WRAP) {
			measuredWidth = msize.width + pad.l + pad.r;
		}
		if (height == SIZE_WRAP) {
			measuredHeight = msize.height + pad.t + pad.b;

		}
	}
	if ((width == SIZE_MATCH || height == SIZE_MATCH) && parent) {
		if (width == SIZE_MATCH) {
			measuredWidth = parent->GetMeasuredWidth() - pad.l - pad.r;
		}
		if (height == SIZE_MATCH) {
			measuredHeight = parent->GetMeasuredHeight() - pad.t - pad.b;
		}
	}

}

void RfTextView::OnDraw(DrawEvent e)
{
	RfWidget::OnDraw(e);
	e.render->DrawString(text, { 0,0,GetMeasuredWidth(),GetMeasuredHeight() }, textStyle);
	std::cout << "RfTextView::OnDraw \n";
}

void RfTextView::OnMouseEnter()
{
	std::cout << "RfTextView::OnMouseEnter \n";

	RfWidget::OnMouseEnter();
}

void RfTextView::OnMouseExit()
{
	RfWidget::OnMouseExit();

}

void RfTextView::OnMouseUp(MouseEvent e)
{
}

void RfTextView::OnMouseDown(MouseEvent e)
{
}

void RfTextView::OnMouseMove(MouseEvent e)
{
}

void RfTextView::OnMouseScroll(MouseEvent e)
{
}
