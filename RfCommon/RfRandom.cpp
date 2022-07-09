#include"pch.h"
#include "RfRandom.h"

static void Init();
static bool m_isSeeded=false;

int RfRandom::RangeInt(int a, int b)
{
	Init();
	return  int(a + (float(::rand()) / float(RAND_MAX)) * (b - a));
}

float RfRandom::RangeFloat(float a, float b)
{
	Init();
	return  a + (float(::rand()) / float(RAND_MAX)) * (b - a);
}

void Init()
{
	if (!m_isSeeded)
	{
		m_isSeeded = true;
		::srand((unsigned int)time(0));
	}
}