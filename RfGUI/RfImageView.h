#pragma once
#include "RfWidget.h"
#include<RfD2Bitmap.h>
#include<RfImage.h>
class RfImageView :
    public RfWidget
{
protected:
	RfImage image{};
	RfD2Bitmap d2bitmap{};
public:
	RfImageView(Context ctx, std::string path);
	RfImageView(Context ctx);
protected:
	virtual void OnMeasure(MeasureEvent e);
	virtual void OnDraw(DrawEvent e);
	//mouse
	virtual void OnMouseEnter();
	virtual void OnMouseExit();
	virtual void OnMouseUp(MouseEvent e);
	virtual void OnMouseDown(MouseEvent e);
	virtual void OnMouseMove(MouseEvent e);
	virtual void OnMouseScroll(MouseEvent e);
};

