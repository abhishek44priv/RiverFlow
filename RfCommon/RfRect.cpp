#include"pch.h"
#include "RfRect.h"
#include"RfMath.h"
RfRect::RfRect()
{
	x = y = width = height = 0;
}
RfRect::RfRect(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}
RfRect::RfRect(const RfPoint& location, const RfSize& size)
{
	this->x = location.x;
	this->y = location.y;
	this->width = size.width;
	this->height = size.height;
}
RfRect* RfRect::Clone() const
{
	return new RfRect(x, y, width, height);
}
void RfRect::SetXYWH(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
}
void RfRect::SetLTRB(float l, float t, float r, float b)
{
	SetXYWH(l, t, r - l, b - t);
}
void RfRect::GetLocation(RfPoint* point) const
{
	point->x = x;
	point->y = y;
}
void RfRect::GetSize(RfSize* size) const
{
	size->width = width;
	size->height = height;
}
void RfRect::GetBounds(RfRect* rect) const
{
	rect->x = x;
	rect->y = y;
	rect->width = width;
	rect->height = height;
}
float RfRect::GetLeft() const
{
	return x;
}
float RfRect::GetTop() const
{
	return y;
}
float RfRect::GetRight() const
{
	return x + width;
}
float RfRect::GetBottom() const
{
	return y + height;
}
bool RfRect::IsEmptyArea() const
{
	return (width <= 0) || (height <= 0);
}
bool RfRect::Equals(const RfRect& rect) const
{
	return x == rect.x &&
		this->y == rect.y &&
		this->width == rect.width &&
		this->height == rect.height;
}
bool RfRect::Contains(float x, float y) const
{
	return x >= this->x && x < (this->x + width) &&
		y >= this->y && y < (this->y + height);
}
bool RfRect::Contains(const RfPoint& pt) const
{
	return Contains(pt.x, pt.y);
}
bool RfRect::Contains(const RfRect& rect) const
{
	return (x <= rect.x) && (rect.GetRight() <= GetRight()) &&
		(y <= rect.y) && (rect.GetBottom() <= GetBottom());
}
void RfRect::Inflate(float dx, float dy)
{
	this->x -= dx;
	this->y -= dy;
	this->width += 2 * dx;
	this->height += 2 * dy;
}
void RfRect::Inflate(const RfPoint& point)
{
	Inflate(point.x, point.y);
}
bool RfRect::Intersect(const RfRect& rect)
{
	return Intersect(*this, *this, rect);
}
bool RfRect::Intersect(RfRect& c, const RfRect& a, const RfRect& b)
{
	float right = RfMath::Min(a.GetRight(), b.GetRight());
	float bottom = RfMath::Min(a.GetBottom(), b.GetBottom());
	float left = RfMath::Max(a.GetLeft(), b.GetLeft());
	float top = RfMath::Max(a.GetTop(), b.GetTop());
	c.x = left;
	c.y = top;
	c.width = right - left;
	c.height = bottom - top;
	if (c.width < 0)
		c.width = 0;
	if (c.height < 0)
		c.height = 0;
	return !c.IsEmptyArea();
}
bool RfRect::IntersectsWith(const RfRect& rect2) const
{
	RfRect out;
	return RfRect::Intersect(out, *this, rect2);
	/*RfRect rect1 = *this;
	if (rect1.x < rect2.x + rect2.width &&
		rect1.x + rect1.width > rect2.x &&
		rect1.y < rect2.y + rect2.height &&
		rect1.height + rect1.y > rect2.y)
	{
		return true;
	}
	return false;*/
	/*return (GetLeft() < rect.GetRight() &&
		GetTop() < rect.GetBottom() &&
		GetRight() > rect.GetLeft() &&
		GetBottom() > rect.GetTop());*/
}
bool RfRect::Union(RfRect& c, const RfRect& a, const RfRect& b)
{
	float right = RfMath::Max(a.GetRight(), b.GetRight());
	float bottom = RfMath::Max(a.GetBottom(), b.GetBottom());
	float left = RfMath::Min(a.GetLeft(), b.GetLeft());
	float top = RfMath::Min(a.GetTop(), b.GetTop());

	c.x = left;
	c.y = top;
	c.width = right - left;
	c.height = bottom - top;
	return !c.IsEmptyArea();
}
void RfRect::Offset(const RfPoint& point)
{
	Offset(point.x, point.y);
}
void RfRect::Offset(float dx, float dy)
{
	this->x += dx;
	this->y += dy;
}

void RfRect::Print(const char* msg)
{
	std::cout << msg << " x::" << x << " y:" << y << " w:" << width << " h:" << height << "\n";
}

void RfRect::PrintLTRB(const char* msg)
{
	std::cout << msg << " L::" << GetLeft() << " T:" << GetTop() << " R:" << GetRight() << " B:" << GetBottom() << "\n";
}