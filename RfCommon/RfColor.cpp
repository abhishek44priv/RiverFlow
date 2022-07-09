#include"pch.h"
#include "RfColor.h"

template<typename T1, typename T2, typename T3, typename T4>
constexpr auto _RGBA(T1 r, T2 g, T3 b, T4 a) { return (((unsigned int)(unsigned char)r) << 24) | (((unsigned int)(unsigned char)g) << 16) | (((unsigned int)(unsigned char)b) << 8) | (((unsigned int)(unsigned char)a) << 0) ; }


RfColor::RfColor(unsigned int rgba)
	:rgba(rgba)
{
	
}

RfColor::RfColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	:rgba(_RGBA(r,g,b,a))
{
}

void RfColor::Set(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	rgba = _RGBA(r, g, b, a);
}


void RfColor::Set(unsigned int rgba)
{
	this->rgba = rgba;
}

unsigned char RfColor::GetR()
{
	return  (rgba & 0xff000000) >> 24;
}

unsigned char RfColor::GetG()
{
	return (rgba & 0x00ff0000) >> 16;
}

unsigned char RfColor::GetB()
{
	return  (rgba & 0x0000ff00) >> 8;
}

unsigned char RfColor::GetA()
{
	return  (rgba & 0x000000ff);
}

RfColor::RfColorF RfColor::ToRfColorF()
{
	return { GetR() / 255.0f,GetG() / 255.0f, GetB() / 255.0f, GetA() / 255.0f };
}
