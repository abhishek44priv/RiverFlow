#include "pch.h"
#include "RfWidget.h"
#include<RfD2Factory.h>
RfWidget::RfWidget(Context ctx)
	:RfView(ctx)
{
	bgColor = RfColor::Aqua;
	width = SIZE_WRAP;
	height = SIZE_WRAP;
}

void RfWidget::OnMeasure(MeasureEvent e)
{
	
}

void RfWidget::OnDraw(DrawEvent e)
{
	RfView::OnDraw(e);
	//e.render->DrawRect({ 0,0,measuredWidth,measuredHeight }, borderColor, 1.0f);

}

void RfWidget::OnMouseEnter()
{
	bgColor = bgColor.rgba & 0xffffffaa;
	RfView::OnMouseEnter();
}

void RfWidget::OnMouseExit()
{
	bgColor = bgColor.rgba | 0x000000ff;
	RfView::OnMouseExit();
}

void RfWidget::OnMouseUp(MouseEvent e)
{
	bgColor = bgColor.rgba | 0x000000aa;
	Repaint();

}

void RfWidget::OnMouseDown(MouseEvent e)
{
	bgColor = bgColor.rgba & 0xffffff99;
	Repaint();
}

void RfWidget::OnMouseMove(MouseEvent e)
{
}

void RfWidget::OnMouseScroll(MouseEvent e)
{
}
