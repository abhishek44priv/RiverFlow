#include"pch.h"
#include "RfVector2.h"
#include"RfMath.h"

#undef min
RfVector2::RfVector2(float x, float y)
	:x(x),y(y)
{
}

void RfVector2::Plus(RfVector2 p)
{
	x += p.x;
	y += p.y;
}

void RfVector2::Set(float x, float y)
{
	this->x = x;
	this->y = y;
}

void RfVector2::Normalize()
{
	const float length = Length();
	this->x = this->x / length;
	this->y = this->y / length;
}

float RfVector2::SquareLength()
{
	return x*x+y*y;
}

float RfVector2::Length()
{
	return RfMath::SqRoot(SquareLength());
}

void RfVector2::Rotate(float rad)
{
	const float sint = RfMath::Sin(rad);
	const float cost = RfMath::Cos(rad);
	float tempX = x;
	x = (x * cost - y * sint) ;
	y = (y * cost + tempX * sint);
}

void RfVector2::Scale(float sx, float sy)
{
	this->x = this->x * sx;
	this->y = this->y * sy;
}

void RfVector2::Translate(float tx, float ty)
{
	this->x = this->x + tx;
	this->y = this->y + ty;
}

RfVector2 RfVector2::GetNormal()
{
	return {-y,x}; 
}

float RfVector2::Dot(RfVector2 a, RfVector2 b)
{
	return a.x*b.x+ a.y * b.y;
}

//RfVector2 RfVector2::Cross(RfVector2 a, RfVector2 b)
//{
//	float z = a.x * b.y - a.y * b.x;
//	return RfVector2();
//}

RfVector2 RfVector2::Lerp(RfVector2 a, RfVector2 b, float t)
{
	
	return {
		a.x + t * (b.x - a.x),
		a.y + t * (b.y - a.y)
	};
}

float RfVector2::Angle(RfVector2 a, RfVector2 b)
{
	return RfMath::ACos(RfMath::Min(RfMath::Max((a.x * b.x + a.y * b.y)
		/ (a.Length() * b.Length() + std::numeric_limits<float>::min()), -1.0f), 1.0f));
}

float RfVector2::Angle(RfVector2 b)
{
	return Angle({x,y},b);
}

void RfVector2::Zero()
{
	this->x = 0.0f;
	this->y = 0.0f;
}
