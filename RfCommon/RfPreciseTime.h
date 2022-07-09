#pragma once
#include"pch.h"
class RfPreciseTime
{
public:
    static float Millisecond();
    static  float Second();
    static  long  GetTick();
    static  long  GetFrequency();
    static float MesureTime(std::function<void()> fun);
};

