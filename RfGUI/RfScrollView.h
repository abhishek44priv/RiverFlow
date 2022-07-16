#pragma once
#include "RfLayout.h"
/*
-hold only one child
*/
#include"RfWidget.h"
class RfScrollBar :public RfWidget
{
	float scrollPos = 0.0f;
	bool isMouseDown = false;
	RfPoint lastMove;
	float pageSize = 0.0f;
	RfRect thumbRect{};
	bool isGrab = false;
	float MaxScrollPos();
	void OnValueChange();
public:
	RfScrollBar(Context ctx);
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
class RfScrollView :
    public RfLayout
{
	void AddView(RfView* view, LayoutParams *lparam);
public:
	RfScrollView(Context ctx);
	void SetMainView(RfView* view);
protected:
	virtual void OnMeasure(MeasureEvent e)override;
	virtual void OnLayout(LayoutEvent e)override;
	virtual void OnMouseScroll(MouseEvent e)override;
	virtual void OnPageScroll(float ratio)override;

protected:
	int orientation = O_VERTICAL;
	RfScrollBar* mScrollbar = nullptr;
	

};

