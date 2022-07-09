#include"pch.h"
#include "RfPoint.h"
RfPoint::RfPoint()
{
	this->x = y = 0;
}
RfPoint::RfPoint(const RfPoint& point)
{
	this->x = point.x;
	this->y = point.y;
}
RfPoint::RfPoint(const RfSize& size)
{
	this->x = size.width;
	this->y = size.height;
}
RfPoint::RfPoint(float x, float y)
{
	this->x = x;
	this->y = y;
}
void RfPoint::Set(float x, float y)
{
	this->x = x;
	this->y = y;
}
bool RfPoint::Equals(const RfPoint& point)
{
	return (x == point.x) && (y == point.y);
}

