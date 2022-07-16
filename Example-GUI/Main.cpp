#include"stdafx.h"
#include<RfRandom.h>
#include<RfWinView.h>
#include<RfImage.h>
#include<RfD2Render.h>
#include<RfD2Bitmap.h>
#include<RfImageView.h>
#include<RfCanvasView.h>
#include<RfSwitch.h>
class Example :public RfGUIWindow
{
	void Example1()
	{
		auto scrollv = new RfScrollView({ this });
		{
			auto topvlinear = new RfLinearLayout({ this });
			topvlinear->width = SIZE_MATCH;
			topvlinear->height = SIZE_MATCH;
			//1
			{
				auto hlinear = new RfLinearLayout({ this },O_HORIZONTAL);
				hlinear->width = SIZE_MATCH;
				hlinear->height = SIZE_WRAP;
				{
					auto imageview = new RfImageView({ this });
					hlinear->AddView(imageview,
						new RfLinearLayout::LayoutParams(ALIGN_LEFT));
					//vlinear
					{
						auto vlinear = new RfLinearLayout({ this });
						vlinear->width = SIZE_WRAP;
						vlinear->height = SIZE_WRAP;
						//some text
						{
							{
								auto text1 = new RfTextView(
									{ this },
									L"abhishek"
								);
								text1->margin = { 2,1 };
								text1->pad = { 2,2 };
								vlinear->AddView(text1,
									new RfLinearLayout::LayoutParams(ALIGN_LEFT));
							}
							{
								auto text1 = new RfTextView(
									{ this },
									L"abhishekkumar2595@outlook.com"
								);
								text1->margin = { 2,1 };
								text1->pad = { 2,2 };
								text1->textColor = RfColor::Gray;
								vlinear->AddView(text1,
									new RfLinearLayout::LayoutParams(ALIGN_LEFT));
							}
							{
								auto text1 = new RfTextView(
									{ this },
									L"Sign out"
								);
								text1->margin = { 2,1 };
								text1->pad = { 2,2 };
								text1->textColor = RfColor::DeepSkyBlue;
								vlinear->AddView(text1,
									new RfLinearLayout::LayoutParams(ALIGN_LEFT));
							}
						}
						hlinear->AddView(vlinear,
							new RfLinearLayout::LayoutParams(ALIGN_LEFT));
					}
				}
				topvlinear->AddView(hlinear,
					new RfLinearLayout::LayoutParams(ALIGN_LEFT));

				auto vsep = [&]() {
					auto vseparator = new RfWidget({ this });
					vseparator->bgColor = RfColor::Gray;
					vseparator->width = SIZE_MATCH;
					vseparator->measuredHeight = 1.0f;
					vseparator->margin = { 4,4 };
					topvlinear->AddView(vseparator,
						new RfLinearLayout::LayoutParams(ALIGN_LEFT));
				};
				vsep();
				{
					//general
					//enable insights
					//{switch} {off}
					//Confirm before deleting
					//{switch} {On}
					
					//++general
					{
						auto general = new RfTextView(
							{ this },
							L"General"
						);
						general->textStyle.size = 20.0f;
						general->margin = { 4,4 };
						general->pad = { 2,2 };
						topvlinear->AddView(general,
							new RfLinearLayout::LayoutParams(ALIGN_LEFT));
					}
					//++enable insights
					{
						auto general = new RfTextView(
							{ this },
							L"Enable insights"
						);
						general->textStyle.size = 15.0f;
						general->margin = { 4,2 };
						general->pad = { 2,2 };
						topvlinear->AddView(general,
							new RfLinearLayout::LayoutParams(ALIGN_LEFT));
					}
					//hlinear
					{
						auto linear = new RfLinearLayout({ this },O_HORIZONTAL);
						linear->width = SIZE_WRAP;
						linear->height = SIZE_WRAP;
						{
							auto switch1 = new RfSwitch({ this });
							linear->AddView(switch1,
								new RfLinearLayout::LayoutParams());

							auto general = new RfTextView(
								{ this },
								L"On"
							);
							general->margin = { 4,2 };
							general->pad = { 2,2 };
							linear->AddView(general,
								new RfLinearLayout::LayoutParams(ALIGN_LEFT));
						}
						topvlinear->AddView(linear,
							new RfLinearLayout::LayoutParams(ALIGN_LEFT));

					}
					//++Confirm before deleting
					{
						auto general = new RfTextView(
							{ this },
							L"Confirm before deleting"
						);
						general->textStyle.size = 15.0f;
						general->margin = { 4,2 };
						general->pad = { 2,2 };
						topvlinear->AddView(general,
							new RfLinearLayout::LayoutParams(ALIGN_LEFT));
					}
					//hlinear
					{
						auto linear = new RfLinearLayout({ this }, O_HORIZONTAL);
						linear->width = SIZE_WRAP;
						linear->height = SIZE_WRAP;
						{
							auto switch1 = new RfSwitch({ this });
							linear->AddView(switch1,
								new RfLinearLayout::LayoutParams());

							auto general = new RfTextView(
								{ this },
								L"On"
							);
							general->margin = { 4,2 };
							general->pad = { 2,2 };
							linear->AddView(general,
								new RfLinearLayout::LayoutParams(ALIGN_LEFT));
						}
						topvlinear->AddView(linear,
							new RfLinearLayout::LayoutParams(ALIGN_LEFT));

					}
				}
				vsep();
				
				//Color
				{
					auto textview = new RfTextView(
						{ this },
						L"Color"
					);
					textview->textStyle.size = 20.0f;
					textview->margin = { 4,4 };
					textview->pad = { 2,2 };
					topvlinear->AddView(textview,
						new RfLinearLayout::LayoutParams(ALIGN_LEFT));
				}

			}
			scrollv->SetMainView(topvlinear);
		}
		
		AddLayout(scrollv);
	}
public:
	Example()
	{
		
		int which = 0;
		switch (which)
		{
		case 0:
			Example1();
			break;

		}
		
	}
protected:
	virtual void OnPaint(RfPaintParams e) override
	{
		
		//RfConsole::Clear();
		RfGUIWindow::OnPaint(e);

		//e.dirtyRect.Print("win dirtyRect");

		
		
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