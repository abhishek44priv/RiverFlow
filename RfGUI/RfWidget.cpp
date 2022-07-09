#include "pch.h"
#include "RfWidget.h"
#include<RfD2Factory.h>
RfWidget::RfWidget(Context ctx)
	:RfView(ctx)
{
	bgColor = RfColor::Aqua;
}

void RfWidget::OnMeasure(MeasureEvent e)
{
	
}

void RfWidget::OnDraw(DrawEvent e)
{
	RfView::OnDraw(e);
}

void RfWidget::OnMouseEnter()
{
	bgColor = bgColor.rgba & 0xffffffaa;
	Repaint();
}

void RfWidget::OnMouseExit()
{
	bgColor = bgColor.rgba | 0x000000ff;
	Repaint();

}

void RfWidget::OnMouseUp(MouseEvent e)
{
}

void RfWidget::OnMouseDown(MouseEvent e)
{
}

void RfWidget::OnMouseMove(MouseEvent e)
{
}

void RfWidget::OnMouseScroll(MouseEvent e)
{
}
