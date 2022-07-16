#include "pch.h"
#include "RfCanvasView.h"

RfCanvasView::RfCanvasView(Context ctx)
	:RfWidget(ctx)
{
	width = SIZE_FIXED;
	height = SIZE_FIXED;
	measuredWidth = 300.0f;
	measuredHeight = 300.0f;
}

void RfCanvasView::OnMeasure(MeasureEvent e)
{
}

void RfCanvasView::OnDraw(DrawEvent e)
{
	e.render->DrawEllipse(
		{100,100},50,50,RfColor::Aqua
	);
	e.render->DrawRect({ 0,0,MW(),MH() },RfColor::Black);
}

void RfCanvasView::OnMouseEnter()
{
}

void RfCanvasView::OnMouseExit()
{
}

void RfCanvasView::OnMouseUp(MouseEvent e)
{
}

void RfCanvasView::OnMouseDown(MouseEvent e)
{
}

void RfCanvasView::OnMouseMove(MouseEvent e)
{
}

void RfCanvasView::OnMouseScroll(MouseEvent e)
{
}
