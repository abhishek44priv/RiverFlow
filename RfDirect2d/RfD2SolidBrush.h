#pragma once
#include "RfD2Brush.h"
#include<RfColor.h>
class RfD2SolidBrush :
    public RfD2Brush
{
public:
	RfD2SolidBrush();
	RfD2SolidBrush(RfD2Render* render, RfColor color= RfColor(RfColor::Aqua));
	void Create(RfD2Render* render, RfColor color = RfColor(RfColor::Aqua));
	void SetColor(RfColor color);
};

