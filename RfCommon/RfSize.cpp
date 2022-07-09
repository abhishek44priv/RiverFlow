#include"pch.h"
#include "RfSize.h"

RfSize::RfSize()
{
	this->width = height = 0;
}
RfSize::RfSize(const RfSize& size)
{
	this->width = size.width;
	this->height = size.height;
}
RfSize::RfSize(float width, float height)
{
	this->width = width;
	this->height = height;
}
bool RfSize::Equals(const RfSize& sz) const
{
	return (width == sz.width) && (height == sz.height);
}
bool RfSize::Empty() const
{
	return (width == 0 && height == 0);
}