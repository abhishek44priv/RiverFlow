#pragma once
#include "RfWidget.h"
class RfSwitch :
    public RfWidget
{
public:
	bool isOn = true;
	RfSwitch(Context ctx);
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

