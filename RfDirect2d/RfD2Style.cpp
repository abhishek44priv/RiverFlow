#include"pch.h"
#include "RfD2Style.h"

#include"RfD2Factory.h"
static D2D1_CAP_STYLE TO_D2_CAP(RfD2Cap cap)
{
	switch (cap)
	{
	case RfD2Cap::FLAT:
		return D2D1_CAP_STYLE::D2D1_CAP_STYLE_FLAT;
	case RfD2Cap::SQUARE:
		return D2D1_CAP_STYLE::D2D1_CAP_STYLE_SQUARE;
	case RfD2Cap::ROUND:
		return D2D1_CAP_STYLE::D2D1_CAP_STYLE_ROUND;
	case RfD2Cap::TRIANGE:
		return D2D1_CAP_STYLE::D2D1_CAP_STYLE_TRIANGLE;
	default:
		break;
	}
	return D2D1_CAP_STYLE::D2D1_CAP_STYLE_FLAT;
}
static D2D1_LINE_JOIN TO_D2_JOINT(RfD2Join join)
{
	switch (join)
	{
	case RfD2Join::MITER:
		return D2D1_LINE_JOIN::D2D1_LINE_JOIN_MITER;
	case RfD2Join::BEVEL:
		return D2D1_LINE_JOIN::D2D1_LINE_JOIN_BEVEL;
	case RfD2Join::ROUND:
		return D2D1_LINE_JOIN::D2D1_LINE_JOIN_ROUND;
		break;
	case RfD2Join::MITER_OR_BEVEL:
		return D2D1_LINE_JOIN::D2D1_LINE_JOIN_MITER_OR_BEVEL;
	default:
		break;
	}
	return D2D1_LINE_JOIN::D2D1_LINE_JOIN_ROUND;
}
static D2D1_DASH_STYLE TO_D2_DASH_STYLE(RfD2DashStyle dash)
{
	switch (dash)
	{
	case RfD2DashStyle::SOLID:
		return D2D1_DASH_STYLE::D2D1_DASH_STYLE_SOLID;
	case RfD2DashStyle::DASH:
		return D2D1_DASH_STYLE::D2D1_DASH_STYLE_DASH;
	case RfD2DashStyle::DOT:
		return D2D1_DASH_STYLE::D2D1_DASH_STYLE_DOT;
	case RfD2DashStyle::DASH_DOT:
		return D2D1_DASH_STYLE::D2D1_DASH_STYLE_DASH_DOT;
	case RfD2DashStyle::DASH_DOT_DOT:
		return D2D1_DASH_STYLE::D2D1_DASH_STYLE_DASH_DOT_DOT;
	case RfD2DashStyle::CUSTOM:
		return D2D1_DASH_STYLE::D2D1_DASH_STYLE_CUSTOM;
	default:
		break;
	}
	return D2D1_DASH_STYLE::D2D1_DASH_STYLE_SOLID;
}
void* RfD2Style::Native()
{
	auto factory = (ID2D1Factory*)RfD2Factory::n_factory;
	ID2D1StrokeStyle* nstyle = nullptr;
	factory->CreateStrokeStyle(
		D2D1::StrokeStyleProperties(
			TO_D2_CAP(startCap),
			TO_D2_CAP(endCap),
			TO_D2_CAP(dashCap),
			TO_D2_JOINT(lineJoin),
			miterLimit,
			TO_D2_DASH_STYLE(dashStyle),
			dashOffset
		),
		dashes,
		count,
		&nstyle
	);
	if (!nstyle)
	{
		std::cout << "error ID2D1StrokeStyle\n";
	}
	return nstyle;
}
