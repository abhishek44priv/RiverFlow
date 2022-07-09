#include"pch.h"
#include "RfMath.h"
float RfMath::PI = 3.14159265f;
float RfMath::Rad2Deg = 180.0f/PI;
float RfMath::Deg2Rad = 1.0f/ Rad2Deg;
float RfMath::Sin(float rad)
{
	return std::sin(rad);
}
float RfMath::Cos(float rad)
{
	return ::cosf(rad);

}
float RfMath::Tan(float rad)
{
	return ::tanf(rad);
}
float RfMath::ASin(float ratio)
{
	return ::asinf(ratio);
}
float RfMath::ACos(float ratio)
{
	return ::acosf(ratio);
}
float RfMath::ATan(float ratio)
{
	return ::atanf(ratio);
}
int RfMath::Abs(int v)
{
	return std::abs(v);
}
float RfMath::Abs(float v)
{
	return std::abs(v);
}
double RfMath::Abs(double v)
{
	return std::abs(v);
}
long RfMath::Abs(long v)
{
	return std::abs(v);
}
int RfMath::Ceil(float v)
{
	return (int)std::ceil(v);
}
int RfMath::Floor(float v)
{
	return (int)std::floor(v);

}
float RfMath::Log(float v)
{
	return std::log(v);

}
float RfMath::Log10(float v)
{
	return std::log10(v);

}
int RfMath::Fmod(float divident, float divisor)
{
	return (int)std::fmod(divident, divisor);
}
float RfMath::SqRoot(float v)
{
	return std::sqrt(v);
}
float RfMath::Square(float v)
{
	return v * v;
}
float RfMath::Power(float base, float exponent)
{
	return std::pow(base, exponent);
}
float RfMath::ModF(float v, int& intPart)
{
	return (float)std::modf(v, (double*)&intPart);
}
float RfMath::Exp(float exponent)
{
	return std::exp(exponent);
}
int RfMath::Max(int a, int b)
{
	return a > b ? a : b;
}
int RfMath::Min(int a, int b)
{
	return a < b ? a : b;
}
float RfMath::Max(float a, float b)
{
	return a > b ? a : b;
}
float RfMath::Min(float a, float b)
{
	return a < b ? a : b;
}
float RfMath::Normalize(float v, float maxValue)
{
	return v / maxValue;
}
float RfMath::SqDist(float x, float y)
{
	return x * x + y * y;
}
float RfMath::Distance(float x, float y)
{
	return SqRoot(SqDist(x, y));
}

//interpolate

float RfMath::Clamp(float x, float lowerlimit, float upperlimit) {
	if (x < lowerlimit)
		x = lowerlimit;
	if (x > upperlimit)
		x = upperlimit;
	return x;
}
float RfMath::Smoothstep(float edge0, float edge1, float x) {
	// Scale, bias and saturate x to 0..1 range
	x = Clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
	// Evaluate polynomial
	return x * x * (3 - 2 * x);
}