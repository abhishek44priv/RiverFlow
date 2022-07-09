#pragma once
#include"RfTextStyle.h"
#include<RfSize.h>
class RfTextLayout 
{
public:
	RfTextLayout(const wchar_t* txt,
		RfTextStyle style,
		float boxWidth=0,
		float boxHeight=0
	);
	~RfTextLayout();
	RfSize GetSize();
protected:
	struct Info
	{
		void *n_layout = nullptr;
		RfTextStyle style;
	};
	Info info;
	friend class RfD2Render;
};