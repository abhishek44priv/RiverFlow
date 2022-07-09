#pragma once
#include<RfColor.h>
#include<RfRect.h>
#include"RfD2Style.h"
#include"RfTextLayout.h"
class RfD2Brush;
class RfD2Render
{
public:
	RfD2Render();
	~RfD2Render();
	RfPoint GetOffset();
	void PlusOffest(float offx, float offy);
	void ResetOffset();
	void PushClipRect(RfRect rect);
	void PopClipRect();
	RfSize GetSize();
	void DrawRect(RfRect rect, RfColor color, 
		float width = 1.0f , RfD2Style style={});
	void FillRect(RfRect rect, RfColor color);

	void DrawRRect(RfRect rect,float xRad,float yRad,
		RfColor color,float width = 1.0f , RfD2Style style={});
	void FillRRect(RfRect rect, float xRad, float yRad,
		RfColor color);

	void DrawEllipse(RfPoint center,float xRad,float yRad, RfColor color,
		float width = 1.0f , RfD2Style style={});
	void FillEllipse(RfPoint center, float xRad, float yRad,
		RfColor color);

	void DrawLine(RfPoint p1, RfPoint p2, RfColor color,
		float width = 1.0f , RfD2Style style={});

	void DrawRect(RfRect rect,  RfD2Brush &brush,
		float width = 1.0f , RfD2Style style={});
	void FillRect(RfRect rect,  RfD2Brush &brush);

	void DrawRRect(RfRect rect, float xRad, float yRad,
		 RfD2Brush &brush, float width = 1.0f , RfD2Style style={});
	void FillRRect(RfRect rect, float xRad, float yRad,
		 RfD2Brush &brush);

	void DrawEllipse(RfPoint center, float xRad, float yRad,  RfD2Brush &brush,
		float width = 1.0f , RfD2Style style={});
	void FillEllipse(RfPoint center, float xRad, float yRad,
		 RfD2Brush &brush);

	void DrawLine(RfPoint p1, RfPoint p2,  RfD2Brush &brush,
		float width = 1.0f , RfD2Style style={});

	void DrawString(const wchar_t* text, RfRect rect,
		RfTextStyle txtStyle, RfD2Brush& brush);
	void DrawString(const wchar_t* text, RfRect rect,
		RfTextStyle txtStyle = {},RfColor color=RfColor::Black);
	void DrawTextLayout(RfTextLayout& txtLayout, RfPoint xy, RfColor color = RfColor::Black);
	//image

	void Begin();
	void End();
	void Clear(RfColor color, RfRect rect = {});
	void* GetNativeRender();
protected:
	struct Info {
		void* n_d2Render = nullptr;

		RfPoint offset = { 0,0 };
	};;
	Info info;
};

