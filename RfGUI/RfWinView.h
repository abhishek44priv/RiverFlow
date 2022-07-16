#pragma once
#include "RfLayout.h"
class RfWinView :
    public RfLayout
{
	RfPoint lastMove;
public:
	RfWinView(Context ctx);
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

