#pragma once
#include<RfColor.h>
#include<RfD2Render.h>

class RfGUIWindow;
struct RfLTRB
{
	float l= 0.0f, t= 0.0f, r= 0.0f, b=0.0f;
	RfLTRB(float all=0.0f)
	:l(all), t(all), r(all), b(all) {}
	RfLTRB(float a,float b)
		:l(a), t(b), r(a), b(b) {}
	RfLTRB(float l, float t, float r, float b)
		: l(l), t(t), r(r), b(b) {}
};
enum
{
	SIZE_MATCH = -10, SIZE_WRAP, SIZE_FIXED
};
class RfView
{
	
public:
	
	struct MeasureEvent { int width, height; };
	struct LayoutEvent {};
	struct SizeEvent {};
	struct DrawEvent {
		RfD2Render* render = nullptr;
		RfRect clipRect{};
	};
	struct MouseEvent {
		int x=0, y=0;
		bool isDown = false;
	};
	struct KeyEvent {};
	struct Context
	{
		RfGUIWindow* guiwindow = nullptr;
	};
public:
	float x = 0, y = 0;
	int width=0,height=0;
	float measuredWidth = 0, measuredHeight = 0;
	RfColor bgColor = RfColor::Aqua;
	Context ctx;
	RfView* parent = nullptr;
	RfLTRB pad,margin;
public:
	RfView(Context ctx);
	~RfView();
	void SetWidth(int width);
	void SetHeight(int height);
	float GetMeasuredWidth();
	float GetMeasuredHeight();

	void SetX(int x, bool update = true);
	void SetY(int y,bool update=true);
	virtual void Measure(MeasureEvent e = {});
	virtual void Layout(LayoutEvent e = {});
	void Repaint();
	RfRect GetLocalRect();
	RfRect GetClipRect();
	RfRect GetScreenRect();

	void SetParent(RfView* p);

protected:
	virtual void OnVisibility(bool isVisible);
	virtual void OnMeasure(MeasureEvent e);
	virtual void OnLayout(LayoutEvent e);
	virtual void OnSize(SizeEvent e);
	virtual void OnDraw(DrawEvent e);
	//mouse
	virtual void OnMouseEnter();
	virtual void OnMouseExit();
	virtual void OnMouseUp(MouseEvent e);
	virtual void OnMouseDown(MouseEvent e);
	virtual void OnMouseMove(MouseEvent e);
	virtual void OnMouseScroll(MouseEvent e);

	friend class RfGUIWindow;
	friend class RfLayout;
};

