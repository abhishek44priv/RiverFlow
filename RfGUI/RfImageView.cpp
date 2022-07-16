#include "pch.h"
#include "RfImageView.h"

RfImageView::RfImageView(Context ctx, std::string path)
	:RfWidget(ctx)
{
	image.Load(path);
	d2bitmap.Create(GetD2Render(),image.width,image.height,image.pixels);
}

RfImageView::RfImageView(Context ctx)
	:RfWidget(ctx)
{
	
}

void RfImageView::OnMeasure(MeasureEvent e)
{
	if (width == SIZE_WRAP )
	{
		if (image.IsPixels())
			measuredWidth = (float)image.width;
		else
			measuredWidth = 60.0f;

	}
	if (height == SIZE_WRAP)
	{
		if (image.IsPixels())
			measuredHeight = (float)image.height;
		else
			measuredHeight = 60.0f;
	}

}

void RfImageView::OnDraw(DrawEvent e)
{
	//drawImage
	if (image.IsPixels())
	{
		e.render->DrawBitmap(&d2bitmap, { 0,0,measuredWidth,measuredHeight });
	}
	else
	{
		auto center = RfPoint(MW() * 0.5f, MH() * 0.5f);
		e.render->FillEllipse(
			center,
			center.x,
			center.x,
			RfColor::Gray & 0xffffff55
		);

	}
}

void RfImageView::OnMouseEnter()
{
}

void RfImageView::OnMouseExit()
{
}

void RfImageView::OnMouseUp(MouseEvent e)
{
}

void RfImageView::OnMouseDown(MouseEvent e)
{
}

void RfImageView::OnMouseMove(MouseEvent e)
{
}

void RfImageView::OnMouseScroll(MouseEvent e)
{
}
