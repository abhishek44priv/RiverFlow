#include"pch.h"
#include "RfPreciseTime.h"
static long ___g_frequency = 0;
static bool isInited = false;
static void Init();
long RfPreciseTime::GetTick()
{
	Init();
	LARGE_INTEGER ticks;
	if (!QueryPerformanceCounter(&ticks))
	{
		std::cout << "some error in GetTicks\n";
	}
	return(long)ticks.QuadPart;
}

long  RfPreciseTime::GetFrequency()
{
	Init();
	return ___g_frequency;
}

float RfPreciseTime::MesureTime(std::function<void()> fun)
{
	auto a = Millisecond();
	fun();
	auto b = Millisecond();
	return b - a;
}

float RfPreciseTime::Millisecond()
{

	return GetTick() * (1000.0f / ___g_frequency);
}

float RfPreciseTime::Second()
{
	return GetTick() * (1.0f / ___g_frequency);
}

void Init()
{
	if (!isInited)
	{
		if (!QueryPerformanceFrequency((LARGE_INTEGER*)&___g_frequency))
		{
			std::cout << "erro  InitTimer\n";
		}
	}
	else
		isInited = true;
}