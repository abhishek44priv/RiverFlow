#pragma once
enum class RfD2Cap { FLAT, SQUARE, ROUND, TRIANGE };
enum class RfD2Join { MITER, BEVEL, ROUND, MITER_OR_BEVEL };
enum class RfD2DashStyle { SOLID, DASH, DOT, DASH_DOT, DASH_DOT_DOT, CUSTOM };
struct RfD2Style
{
	RfD2Cap startCap = RfD2Cap::FLAT;
	RfD2Cap endCap = RfD2Cap::FLAT;
	RfD2Cap dashCap = RfD2Cap::FLAT;
	RfD2Join lineJoin = RfD2Join::ROUND;
	RfD2DashStyle dashStyle = RfD2DashStyle::SOLID;
	float dashOffset = 0.0f;
	float* dashes = nullptr;
	float miterLimit = 1.0f;
	unsigned int count = 0;
	void* Native();
};
