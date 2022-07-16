#pragma once
#include "RfLayout.h"

enum {
	ALIGN_LEFT,ALIGN_CENTER,ALIGN_RIGHT,
	ALIGN_TOP,ALIGN_BOTTOM
};
class RfLinearLayout :
    public RfLayout
{
	void MeasureH(MeasureEvent e);
	void MeasureV(MeasureEvent e);
	void LayoutV(LayoutEvent e);
	void LayoutH(LayoutEvent e);
public:
	struct LayoutParams:
		public RfLayout::LayoutParams
	{
		int align=ALIGN_CENTER;
		LayoutParams(int align= ALIGN_CENTER) :align(align) {}
	};
	RfLinearLayout(Context ctx, int orientation = O_VERTICAL);
	void AddView(RfView* view, LayoutParams *lparam);
protected:
	virtual void OnMeasure(MeasureEvent e)override;
	virtual void OnLayout(LayoutEvent e)override;
	virtual void OnMouseScroll(MouseEvent e)override;
	virtual void OnPageScroll(float ratio)override;

protected:
	int orientation = O_VERTICAL;
	float childsHeight = 0.0f;

};

