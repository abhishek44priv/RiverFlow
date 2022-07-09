#pragma once
#include "RfLayout.h"
enum 
{
	DIR_NORTH,
	DIR_SOUTH,
	DIR_EAST,
	DIR_WEST,
	DIR_CENTER,
};
class RfBorderLayout :
    public RfLayout
{
public:
	struct LayoutParams:public RfLayout::LayoutParams
	{
		int dir=DIR_NORTH;
	};
	RfBorderLayout(Context ctx);
	void AddView(RfView* view, LayoutParams lparam);
protected:
	virtual void OnMeasure(MeasureEvent e)override;
	virtual void OnLayout(LayoutEvent e)override;
	virtual void OnSize(SizeEvent e)override;
	virtual void OnDraw(DrawEvent e)override;
};

