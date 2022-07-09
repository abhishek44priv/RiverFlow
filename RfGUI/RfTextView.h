#pragma once
#include "RfWidget.h"
class RfTextView :
    public RfWidget
{
public:
	RfTextView(Context ctx);
	RfTextView(Context ctx, const wchar_t* text);
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
public:
	const wchar_t* text = L"RfWidget";
	RfTextStyle textStyle;
};

