#include "pch.h"
#include "RfWinView.h"

RfWinView::RfWinView(Context ctx)
	:RfLayout(ctx)
{
	width = SIZE_FIXED;
	height = SIZE_FIXED;
}

void RfWinView::OnMeasure(MeasureEvent e)
{
	RfLayout::OnMeasure(e);
}

void RfWinView::OnDraw(DrawEvent e)
{
	RfLayout::OnDraw(e);

}

void RfWinView::OnMouseEnter()
{
	RfLayout::OnMouseEnter();

}

void RfWinView::OnMouseExit()
{
	RfLayout::OnMouseExit();

}

void RfWinView::OnMouseUp(MouseEvent e)
{
	RfLayout::OnMouseUp(e);
	ReleaseMouseCapture();
}

void RfWinView::OnMouseDown(MouseEvent e)
{
	RfLayout::OnMouseDown(e);
	lastMove = RfPoint(e.x, e.y);
	CaptureMouse();

}

void RfWinView::OnMouseMove(MouseEvent e)
{
	RfLayout::OnMouseMove(e);

	if (e.isMouseDown)
	{
		Repaint();

		auto offset = RfPoint(e.x, e.y) - lastMove;
		/*x += offset.x;
		y += offset.y;*/
		measuredWidth += offset.x;
		measuredHeight += offset.y;
		Repaint();
	}
	lastMove = RfPoint(e.x, e.y);
}

void RfWinView::OnMouseScroll(MouseEvent e)
{
	RfLayout::OnMouseScroll(e);

}
