#pragma once
#include "RfWidget.h"
class RfTextView :
    public RfWidget
{
public:
	RfTextView(Context ctx);
	RfTextView(Context ctx, std::wstring text);
protected:
	virtual void OnMeasure(MeasureEvent e)override;
	virtual void OnDraw(DrawEvent e)override;
	//mouse
	virtual void OnMouseEnter()override;
	virtual void OnMouseExit()override;
	virtual void OnMouseUp(MouseEvent e)override;
	virtual void OnMouseDown(MouseEvent e)override;
	virtual void OnMouseMove(MouseEvent e)override;
	virtual void OnMouseScroll(MouseEvent e)override;
public:
	std::wstring text = L"RfWidget";
	RfTextStyle textStyle;
	bool isMeasureNeeded = true;
	RfColor textColor = RfColor::Black;
};

