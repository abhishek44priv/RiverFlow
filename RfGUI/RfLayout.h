#pragma once
#include"pch.h"
#include "RfView.h"
/*
    #event
    #measure
    #layout
    #paint
*/
class RfLayout :
    public RfView
{
public:
	struct LayoutParams
	{
		
	};
    RfLayout(Context ctx);
    void AddView(RfView* view,LayoutParams *lparam) ;
    void RemoveView(RfView* view);
    void RemoveViewAt(int index);
protected:
	virtual void OnMeasure(MeasureEvent e)override;
	virtual void OnLayout(LayoutEvent e)override;
	virtual void OnSize(SizeEvent e)override;
	virtual void OnDraw(DrawEvent e)override;
	virtual void OnDrawChilds(DrawEvent e);
	//mouse
	//if used return true
	virtual void OnMouseEnter()override;
	virtual void OnMouseExit()override;
	virtual void OnMouseUp(MouseEvent e)override;
	virtual void OnMouseDown(MouseEvent e)override;
	virtual void OnMouseMove(MouseEvent e)override;
	virtual void OnMouseScroll(MouseEvent e)override;
protected:
	std::vector<RfView*> childs;
	std::vector<LayoutParams*> lparams;
	friend class RfGUIWindow;
};

