#include"stdafx.h"

class Example :public RfGUIWindow
{
public:
	Example()
	{
		auto mainLayout = new RfBorderLayout({ this }); {
			mainLayout->margin={10,10};
		}
		auto tv1 = new RfTextView({ this }, L"Click Me"); {
			tv1->SetWidth(SIZE_MATCH);
		}
		mainLayout->AddView(tv1, {});
		SetMainLayout(mainLayout);
	}
protected:
	virtual void OnPaint(RfPaintParams e) override
	{
		RfGUIWindow::OnPaint(e);

		e.dirtyRect.Print("win dirtyRect");
	}
	virtual void OnMouseMove(RfMouseEvent& e) override
	{
		RfGUIWindow::OnMouseMove(e);

	}
protected:

};

//template <class... _Types>
//_NODISCARD string format(const _Fmt_string<_Types...> _Fmt, _Types&&... _Args) {


int main()
{
	Example win;
	RfGUIWindow::EventLoop();
}

/*
	View
		Layout
			LinearLayout
			FlowLayout
			BorderLayout
		Widget
			TextView
			EditText
			Button
			ProgressBar
			ImageView


*/